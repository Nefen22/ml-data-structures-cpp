/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "tensor/xtensor_lib.h"
#include "loader/dataset.h"

using namespace std;

template<typename DType, typename LType>
class DataLoader{
public:
    class Iterator; //forward declaration for class Iterator
    
private:
    Dataset<DType, LType>* ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int nbatch;
    ulong_tensor item_indices;
    int m_seed;
    
public:
    DataLoader(Dataset<DType, LType>* ptr_dataset, 
            int batch_size, bool shuffle=true, 
            bool drop_last=false, int seed=-1)
                : ptr_dataset(ptr_dataset), 
                batch_size(batch_size), 
                shuffle(shuffle),
                m_seed(seed),
                drop_last(drop_last){
            nbatch = ptr_dataset->len()/batch_size;
            if (!drop_last and ptr_dataset->len() % batch_size != 0) {
                nbatch++;
            }
            item_indices = xt::arange(0, ptr_dataset->len());
    }
    virtual ~DataLoader(){}
    
    //New method: from V2: begin
    int get_batch_size(){ return batch_size; }
    int get_sample_count(){ return ptr_dataset->len(); }
    int get_total_batch(){return int(ptr_dataset->len()/batch_size); }
    
    //New method: from V2: end
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
public:


    class Iterator
    {
    private:
        int cursor;
        DataLoader<DType, LType>* pLoader;

    public:
        Iterator(DataLoader<DType, LType>* pLoader, int index = 0)
        {
            this->pLoader = pLoader;
            this->cursor = index;
        }
        Iterator& operator=(const Iterator& iterator)
        {
            cursor = iterator.cursor;
            pLoader = iterator.pLoader;
            return *this;
        }

        Batch<DType, LType> subLoad(int cur, int lim) {
            xt::xarray<DType> reData;
            xt::xarray<LType> reLabel;
            bool first = true;
            for (int i = cur; i < lim; i++) {
                DataLabel<DType, LType> curData = this->pLoader->ptr_dataset->getitem(this->pLoader->item_indices[i]);
                if (first) {
                    reData = xt::xarray<DType>(xt::expand_dims(curData.getData(), 0));
                    reLabel = xt::xarray<LType>(xt::expand_dims(curData.getLabel(), 0));
                    first = false;
                    continue;
                }
                reData = xt::xarray<DType>(xt::concatenate(xt::xtuple(reData, xt::expand_dims(curData.getData(), 0)), 0));
                reLabel = xt::xarray<LType>(xt::concatenate(xt::xtuple(reLabel,  xt::expand_dims(curData.getLabel(), 0)), 0));
            }
            return Batch<DType, LType>(reData, reLabel);
        }

        Batch<DType, LType> operator*()
        {
            int nextBatch = this->cursor + 1;
            int cur = this->cursor * this->pLoader->get_batch_size();
            int lim = nextBatch * this->pLoader->get_batch_size();
            if (lim > this->pLoader->get_sample_count()) {
                lim = this->pLoader->get_sample_count();
            }
            return subLoad(cur, lim);
            
        }
        bool operator!=(const Iterator& iterator)
        {
            return cursor != iterator.cursor;
        }
        // Prefix ++ overload
        Iterator& operator++()
        {
            this->cursor++;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        
    };
    Iterator begin() {
        //YOUR CODE IS HERE
        if (shuffle) {
            if (m_seed >= 0) xt::random::seed(m_seed);
            xt::random::shuffle(item_indices);
        }
        return Iterator(this, 0);
    }
    Iterator end() {
        //YOUR CODE IS HERE
        return Iterator(this, nbatch);
    }
    // Iterator: END
    
    //BEGIN of Iterator

    //YOUR CODE IS HERE: to define iterator

    //END of Iterator
    
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
};


#endif /* DATALOADER_H */


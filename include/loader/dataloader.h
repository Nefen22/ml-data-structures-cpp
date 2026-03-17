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
            int actual_size = lim - cur;
            if (actual_size <= 0) {
                // return empty batch hoặc throw tùy assignment
                return Batch<DType, LType>(xt::xarray<DType>{}, xt::xarray<LType>{});
            }

            // Lấy shape của 1 mẫu
            auto sample = pLoader->ptr_dataset->getitem(pLoader->item_indices[cur]);
            auto data_shape_1 = sample.getData().shape();
            auto label_shape_1 = sample.getLabel().shape();

            // Tạo tensor lớn với batch dim
            xt::svector<size_t> batch_data_shape = data_shape_1;
            batch_data_shape.insert(batch_data_shape.begin(), actual_size);

            xt::svector<size_t> batch_label_shape = label_shape_1;
            batch_label_shape.insert(batch_label_shape.begin(), actual_size);

            xt::xarray<DType> reData = xt::empty<DType>(batch_data_shape);
            xt::xarray<LType> reLabel = xt::empty<LType>(batch_label_shape);

            for (int b = 0; b < actual_size; ++b) {
                int idx = pLoader->item_indices[cur + b];
                auto item = pLoader->ptr_dataset->getitem(idx);

                // Copy vào slice
                xt::view(reData, b) = item.getData();
                xt::view(reLabel, b) = item.getLabel();
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
            if (m_seed > -1) xt::random::seed(m_seed);
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


/*
 * File:   DLinkedList.h
 */

#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "list/IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class DLinkedList : public IList<T>
{
public:
    class Node;        // Forward declaration
    class Iterator;    // Forward declaration
    class BWDIterator; // Forward declaration

protected:
    Node *head; // this node does not contain user's data
    Node *tail; // this node does not contain user's data
    int count;
    bool (*itemEqual)(T &lhs, T &rhs);        // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(DLinkedList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    DLinkedList(
        void (*deleteUserData)(DLinkedList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0);
    DLinkedList(const DLinkedList<T> &list);
    DLinkedList<T> &operator=(const DLinkedList<T> &list);
    ~DLinkedList();

    // Inherit from IList: BEGIN
    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item, void (*removeItemData)(T) = 0);
    bool empty();
    int size();
    void clear();
    T &get(int index);
    int indexOf(T item);
    bool contains(T item);
    string toString(string (*item2str)(T &) = 0);
    // Inherit from IList: END

    void println(string (*item2str)(T &) = 0)
    {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T> *) = 0)
    {
        this->deleteUserData = deleteUserData;
    }

    bool contains(T array[], int size)
    {
        int idx = 0;
        for (DLinkedList<T>::Iterator it = begin(); it != end(); it++)
        {
            if (!equals(*it, array[idx++], this->itemEqual))
                return false;
        }
        return true;
    }

    /*
     * free(DLinkedList<T> *list):
     *  + to remove user's data (type T, must be a pointer type, e.g.: int*, Point*)
     *  + if users want a DLinkedList removing their data,
     *      he/she must pass "free" to constructor of DLinkedList
     *      Example:
     *      DLinkedList<T> list(&DLinkedList<T>::free);
     */
    static void free(DLinkedList<T> *list)
    {
        typename DLinkedList<T>::Iterator it = list->begin();
        while (it != list->end())
        {
            delete *it;
            it++;
        }
    }

    /* begin, end and Iterator helps user to traverse a list forwardly
     * Example: assume "list" is object of DLinkedList

     DLinkedList<char>::Iterator it;
     for(it = list.begin(); it != list.end(); it++){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

    /* last, beforeFirst and BWDIterator helps user to traverse a list backwardly
     * Example: assume "list" is object of DLinkedList

     DLinkedList<char>::BWDIterator it;
     for(it = list.last(); it != list.beforeFirst(); it--){
            char item = *it;
            std::cout << item; //print the item
     }
     */
    BWDIterator bbegin()
    {
        return BWDIterator(this, true);
    }
    BWDIterator bend()
    {
        return BWDIterator(this, false);
    }

protected:
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }
    void copyFrom(const DLinkedList<T> &list);
    void removeInternalData();
    Node *getPreviousNodeOf(int index);

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    class Node
    {
    public:
        T data;
        Node *next;
        Node *prev;
        friend class DLinkedList<T>;

    public:
        Node(Node *next = 0, Node *prev = 0)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next = 0, Node *prev = 0)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    //////////////////////////////////////////////////////////////////////
    class BWDIterator {
    private:
        Node* current;
        DLinkedList<T>* list;

    public:
        BWDIterator(DLinkedList<T>* list, bool begin) {
            this->list = list;
            if (begin)
                current = list->tail->prev;
            else
                current = list->head;
        }

        bool operator!=(const BWDIterator& other) {
            return current != other.current;
        }

        T& operator*() {
            return current->data;
        }

        BWDIterator& operator++() {
            current = current->prev;
            return *this;
        }
        BWDIterator operator++(int)
        {
            BWDIterator iterator = *this;
            ++*this;
            return iterator;
        }
    };

    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *pNode;

    public:
        Iterator(DLinkedList<T> *pList = 0, bool begin = true)
        {
            if (begin)
            {
                if (pList != 0)
                    this->pNode = pList->head->next;
                else
                    pNode = 0;
            }
            else
            {
                if (pList != 0)
                    this->pNode = pList->tail;
                else
                    pNode = 0;
            }
            this->pList = pList;
        }

        Iterator &operator=(const Iterator &iterator)
        {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node *pNext = pNode->prev; // MUST prev, so iterator++ will go to end
            if (removeItemData != 0)
                removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }

        T &operator*()
        {
            return pNode->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return pNode != iterator.pNode;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            pNode = pNode->next;
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
};
//////////////////////////////////////////////////////////////////////
// Define a shorter name for DLinkedList:

template <class T>
using List = DLinkedList<T>;

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
DLinkedList<T>::DLinkedList(
    void (*deleteUserData)(DLinkedList<T> *),
    bool (*itemEqual)(T &, T &))
{
    // TODO
    this->deleteUserData = deleteUserData;
    this->itemEqual = itemEqual;
    this->head = new Node;
    this->tail = new Node;
    this->head->next = tail;
    this->tail->prev = head;
    this->count = 0;
}

template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &list)
{
    // TODO
    this->itemEqual = list.itemEqual;
    this->deleteUserData = 0;
    this->head = new Node;
    this->tail = new Node;
    this->head->next = tail;
    this->tail->prev = head;
    this->count = 0;
    this->copyFrom(list);
}

template <class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list)
{
    // TODO
    if (this == &list) return *this;
    this->clear();
    this->deleteUserData = 0;
    this->count = 0;
    this->copyFrom(list);
    return *this;
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
    // TODO
    if (head != nullptr)
        removeInternalData();
}

template <class T>
void DLinkedList<T>::add(T e)
{
    // TODO
    this->add(count, e);
}

template <class T>
void DLinkedList<T>::add(int index, T e)
{
    // TODO
    if (index < 0 or index > count) throw out_of_range("Index is invalid!");
    Node* newNode = new Node(e);
    Node* tmp = this->getPreviousNodeOf(index);
    newNode->next = tmp->next;
    newNode->prev = tmp;
    tmp->next->prev = newNode;
    tmp->next = newNode;
    this->count++;
}

template <class T>
typename DLinkedList<T>::Node *DLinkedList<T>::getPreviousNodeOf(int index)
{
    /**
     * Returns the node preceding the specified index in the doubly linked list.
     * If the index is in the first half of the list, it traverses from the head; otherwise, it traverses from the tail.
     * Efficiently navigates to the node by choosing the shorter path based on the index's position.
     */
    // TODO
    if (index < 0 or index > count) throw out_of_range("Index is invalid!");
    Node* tmp = head->next;
    bool goTail = false;
    if (index > count / 2) goTail = true;
    if (goTail) {
        tmp = tail;
        for (int i = count; i > index; i--) {
            tmp = tmp->prev;
        }
    }
    else {
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
    }
    return tmp->prev;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    // TODO
    if (index < 0 or index >= count) throw out_of_range("Index is invalid!");
    Node* tmp = this->getPreviousNodeOf(index);
    Node* reNode = tmp->next;
    tmp->next = reNode->next;
    reNode->next->prev = tmp;
    reNode->next = nullptr;
    reNode->prev = nullptr;
    T reVal = reNode->data;
    this->count--;
    delete reNode;
    return reVal;
}

template <class T>
bool DLinkedList<T>::empty()
{
    // TODO
    return (count == 0) ? true : false;
}

template <class T>
int DLinkedList<T>::size()
{
    // TODO
    return this->count;
}

template <class T>
void DLinkedList<T>::clear()
{
    // TODO
    this->removeInternalData();
    this->head = new Node;
    this->tail = new Node;
    this->head->next = tail;
    this->tail->prev = head;
    this->count = 0;
    
}

template <class T>
T &DLinkedList<T>::get(int index)
{
    // TODO
    return this->getPreviousNodeOf(index)->next->data;
}

template <class T>
int DLinkedList<T>::indexOf(T item)
{
    // TODO
    int index = 0;
    for (Node* tmp = head->next; tmp != tail; tmp = tmp->next) {
        if (this->itemEqual != 0 and this->itemEqual(tmp->data, item)) return index;
        else if (tmp->data == item) return index;
            index++;
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T))
{
    // TODO
    int index = this->indexOf(item);
    if (index == -1) return false;
    T delData = this->removeAt(index);
    if (removeItemData) removeItemData(delData);
    return true;
}

template <class T>
bool DLinkedList<T>::contains(T item)
{
    // TODO
    if (this->indexOf(item) == -1) return false;
    return true;
}

template <class T>
string DLinkedList<T>::toString(string (*item2str)(T &))
{
    /**
     * Converts the list into a string representation, where each element is formatted using a user-provided function.
     * If no custom function is provided, it directly uses the element's default string representation.
     * Example: If the list contains {1, 2, 3} and the provided function formats integers, calling toString would return "[1, 2, 3]".
     *
     * @param item2str A function that converts an item of type T to a string. If null, default to string conversion of T.
     * @return A string representation of the list with elements separated by commas and enclosed in square brackets.
     */
    // TODO
    string reVal = "[";
    for (Node* tmp = head->next; tmp != tail; tmp = tmp->next) {
        if(item2str != nullptr)
            reVal += (tmp->next == tail) ? item2str(tmp->data)  : item2str(tmp->data) + ",";
        else{
            ostringstream oss;
            oss << tmp->data;
            reVal += (tmp->next == tail)? oss.str() : oss.str() + ",";
        }
    }
    return reVal + "]";
}

template <class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T> &list)
{
    /**
     * Copies the contents of another doubly linked list into this list.
     * Initializes the current list to an empty state and then duplicates all data and pointers from the source list.
     * Iterates through the source list and adds each element, preserving the order of the nodes.
     */
    // TODO
    this->itemEqual = list.itemEqual;
    if (list.count == 0) return;
    Node* tmp = list.head->next; 
    for (int i = 0; i < list.count; i++) {
        this->add(tmp->data);
        tmp = tmp->next;
    }
}

template <class T>
void DLinkedList<T>::removeInternalData()
{
    /**
     * Clears the internal data of the list by deleting all nodes and user-defined data.
     * If a custom deletion function is provided, it is used to free the user's data stored in the nodes.
     * Traverses and deletes each node between the head and tail to release memory.
     */
    if (head == nullptr) return;
    if (this->deleteUserData != 0) {
        this->deleteUserData(this);
    }

    while (this->count > 0)
        this->removeAt(0);
    
    delete head;
    delete tail;
    head = tail = nullptr; 
    this->count = 0;
}

#endif /* DLINKEDLIST_H */

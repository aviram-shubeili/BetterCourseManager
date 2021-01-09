//
// Created by uri25 on 02/01/2021.
//

#ifndef BOOM2_HASHMAP_H
#define BOOM2_HASHMAP_H
#include "NodeHash.h"
#define STARTING_SIZE 100
#define RESIZE_ON 4

/**
 * Generic Dynamic HashMap (rehash) using chain Hashing
 */
template< typename T>
class HashMap {
private:
    //array of ptrs to lists
    std::shared_ptr<NodeHash<T>>* nodePtrArray;
    int size; // m
    int used_current_keys; // n
    int decodeKey(int key);
    void resizeMap(int new_size);
public:
    HashMap<T>();
    ~HashMap<T>();

    int getUsedCurrentKeys() const;

    //cleans an array of chains
    void cleanMap(int n_size, std::shared_ptr<NodeHash<T>>* n_nodePtrArray);

    //will return nullptr if already exists
    std::shared_ptr<NodeHash<T>> insert(int key);

    //will return nullptr if desnt exists
    std::shared_ptr<NodeHash<T>> find(int key);

    //will return false if couldnt find the key
    bool deleteNode(int key);

    //debug func
    void printMap();
};

/*
 * ************************************************************************************************************
 * ************************************************************************************************************
 *                                                 Implementation
 * ************************************************************************************************************
 * ************************************************************************************************************
 */

template< typename T>
HashMap<T>::HashMap(): size(STARTING_SIZE),used_current_keys(0)
{
    nodePtrArray = new std::shared_ptr<NodeHash<T>>[STARTING_SIZE];
}
template< typename T>
void HashMap<T>::cleanMap(int n_size, std::shared_ptr<NodeHash<T>>* n_nodePtrArray)
{
    //loop and clear all chains in the map
    for (int i = 0; i < n_size; ++i) {
        if(n_nodePtrArray[i] != nullptr)
        {
            std::shared_ptr<NodeHash<T>> temp = n_nodePtrArray[i]->getNext();
            while (temp != nullptr)
            {
                if(temp->getPrev() != nullptr)
                {
                    temp->getPrev()->setNext(nullptr);
                }
                temp->setPrev(nullptr);//disconnect pointer to last
                temp = temp -> getNext();//tend next
            }
        }
        n_nodePtrArray[i]= nullptr;
    }
}
template< typename T>
HashMap<T>::~HashMap()
{
    cleanMap(size, nodePtrArray);
    delete [] nodePtrArray;
}
template< typename T>
int HashMap<T>::decodeKey(int key) {
    // golden value
    double a = (sqrt(5)-1)/2;
    double  temp = a * (double)key;
    double m = (double) size;
    int decoded_key =  (int)(m * (temp - (int)temp));
    //safety check
    if( decoded_key == size)//only if really close to max
    {
        decoded_key--;
    }
    return decoded_key;
}
template< typename T>
std::shared_ptr<NodeHash<T>> HashMap<T>::insert(int key)
{
    //check if already exists
    if(find(key) != nullptr)
    {
        return nullptr;
    }

    //check if need to extend the array
    if(used_current_keys >= size * RESIZE_ON)//TODO needs to check if n = O(m)
    {
        resizeMap(size * RESIZE_ON);
    }

    int decoded_key = decodeKey(key);
    std::shared_ptr<NodeHash<T>> node(new NodeHash<T>(key));
    if(nodePtrArray[decoded_key] == nullptr)//if first cell is empty
    {
        node->setPrev(nullptr);
        nodePtrArray[decoded_key] = node;
    }
    else//need to add to chain - add as first
    {
        nodePtrArray[decoded_key]->setPrev(node);
        node->setNext(nodePtrArray[decoded_key]);

        nodePtrArray[decoded_key] = node;
    }
    used_current_keys++;
    return node;
}
template< typename T>
std::shared_ptr<NodeHash<T>> HashMap<T>::find(int key)
{
    int decoded_key = decodeKey(key);
    std::shared_ptr<NodeHash<T>> temp = nodePtrArray[decoded_key];
    while (true)
    {
        if (temp == nullptr)
        {
            return nullptr;
        }
        if(temp->getKey() == key)
        {
            return temp;
        }
        temp = temp->getNext();
    }
}
template< typename T>
bool HashMap<T>::deleteNode(int key)
{
    std::shared_ptr<NodeHash<T>> target = find(key);
    if(target == nullptr)
    {
        return false;
    }

    //need to resize the map
    if(used_current_keys >= STARTING_SIZE && used_current_keys-1 <= size / (RESIZE_ON * 2))
    {
        resizeMap(size / RESIZE_ON);
    }

    int decoded_key = decodeKey(key);
    if(target->getPrev() == nullptr)//if deleting the first in the chain
    {
        if(target->getNext() != nullptr)
        {
            target->getNext()->setPrev(nullptr);
        }
        nodePtrArray[decoded_key] = target->getNext();
    } else//not the first
    {
        std::shared_ptr<NodeHash<T>> next = target->getNext();
        std::shared_ptr<NodeHash<T>> prev = target->getPrev();
        prev->setNext(next);
        if(next != nullptr)
        {
            next->setPrev(prev);
        }
    }

    used_current_keys--;
    return true;
}
template< typename T>
void HashMap<T>::resizeMap(int new_size)
{
    //allocate new array:
    std::shared_ptr<NodeHash<T>>* new_nodePtrArray = new std::shared_ptr<NodeHash<T>>[new_size];
    //save old map
    std::shared_ptr<NodeHash<T>>* old_map = nodePtrArray;
    int old_size = size;

    size = new_size;
    nodePtrArray = new_nodePtrArray;

    //pre reset used_current_keys
    used_current_keys = 0;
    //copy map
    for (int i = 0; i < old_size; ++i) {
        if(old_map[i] != nullptr)
        {
            std::shared_ptr<NodeHash<T>> temp = old_map[i];
            while (temp != nullptr)
            {
                std::shared_ptr<NodeHash<T>> curr = insert(temp->getKey());//insert new node
                curr -> setData(temp->getData());//copy node data
                temp = temp -> getNext();
            }
        }
    }

    //delete old map
    cleanMap(old_size, old_map);
    delete[]  old_map;

    //change to new one
    nodePtrArray = new_nodePtrArray;
}

template< typename T>
void HashMap<T>::printMap() {
    std::cout<<"total vars number: "<< used_current_keys<<"\n";
    std::cout<<"size of array: "<< size <<"\n";
    for (int i = 0; i < size; ++i) {
        std::cout<<"cell "<< i <<": ";
        if(nodePtrArray[i] != nullptr)
        {
            std::shared_ptr<NodeHash<T>> temp = nodePtrArray[i];
            while (temp != nullptr)
            {
                std::cout<< "," << temp->getKey();
                temp = temp -> getNext();//tend next
            }
        } else
        {
            std::cout<< "is empty";
        }
        std::cout<<"\n";
    }
}

template<typename T>
int HashMap<T>::getUsedCurrentKeys() const {
    return used_current_keys;
}

#endif //BOOM2_HASHMAP_H

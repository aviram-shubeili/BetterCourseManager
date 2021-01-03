//
// Created by uri25 on 01/01/2021.
//
#ifndef BOOM2_NODEHASH_H
#define BOOM2_NODEHASH_H
#include <memory>
#include <math.h> // use for sqrt
/**
 * Generic Dynamic HashMap Node using chain Hashing
 */
template< typename T>
class NodeHash {

private:
    int key;
    std::shared_ptr<T> data;
    std::shared_ptr<NodeHash> next;
    std::shared_ptr<NodeHash> prev;

public:

    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    NodeHash<T>(int key);
    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    int getKey();
    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    std::shared_ptr<NodeHash> getNext();
    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    std::shared_ptr<NodeHash> getPrev();
    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    void setNext(std::shared_ptr<NodeHash> new_next);
    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    void setPrev(std::shared_ptr<NodeHash> new_prev);
    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    void setData(std::shared_ptr<T> new_data);
    /**
     * Description:
     *
     * may throw this exceptions:
     *
     *
     */
    std::shared_ptr<T> getData();
};


/*
 * ************************************************************************************************************
 * ************************************************************************************************************
 *                                                 Implementation
 * ************************************************************************************************************
 * ************************************************************************************************************
 */


template<typename T>
NodeHash<T>::NodeHash(int new_key) : key(new_key)
{

}
template<typename T>
int NodeHash<T>::getKey(){
    return key;
}
template<typename T>
std::shared_ptr<NodeHash<T>> NodeHash<T>::getNext() {
    return next;
}
template<typename T>
std::shared_ptr<NodeHash<T>> NodeHash<T>::getPrev() {
    return prev;
}
template<typename T>
void NodeHash<T>::setNext(std::shared_ptr<NodeHash> new_next) {
    next = new_next;
}
template<typename T>
void NodeHash<T>::setPrev(std::shared_ptr<NodeHash<T>> new_prev) {
    prev = new_prev;
}
template<typename T>
void NodeHash<T>::setData(std::shared_ptr<T> new_data)
{
    data = new_data;
}
template<typename T>
std::shared_ptr<T> NodeHash<T>::getData()
{
    return data;
}

#endif //BOOM2_NODEHASH_H

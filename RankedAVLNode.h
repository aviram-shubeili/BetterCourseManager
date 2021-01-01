#ifndef BOOM_AVLNODE_H
#define BOOM_AVLNODE_H


#include "Auxiliaries.h"

/**
 * Assumptions on T:
 *      default constructor
 *      copy constructor
 *      assignment operator
 *      operator <
 *
 * @tparam T
 */
template< typename T>
class RankedAVLNode {
private:
    ThreeKey key;
    std::shared_ptr<T> data;
    std::shared_ptr<RankedAVLNode<T>> father;
    std::shared_ptr<RankedAVLNode<T>> right_son;
    std::shared_ptr<RankedAVLNode<T>> left_son;
    int height;
    bool visited;

public:
    /**
     * Description:
     *      Constructor.
     * T Assumptions:
     *      Copy constructor
     * Exceptions:
     *      std::bad_alloc() - allocation problem
     */
    explicit RankedAVLNode<T>(ThreeKey key, std::shared_ptr<T> data);

    /**
     * Description:
     *      Copy Constructor.
     * T Assumptions:
     *      Copy constructor.
     * Exceptions:
     *      std::bad_alloc() - allocation problem (thrown from T copy ctor)
     *
     */
    RankedAVLNode<T>(const RankedAVLNode<T>& other);

    /**
     * Description:
     *       Assignment Operator - doesnt change place in tree
     * T Assumptions:
     *      Assignment Operator
     *
     * Exceptions:
     *      std::bad_alloc() - allocation problem (thrown from T Assignment operator)
     */
    RankedAVLNode<T>& operator=(const RankedAVLNode<T>& other);

    ~RankedAVLNode<T>() = default;



    /**
     *           Getters And Setters:
     * **********************************************
     */
    std::shared_ptr<RankedAVLNode<T>> getFather() ;

    void setFather(std::shared_ptr<RankedAVLNode<T>> node);

    std::shared_ptr<RankedAVLNode<T>> getLeftSon() ;

    void setLeftSon(std::shared_ptr<RankedAVLNode<T>> node);

    std::shared_ptr<RankedAVLNode<T>> getRightSon() ;

    void setRightSon(std::shared_ptr<RankedAVLNode<T>> node);

    /**
     * Description:
     *     return height of node (assume sons of node is height correct).
     */
    int getHeight() { return height; };

    void setHeight(int new_height);


    std::shared_ptr<T> getData();

    void setData(std::shared_ptr<T> new_data);

    /**
     * Compare keys function.
     */
    ThreeKey getKey() const;
    bool operator<( std::shared_ptr<RankedAVLNode<T>> other);
    bool operator==( std::shared_ptr<RankedAVLNode<T>> other);

    /**
     * Helper boolean for special inorder
     * @param b
     */
    void setVisit(bool b) {
    visited = b;
}    
    bool getVisited() {
    return visited;
}

};

/*
 * ************************************************************************************************************
 * ************************************************************************************************************
 *                                                 Implementation
 * ************************************************************************************************************
 * ************************************************************************************************************
 */

template<typename T>
RankedAVLNode<T>::RankedAVLNode(const RankedAVLNode<T> &other):
        key(other.key),
        data(other.data),
        father(nullptr),
        left_son(nullptr),
        right_son(nullptr),
        height(0),
        visited(false) { }

template<typename T>
RankedAVLNode<T> &RankedAVLNode<T>::operator=(const RankedAVLNode<T> &other) {
    if(this == &other) {
        return *this;
    }
    data = other.data;
    key = other.key;
   // height = other.height;
    return *this;
}


template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLNode<T>::getFather()  {
    return father;
}

template<typename T>
void RankedAVLNode<T>::setFather(std::shared_ptr<RankedAVLNode<T>> node) {
    father = node;
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLNode<T>::getLeftSon()  {
    return left_son;
}

template<typename T>
void RankedAVLNode<T>::setLeftSon(std::shared_ptr<RankedAVLNode<T>> node) {
    left_son = node;
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLNode<T>::getRightSon()  {
    return right_son;
}

template<typename T>
void RankedAVLNode<T>::setRightSon(std::shared_ptr<RankedAVLNode<T>> node) {
    right_son = node;
}

template<typename T>
std::shared_ptr<T> RankedAVLNode<T>::getData() {
    return data;
}

template<typename T>
void RankedAVLNode<T>::setData(std::shared_ptr<T> new_data) {
    data = new_data;
}

template<typename T>
void RankedAVLNode<T>::setHeight(int new_height) {
    height = new_height;
}

template<typename T>
bool RankedAVLNode<T>::operator<(std::shared_ptr<RankedAVLNode<T>> other) {
    if(other == NULL) {
        return false;
    }
    return this->key < other->key;
}

template<typename T>
bool RankedAVLNode<T>::operator==(std::shared_ptr<RankedAVLNode<T>> other) {
    if(other == NULL) {
        return false;
    }
    return this->key == other->key;
}

template<typename T>
ThreeKey RankedAVLNode<T>::getKey() const {
    return key;
}


template<typename T>
RankedAVLNode<T>::RankedAVLNode(ThreeKey key, std::shared_ptr<T> data) :
        key(key),
        data(data),
        father(nullptr),
        right_son(nullptr),
        left_son(nullptr),
        height(0)
{
}


template<typename T>
int getHeight(std::shared_ptr<RankedAVLNode<T>> node)  {
    return node == NULL ?  -1 : node->getHeight();
}


template<typename T>
static bool isLeftSon(std::shared_ptr<RankedAVLNode<T>> son) {
    assert(son->getFather() != NULL);
    return (son->getFather())->getLeftSon() == son;
}

template<typename T>
static int getNumSons(std::shared_ptr<RankedAVLNode<T>> node) {
    int sum = 0;
    if(node->getLeftSon()) {
        sum++;
    }
    if(node->getRightSon()) {
        sum++;
    }
    return sum;
}


#endif //BOOM_AVLNODE_H

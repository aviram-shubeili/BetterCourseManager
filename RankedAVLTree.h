#ifndef BOOM_AVL_H
#define BOOM_AVL_H
#include "RankedAVLNode.h"
#include <iostream>



/*
 * T ==>
 * T = AVL_Tree
 * T = course_node - array of shared_ptr
 * T = lecture_node
 *
 *
 *
 */

template<typename T>
class RankedAVLTree {
private:

    std::shared_ptr<RankedAVLNode<T>> root;
    std::shared_ptr<RankedAVLNode<T>> min_node;

    /**
     * Description:
     *     return BF of node (assume sub tree of node is height correct).
     * T Assumptions:
     *      none
     * Exceptions:
     *      none
     */
    int getBF(std::shared_ptr<RankedAVLNode<T>> node);
    /**
     * Description:
     *     update node Height (assume sub tree of node is height correct).
     * T Assumptions:
     *      none
     * Exceptions:
     *      none
     */
    void updateHeight(std::shared_ptr<RankedAVLNode<T>> node);


    std::shared_ptr<RankedAVLNode<T>> LL(std::shared_ptr<RankedAVLNode<T>> C);
    std::shared_ptr<RankedAVLNode<T>> RR(std::shared_ptr<RankedAVLNode<T>> B);


    void removeNode(std::shared_ptr<RankedAVLNode<T>> v);

    /**
     * Recursive call to clear Tree
     * @param node
     */
    void clearTree(std::shared_ptr<RankedAVLNode<T>> node);
    /**
     * return true if is leaf
     * false if null or not leaf
     * @param node
     * @return
     */
    bool isLeaf(std::shared_ptr<RankedAVLNode<T>> node) const;
    /**
     * return true if node points to the tree`s root
     * @param node
     * @return
     */
    bool isRoot(std::shared_ptr<RankedAVLNode<T>> node) const;

    /**
    * Description:
    *    inserts given node to tree and keep it balanced.
    * T Assumptions:
    *      none
    * Exceptions:
    *
    */
    void insert(std::shared_ptr<RankedAVLNode<T>> new_node, std::shared_ptr<RankedAVLNode<T>> current_root);
    /**
    * Description:
    *    given a root to subtree - this will perform rolls and balance the tree
    * T Assumptions:
    *      none
    * Exceptions:
    *
    */
    std::shared_ptr<RankedAVLNode<T>> balanceTree(std::shared_ptr<RankedAVLNode<T>> current_root);

    /**
    * Description:
    *    inorder on tree
    * T Assumptions:
    *      none
    * Exceptions:
    *       none
    */
    void inOrder(std::shared_ptr<RankedAVLNode<T>> root);

    /**
     * Finding the K'th Element in subTree of node (sorted)
     */
    std::shared_ptr<RankedAVLNode<T>> Select(int k, std::shared_ptr<RankedAVLNode<T>> node);



public:
    /**
     * Default c'tor - creates an empty AVL Tree.
     */
    RankedAVLTree<T>();



    /**
    * Description:
    *    public function to clear the tree
    * T Assumptions:
    *      none
    * Exceptions:
    *       none
    */
    void clearTree() { clearTree(root); }

    /**
     * D'or - destroy Nodes and tree.
     */
    ~RankedAVLTree();

    /**
     * return pointer to the min key node
     * @return
     */
    std::shared_ptr<RankedAVLNode<T>> getMin();
    /**
     * return pointer to the root
     * @return
     */
    std::shared_ptr<RankedAVLNode<T>> getRoot() ;

    // Made for debugging.
    void inOrderPTRS(std::shared_ptr<RankedAVLNode<T>> subroot) {
        if(subroot == nullptr) {
            return;
        }
        inOrderPTRS(subroot->getLeftSon());
        std::cout << subroot.use_count() << "  ";
        inOrderPTRS(subroot->getRightSon());
    }

    // Made for debugging.
    void detailedPrint(std::shared_ptr<RankedAVLNode<int>> root) {
        if(root == nullptr) {
            return;
        }
        detailedPrint(root->getLeftSon());
        std::cout << root->getKey() << " BF: " << getBF(root)
                  << " Height: " << root->getHeight();

        // Check if Root's rank is true value
        std::cout <<  "  || Rank: " << root->rank << "  Rank == subtreeSize : ";
        int realRank = recursiveCalcRank(root);
        if(realRank == root->rank) {
            std::cout << "TRUE";
        }
        else {
            std::cout << "FALSE  RealRank = " << realRank ;
            throw BoomExceptions();
        }


        std::cout <<std::endl;

        detailedPrint(root->getRightSon());
    }

    void detailedPrint() {
        std::cout << "case:\n";
        detailedPrint(root);
        //  std::cout << "\n";
    }

// made for debugging when all we care is the keys
#ifndef NDBUG
    /**
* Description:
*    create a Node containing nullptr data and insert it to the tree
* T Assumptions:
*      none
* Exceptions:
*     std::bad_alloc
*     Invalid Input - if key is invalid
*     NodeAlreadyExists - if key already exists in tree
*/

    void insert(ThreeKey key, int data) { insert(key, nullptr); }
#endif

    /**
  * Description:
  *    create a Node containing data and key and insert it to the tree
  * T Assumptions:
  *      none
  * Exceptions:
  *     std::bad_alloc
  *     NodeAlreadyExists - if key already exists in tree
  */

    void insert(ThreeKey key, std::shared_ptr<T> data);

    /**
  * Description:
  *    remove a node
  * T Assumptions:
  *      none
  * Exceptions:
  *     Invalid Input - if key is invalid
  *     NodeDoesntExist - if key doesnt exists in tree
  */
    void remove(ThreeKey key);


    /**
  * Description:
  *    search for the key node inside subtree node
  * T Assumptions:
  *      none
  * Exceptions:

  */
    std::shared_ptr<RankedAVLNode<T>> find(ThreeKey key, std::shared_ptr<RankedAVLNode<T>> node);
    /**
  * Description:
  *    search for the key node inside the whole tree
  * T Assumptions:
  *      none
  * Exceptions:

  */
    std::shared_ptr<RankedAVLNode<T>> find(ThreeKey key)  { return find(key, root); }

    /**
     * pretty printing with Headline (uses inorder)
     */
    void printTree();


    // RankTree Features
    /**
     * Finding the K'th Element in Tree (sorted)
     * Exceptions:
     *      InvalidInput() if k is not in range of 1 <= k <= num_nodes
     */
    std::shared_ptr<RankedAVLNode<T>> Select(int k);



};



template<typename T>
void RankedAVLTree<T>::updateHeight(std::shared_ptr<RankedAVLNode<T>> node) {
    if(node == nullptr) {
        return;
    }
    node->setHeight(1 + max(getHeight(node->getLeftSon()), getHeight(node->getRightSon())));
}

template<typename T>
int RankedAVLTree<T>::getBF(std::shared_ptr<RankedAVLNode<T>> node) {
    if(node == nullptr) {
        return 0;
    }
    // h(l) - h(r)
    return getHeight(node->getLeftSon()) - getHeight(node->getRightSon());
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::LL(std::shared_ptr<RankedAVLNode<T>> C) {
    std::shared_ptr<RankedAVLNode<T>> A = C->getLeftSon();
    C->setLeftSon(A->getRightSon());
    A->setRightSon(C);
    if(C->getLeftSon()) {
        (C->getLeftSon())->setFather(C);
    }
    A->setFather(C->getFather());
    C->setFather(A);

    C->updateRank();
    A->updateRank();
    // update Heights!

    updateHeight(C);
    updateHeight(A);

    // return the subtree`s new root.
    return A;
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::RR(std::shared_ptr<RankedAVLNode<T>> B) {
    std::shared_ptr<RankedAVLNode<T>> A = B->getRightSon();
    B->setRightSon(A->getLeftSon());
    A->setLeftSon(B);
    if(B->getRightSon()) {
        (B->getRightSon())->setFather(B);
    }
    A->setFather(B->getFather());
    B->setFather(A);

    // update Ranks!
    B->updateRank();
    A->updateRank();
    // update Heights!
    updateHeight(B);
    updateHeight(A);


    // return the subtree`s new root.
    return A;
}

template<typename T>
void RankedAVLTree<T>::clearTree(std::shared_ptr<RankedAVLNode<T>> node) {
    if(node == nullptr) {
        return;
    }
    // post order deleting
    clearTree(node->getLeftSon());
    clearTree(node->getRightSon());
    if(node == root) {
        root = nullptr;
    }
    if(node == min_node) {
        min_node = nullptr;
    }
    // im a leaf
    if(node->getFather() != nullptr) {
        if(isLeftSon(node)) {
            node->getFather()->setLeftSon(nullptr);
        }
        else {
            node->getFather()->setRightSon(nullptr);
        }
    }
    node->setFather(nullptr);
}

template<typename T>
bool RankedAVLTree<T>::isLeaf(std::shared_ptr<RankedAVLNode<T>> node) const {
    if(node == nullptr) {
        return false;
    }
    return node->getLeftSon() == nullptr and node->getRightSon() == nullptr;
}

template<typename T>
bool RankedAVLTree<T>::isRoot(std::shared_ptr<RankedAVLNode<T>> node) const {
    return node == root;
}

template<typename T>
RankedAVLTree<T>::RankedAVLTree() :
        root(nullptr),
        min_node(nullptr) {}

template<typename T>
RankedAVLTree<T>::~RankedAVLTree() {
    clearTree(root);
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::getMin() {
    return min_node;
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::getRoot() {
    return root;
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::find(ThreeKey key, std::shared_ptr<RankedAVLNode<T>> node) {

    if(node == nullptr or node->getKey() == key) {
        return node;
    }
    // search in left or right sub tree according to compare.
    return (node->getKey() < key) ? find(key,node->getRightSon()) : find(key,node->getLeftSon());

}

template<typename T>
void RankedAVLTree<T>::insert(ThreeKey key, std::shared_ptr<T> data) {

    // node with same key already in the tree
    if(root != nullptr and find(key,root) != nullptr) {
        throw NodeAlreadyExists();
    }
    // T will be copied to RankedAVLNode
    std::shared_ptr<RankedAVLNode<T>> new_node = std::shared_ptr<RankedAVLNode<T>>(new RankedAVLNode<T>(key, data));
    // empty tree
    if(root == nullptr) {
        root = new_node;
        min_node = new_node;
        return;
    }
    // update min_node ptr.
    if(min_node->getKey() > new_node->getKey()) {
        min_node = new_node;
    }
    insert(new_node,root);

}

template<typename T>
void RankedAVLTree<T>::insert(std::shared_ptr<RankedAVLNode<T>> new_node, std::shared_ptr<RankedAVLNode<T>> current_root) {


    // new_node should be placed in the left subtree
    if(new_node->getKey() < current_root->getKey()) {
        if(current_root->getLeftSon() != nullptr) {
            // keep searching for a place in left subtree
            insert(new_node, current_root->getLeftSon());
        }
        else {
            // there is no left subtree --> insert new_node
            current_root->setLeftSon(new_node);
            new_node->setFather(current_root);
        }
    }

        // new_node should be placed in the right subtree
    else {
        if(current_root->getRightSon() != nullptr) {
            // keep searching for a place in right subtree
            insert(new_node, current_root->getRightSon());
        }
        else {
            // there is no right subtree --> insert new_node
            current_root->setRightSon(new_node);
            new_node->setFather(current_root);
        }
    }

    // Done with insertion!

    balanceTree(current_root);
    // update Rank and Height on the insertion path.
    current_root->updateRank();
    updateHeight(current_root);
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::balanceTree(std::shared_ptr<RankedAVLNode<T>> current_root) {

    int bf = getBF(current_root);
    if(bf > 1) {
        if(getBF(current_root->getLeftSon()) == -1) {
            current_root->setLeftSon(RR(current_root->getLeftSon()));
        }
        // current root has a father
        if(current_root != root) {
            // current root is left son of father
            if(current_root == (current_root->getFather())->getLeftSon()) {
                std::shared_ptr<RankedAVLNode<T>> temp = current_root->getFather();
                temp->setLeftSon(LL(current_root));
            }

                // current root is right son of father
            else {
                std::shared_ptr<RankedAVLNode<T>> temp = current_root->getFather();
                temp->setRightSon(LL(current_root));
            }
        }
            // current root is the whole tree root
        else {
            root = LL(current_root);
        }
    }
    else if (bf < -1) {
        if(getBF(current_root->getRightSon()) == 1) {
            current_root->setRightSon(LL(current_root->getRightSon()));
        }
        // current root has a father
        if(current_root != root) {

            // current root is right son of father
            if(current_root == (current_root->getFather())->getRightSon()) {
                std::shared_ptr<RankedAVLNode<T>> temp = current_root->getFather();
                temp->setRightSon(RR(current_root));
            }
                // current root is left son of father
            else {
                std::shared_ptr<RankedAVLNode<T>> temp = current_root->getFather();
                temp->setLeftSon(RR(current_root));
            }
        }

            // current root is the whole tree root
        else {
            root = RR(current_root);
        }
    }

    // bf is fixed (or never had to be fixed)
    return current_root;
}

template<typename T>
void RankedAVLTree<T>::inOrder(std::shared_ptr<RankedAVLNode<T>> root) {
    if(root == nullptr) {
        return;
    }
    inOrder(root->getLeftSon());
    std::cout << root->getKey() << "  ";
    inOrder(root->getRightSon());

}

template<typename T>
void RankedAVLTree<T>::printTree() {
    std::cout << "Tree print: ";
    inOrder(root);
    std::cout << std::endl;
}



template<typename T>
void RankedAVLTree<T>::remove(ThreeKey key) {

    std::shared_ptr<RankedAVLNode<T>> v = find(key, root);

    // node doesnt exist in the tree
    if(v == nullptr) {
        throw NodeDoesntExist();
    }

    removeNode(v);
}

template<typename T>
void RankedAVLTree<T>::removeNode(std::shared_ptr<RankedAVLNode<T>> v) {
    if(isLeaf(v)) {
        // v != root
        if(v->getFather() != nullptr) {
            if(isLeftSon(v)) {
                v->getFather()->setLeftSon(nullptr);
            }
            else {
                v->getFather()->setRightSon(nullptr);
            }
            std::shared_ptr<RankedAVLNode<T>> A = v->getFather();
            // balancing and updating rank and height in deletion path.
            while(A) {
                balanceTree(A);
                A->updateRank();
                updateHeight(A);
                A = A->getFather();
            }

        }
            // v == root
        else {
            root = nullptr;
        }
        if(v == min_node) {
            min_node = v->getFather();
        }

    }
    else if(getNumSons(v) == 1) {
        std::shared_ptr<RankedAVLNode<T>> son = (v->getLeftSon()) ? v->getLeftSon() : v->getRightSon();
        //    v == min_node --> son is v->rightSon
        if(v == min_node) {
            // getting the minimal bigger than v
            std::shared_ptr<RankedAVLNode<T>> new_min = son;
            while(new_min->getLeftSon()) {
                new_min = new_min->getLeftSon();
            }
            // setting new minimum.
            min_node = new_min;
        }
        if(v == root) {
            root = son;
        }
        else {
            // i have a father
            if(isLeftSon(v)) {
                // im its left son
                v->getFather()->setLeftSon(son);
            }
                // im its right son
            else {
                v->getFather()->setRightSon(son);

            }
        }
        son->setFather(v->getFather());
        std::shared_ptr<RankedAVLNode<T>> A = v->getFather();
        // balancing and updating rank and height in deletion path.
        while(A) {
            balanceTree(A);
            A->updateRank();
            updateHeight(A);
            A = A->getFather();
        }
    }
    else {
        // find smallest bigger
        std::shared_ptr<RankedAVLNode<T>> w = v->getRightSon();
        while(w->getLeftSon()) {
            w = w->getLeftSon();
        }
        *v = *w;
        removeNode(w);
    }
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::Select(int k) {
    if( k <= 0 or k > getRank(root)) {
        throw InvalidInput();
    }
    return Select(k,root);
}

template<typename T>
std::shared_ptr<RankedAVLNode<T>> RankedAVLTree<T>::Select(int k, std::shared_ptr<RankedAVLNode<T>> node) {
    if(getRank(node->getLeftSon()) == k-1) {
        return node;
    }
    if(getRank(node->getLeftSon()) > k-1) {
        return Select(k,node->getLeftSon());
    }
    else {
    // (getRank(node->getLeftSon()) < k-1)
        return Select(k- getRank(node->getLeftSon()) -1, node->getRightSon());
    }
}


#endif //BOOM_AVL_H

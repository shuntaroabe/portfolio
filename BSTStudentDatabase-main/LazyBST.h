/*
a. Shuntaro Steven Abe
b. 2377370
c. sabe@chapman.edu
d. CPSC 350-03
e. PA5

This is the LazyBST that auto balances itself.
*/
#ifndef LAZY_BST_H
#define LAZY_BST_H

#include "TreeNode.h"
#include <cmath>

template <typename T>
class LazyBST{
    public:
				// lecture 17
        LazyBST();
        virtual ~LazyBST();
        bool iterContains(T d);
        bool contains(T d); // recursive version that uses recContainsHelper
        void printInOrder(); // least to greatest
        T* arrayPlace();
        void printTreePostOrder(); // left tree then right tree then root
				// lecture 18
        void insert(T d);
        void insertNoBalance(T d);
        bool checkImbalance();
        int size();
        T max(); // right most child
        T* min(); // left most child
        T median(); // will only work if tree is balanced
        // lecture 19
        void remove (T d);
        int height(TreeNode<T>* node);
        int leftHeight(TreeNode<T>* node);
        int rightHeight(TreeNode<T>* node);
        void restructure();
        void deleteTree(TreeNode<T>* node);
        TreeNode<T>* getRoot();
        T* get(int id);
        T* getHelper(TreeNode<T>* n, int id);

    private:
				// lecture 17
        TreeNode<T>* m_root;
        int m_size;
        bool recContainsHelper(TreeNode<T>* n, T d);
        void printIOHelper(TreeNode<T>* n);
        void arrayPlaceHelper(TreeNode<T>* n,T* array, int& index);
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
				// lecture 18
        void insertHelper(TreeNode<T>*& subTreeRoot, T& d);
        T getMaxHelper(TreeNode<T>* n);
        T* getMinHelper(TreeNode<T>* n);
            // lecture 19
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor (TreeNode<T>* rightChild);
        void restructureHelper(LazyBST<T>& tree,T* array, int start, int end);

};



    // ***************************************************************** //
    // ****************** LECTURE  17 ********************************** //
    // ***************************************************************** //


   template <typename T>
        LazyBST<T>::LazyBST(){
        m_root = NULL;
        m_size = 0;
    }

    template <typename T>
    LazyBST<T>::~LazyBST(){
        // TO DO: free up all memory
        deleteTree(m_root);
    }


    // how do we find whether or not a tree contains a key?
        // navigate through the tree until we find it
        // well it's not linear and each node has a left and right child potentially so...

        // let's say we are at the root and we assume the root is not null
        // how do we know if the tree contains "d"?
        // let's try iteratively
    template <typename T>
    bool LazyBST<T>::iterContains(T d){
        if (m_root == NULL){ // tree is empty
            return false;
        }
        if (m_root -> data == d){ // root is the key d
            return true;
        }

        // look for d
        bool found = false;
        TreeNode<T>* current = m_root;
        while (!found){
            // check if d is greater than current go right
            if (d > current -> m_data){
                current = current -> m_right;
            } else { // if d is less than/ == current go left
                current = current -> m_left;
            }
            // check if current node is NULL -> we've reached a leaf and d was not found
            if (current == NULL){
                found =  false;
                break;
            }

            // check if the current node's data is d -> we found d
            if (current -> m_data == d){
                found = true;
            }
        }
        return found;
    }

    // RECURSIVE CONTAINS
    template <typename T>
    bool LazyBST<T>::contains(T d){
        return recContainsHelper(m_root, d);
    }

    // RECURSIVE CONTAINS HELPER
    template <typename T>
    bool LazyBST<T>::recContainsHelper( TreeNode<T>* n, T d){
        if (n == NULL){ // if it is null then d is not in tree
            return false;
        }
        if (n -> m_data == d) { // if it is not null, is it here?
            return true;
        }
        if (d > n -> m_data){ // it's not null but it's also not here, check if it is > or <
            return recContainsHelper( n -> m_right, d);
        } else {
            return recContainsHelper( n -> m_left, d);
        }
    }

    template <typename T>
    void LazyBST<T>::printInOrder(){
        printIOHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printIOHelper(TreeNode<T>* n){
        if (n != NULL){ // is the node null?
            printIOHelper(n -> m_left); // if not then print the left thing
            std::cout << n -> m_data << std::endl; // then print the key of the curr node
            printIOHelper(n -> m_right); // then print the right thing
        }
    }

    //this places the bst in array form
    template <typename T>
    T* LazyBST<T>::arrayPlace(){
      if(m_size == 0){
        std::cout << "Tree Empty!" << std::endl;
        return nullptr;
      }
      else{
        T* array = new T[m_size];
        int index = 0;
        arrayPlaceHelper(m_root, array, index);
        return array;
      }
    }
    //helper method for arrayPlace
    template <typename T>
    void LazyBST<T>::arrayPlaceHelper(TreeNode<T>* n, T* array, int& index){
        if (n != NULL){
            arrayPlaceHelper(n -> m_left,array,index);
            array[index++] = n->m_data;
            arrayPlaceHelper(n -> m_right,array,index);
        }
    }

    template <typename T>
    void LazyBST<T>::printTreePostOrder(){
        printTreePostOrderHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
        if(subTreeRoot != NULL){
            printTreePostOrderHelper(subTreeRoot->m_left);
            printTreePostOrderHelper(subTreeRoot->m_right);
            std::cout << subTreeRoot->m_data << std::endl;
        }
    }

    // ***************************************************************** //
    // ****************** LECTURE  18 ********************************** //
    // ***************************************************************** //
    //old insert function
    template <typename T>
    void LazyBST<T>::insertNoBalance(T d){
      insertHelper(m_root, d);
      ++m_size;
    }
    // inserts, but checks for imbalance after insertion and restructures if needed
    template <typename T>
    void LazyBST<T>::insert(T d){
      insertHelper(m_root, d);
      ++m_size;


      if(checkImbalance()){
        //std::cout << "Imbalance found after inserting " << d << std::endl;
        std::cout << "root before restruc" << std::endl;
        std::cout << m_root->m_data << std::endl;
        restructure();
        std::cout << "root after restruc" << std::endl;
        std::cout << m_root->m_data << std::endl;
        //double leftHeightVal = static_cast<double>(leftHeight(m_root));
        //double rightHeightVal = static_cast<double>(rightHeight(m_root));
        //std::cout << "Left height after restructure: " << leftHeightVal << std::endl;
        //std::cout << "Right height after restructure: " << rightHeightVal << std::endl;
      }
      //std::cout << d << "was inserted. " << std::endl;
    }

    //checks right and left height, and returns true if imbalanced.
    template <typename T>
    bool LazyBST<T>::checkImbalance(){
      if(m_root == NULL){
        return false;
      }
      double leftHeightVal = static_cast<double>(leftHeight(m_root));
      double rightHeightVal = static_cast<double>(rightHeight(m_root));
      double balanceFactor;

      if(leftHeightVal == 0 && rightHeightVal == 0){
        balanceFactor = 1.0;
      }
      else if(leftHeightVal == 0){
        balanceFactor = rightHeightVal;
      }
      else if(rightHeightVal == 0){
        balanceFactor = leftHeightVal;
      }
      else{
        balanceFactor = std::max(leftHeightVal, rightHeightVal) / std::min(leftHeightVal, rightHeightVal);
      }

      //std::cout << "leftdouble = " << leftHeightVal << std::endl;
      //std::cout << "rightdouble = " << rightHeightVal << std::endl;
      //std::cout << "balance factor = " << balanceFactor << std::endl;
      return balanceFactor >= 1.5;
    }
    // INSERT HELPER SO WE DO NOT HAVE TO PASS IN ROOT
    // pass in by reference so that you don't have to manually mess with pointers (r & l children)
    template <typename T>
    void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, T& d){
        if(subTreeRoot == NULL){
            subTreeRoot =  new TreeNode<T>(d); // insert here  & stop recursive call
        } else if(d > subTreeRoot->m_data){
            insertHelper(subTreeRoot->m_right, d);

        } else{ // Less than or = to so we will have repeats in this tree.
								// Some say duplicates are not allowed in trees but you can alternatively
								// choose whether to put them to left or right as long as you're consistent
            insertHelper(subTreeRoot->m_left, d);
        }
    }

    // HELPER METHODS

    // GET SIZE
    template <typename T>
    int LazyBST<T>::size(){
       return m_size;
    }


    // GET MAX
    template <typename T>
    T LazyBST<T>::max(){
       return getMaxHelper(m_root);
    }

    template <typename T>
    T LazyBST<T>::getMaxHelper(TreeNode<T>* n){
       if(n -> m_right == NULL){
        return n -> m_data;
       } else {
            return getMaxHelper(n -> m_right);
       }

    }

    // GET MIN
    template <typename T>
    T* LazyBST<T>::min(){
       return getMinHelper(m_root);
    }

    template <typename T>
    T* LazyBST<T>::getMinHelper(TreeNode<T>* n){
      if(n==nullptr){
        return nullptr;
      }
      else if(n->m_left == nullptr){
        return &(n->m_data);
      }
      else{
        return getMinHelper(n->m_left);
      }
    }


    // GET MEDIAN - ONTY WORKS IF TREE IS BALANCED!
    template <typename T>
    T LazyBST<T>::median(){
        //check if empty we assume it is a non-empty tree
        return m_root->m_data;
    }

    // ***************************************************************** //
    // ****************** LECTURE  19 ********************************** //
    // ***************************************************************** //

    // HELPER METHODS
    template <typename T>
    void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
        // FIND THE NODE WE WANT TO DELETE AND ITS PARENT NODE
        while (target != NULL && target -> m_data != key){ // while target still has children and it is not our actual target
            parent = target;
            if (key < target -> m_data){ // if the key is less than the current target node, keep going left
                target = target -> m_left;
            } else {
                target = target -> m_right;
            }
        }
    }

    template <typename T>
    TreeNode<T>* LazyBST<T>::getSuccessor (TreeNode<T>* rightChild){
        while (rightChild -> m_left != NULL){ // If the node coming in (rightChild) doesn't have a left child then this is our successor and we're done, else:
            rightChild = rightChild -> m_left;
        }
        return rightChild; // not really (necessarily) a right child, this is the successor!
    }

    //same old, but checks for imbalance after removing and rebalances as needed
    template <typename T>
    void LazyBST<T>::remove(T d){
        //std::cout << "remove called" << std::endl;
        // check if tree is empty
        // we assume the tree is non-empty
        TreeNode<T>* target = NULL;
        TreeNode<T>* parent = NULL;
        target = m_root;

        // find the target
        findTarget(d, target, parent); // no need save under any variables, target and parent are redefined bc we passed them in by reference

        // target value was not found - it does not exist in our tree
        if (target == NULL){
            return;
        }

        // SCENARIO 1: TARGET IS A LEAF (INCLUDING ROOT)
        //std::cout << "went to scen1 b4" << std::endl;
        if (target -> m_left == NULL && target -> m_right == NULL){
            if (target == m_root){
                m_root = NULL;
            } else { // if it's a leaf but not the root
                // check if target is its parent's left or right child
                if (target == parent -> m_left){ // if target is a left child
                    parent -> m_left = NULL;
                } else { // target is a right child
                    parent -> m_right = NULL;
                }
            }
            delete target;
						-- m_size;
            //std::cout << "went to end of scen1" << std::endl;
        }

        // SCENARIO 3: TARGET HAS TWO CHILDREN
        else if (target -> m_left != NULL && target -> m_right != NULL){  // both children pointers are not null
            TreeNode<T>* suc = getSuccessor(target -> m_right);
            T value = suc -> m_data;
            remove(value); // goes in the BST remove method and removes the node w/ d = value
            target -> m_data = value;
        }

        // SCENARIO 2: TARGET HAS 1 CHILD
        else {
            TreeNode<T>* child;
            // check whether target has a left or right child
            if (target -> m_left != NULL){ // target has a left child
                child = target -> m_left;
            } else{                        // target has a right child
                child = target -> m_right;
            }

            if (target == m_root){
                m_root = child;
            } else {
                if (target == parent -> m_left){ // our target is a left child
                    parent -> m_left = child; // make the parent's left child the target's child
                } else {                       // our target is a right child
                    parent -> m_right = child; // make the parent's right child the target's child
                }
            }
						target -> m_left = NULL;
						target -> m_right = NULL;

            delete target;
						-- m_size;
        }
       //  --m_size; // TAKE AWAY FROM HERE

      //std::cout << "went to checkImbalance" << std::endl;
       if(checkImbalance()){
         //std::cout << "went to restructure" << std::endl;
         //std::cout << "Imbalance found after removing " << d << std::endl;
         restructure();
         //std::cout << "after restruc" << std::endl;
         //double leftHeightVal = static_cast<double>(leftHeight(m_root));
         //double rightHeightVal = static_cast<double>(rightHeight(m_root));
         //std::cout << "Left height after restructure: " << leftHeightVal << std::endl;
         //std::cout << "Right height after restructure: " << rightHeightVal << std::endl;
       }
       //std::cout << d << "was removed. " << std::endl;
    }
    template <typename T>
    int LazyBST<T>::height(TreeNode<T>* node) {
        if (node == NULL){
          return 0;
        }
        return 1 + std::max(height(node->m_left), height(node->m_right));
    }
    //checks right height
    template <typename T>
    int LazyBST<T>::leftHeight(TreeNode<T>* node) {
      if(node == NULL){
        return 0;
      }
      return height(node->m_left);
    }
    //checks left height
    template <typename T>
    int LazyBST<T>::rightHeight(TreeNode<T>* node) {
      if(node == NULL){
        return 0;
      }
      return height(node->m_right);
    }

    //restructures the BST based on project specification
    template <typename T>
    void LazyBST<T>::restructure(){
      T* TreeArrayAscending = arrayPlace();
      LazyBST<T> newTree;
      restructureHelper(newTree,TreeArrayAscending,0,m_size-1);
      delete[] TreeArrayAscending;
      deleteTree(m_root);
      m_root = newTree.m_root;
      newTree.m_root = nullptr;
      return;
    }

    //helper method for restructure
    template <typename T>
    void LazyBST<T>::restructureHelper(LazyBST<T>& tree,T* array, int start, int end){
      //std::cout << "RestructureHelper called with start: " << start << ", end: " << end << std::endl;
      if(start > end){
        //std::cout << "start > end, base case" << std::endl;
        return;
      }
      int medianIndex = start + (end - start) / 2;
      tree.insertNoBalance(array[medianIndex]);

      restructureHelper(tree,array,start,medianIndex-1);
      restructureHelper(tree,array,medianIndex+1,end);
      return;
    }

    template <typename T>
    void LazyBST<T>::deleteTree(TreeNode<T>* node) {
      if (node != NULL) {
        deleteTree(node->m_right);
        deleteTree(node->m_left);
        delete node;
      }
    }

    template <typename T>
    TreeNode<T>* LazyBST<T>::getRoot(){
      return m_root;
    }

    //created this function to easily get students/faculty
    template <typename T>
    T* LazyBST<T>::get(int id){
      return getHelper(m_root, id);
    }

    template <typename T>
    T* LazyBST<T>::getHelper(TreeNode<T>* n, int id){
      if(n == NULL){
        return nullptr;
      }
      if(n->m_data.id == id){
        return &(n->m_data);
      }
      if(id > n->m_data.id){
        return getHelper(n->m_right, id);
      }
      else{
        return getHelper(n->m_left, id);
      }
    }
#endif

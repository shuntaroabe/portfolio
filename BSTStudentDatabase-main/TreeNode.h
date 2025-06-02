/*
a. Shuntaro Steven Abe
b. 2377370
c. sabe@chapman.edu
d. CPSC 350-03
e. PA5

This is TreeNode, which represents each node in a binary tree.
*/
#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode(T d);
  virtual ~TreeNode();
  T getData();
  TreeNode<T>* getLeft();
  TreeNode<T>* getRight();


  template <typename S>
  friend class LazyBST;


private:
  T m_data;
  TreeNode<T>* m_left;
  TreeNode<T>* m_right;

};

template <typename T>
TreeNode<T>::TreeNode(T d){
  m_data = d;
  m_left = NULL;
  m_right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  /*if(m_left != NULL){
    delete m_left;
  }
  if(m_right != NULL){
    delete m_right;
  }*/
}

template <typename T>
T TreeNode<T>::getData(){
  return m_data;
}
template <typename T>
TreeNode<T>* TreeNode<T>::getLeft(){
  return m_left;
}

template <typename T>
TreeNode<T>* TreeNode<T>::getRight(){
  return m_right;
}

#endif

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
#include <string>


/** Starter code for PA1, CSE 100 2016
 * Authors: Christine Alvarado, based on code by Paul Kube 
 * Jaime Velazquez, Nha Do
 */

template<typename Data>
class BSTNode {

public:

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d);


  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor(); 

  /*
   * Helper function to the successor function. 
   */ 
  BSTNode<Data>* successorHelper(BSTNode<Data>* curr);
}; 


// Function definitions
// For a templated class it's easiest to just put them in the same file as the class declaration

template <typename Data>
BSTNode<Data>::BSTNode(const Data & d) : data(d), left(0), right(0), parent(0) {}

/* Return a pointer to the BSTNode that contains the item that is sequentially next 
 * in the tree */
template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor()
{
  BSTNode<Data>* curr = this;

	std::cout << "this is curr " << curr->data << "\n";
//	std::cout << "this is curr-> parent: " << curr->parent->data << "\n";
  if (curr->right){
	std::cout << "Inside curr->right, in successor\n";
     return successorHelper(curr->right);
  }
  //if (curr->right == NULL){
//	std::cout << "Inside parent and right child dont exist\n";
//     return 0;   // parent nor right child exist, no successor
//  }

  BSTNode<Data>* parentTmp = curr->parent;
  while (parentTmp && curr == parentTmp->right){
     curr = parentTmp;
     parentTmp = parentTmp->parent;
  }
  //std::cout << "returning parentTmp: " << parentTmp->data << "\n";
  return parentTmp;
}

template <typename Data>
BSTNode<Data>* BSTNode<Data>::successorHelper(BSTNode<Data>* curr){
  BSTNode<Data>* tmp = curr;
  
  while (tmp->left){
    tmp = tmp->left;  // Gets the leftmost node 
  }
  return tmp;

}

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP

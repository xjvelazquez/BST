#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
#include <ios>

template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator 
   *  pointing to either the newly inserted element or the element 
   *  that was already in the BST, and the second element is true if the 
   *  element was newly inserted or false if it was already in the BST.
   * 
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const;
  
  /** Return the height of the BST.
      height of a tree starts with root at height 0
	  height of an empty tree is -1
   */ 
   int height() const;


  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */ 
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;

  /** Private helper method for to find the height of a tree. */
  int heightHelper(BSTNode<Data>* root) const;


private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;
  
  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Find the first element of the BST
   * Helper function for the begin method above.
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);
 };


// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the newly inserted
 *  element or the element that was already in the BST, and the second element is true if the 
 *  element was newly inserted or false if it was already in the BST.
 * 
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) { 
  bool secondTmp;  // bool return value
 
  if (!root) { // Root case
    root = new BSTNode<Data>(item);
    ++isize;
    secondTmp = true;
    BSTIterator<Data> iteratorRoot(root);
    std::pair<BSTIterator<Data>, bool> returnPairRoot(iteratorRoot, secondTmp);
    return returnPairRoot;
  }

  BSTNode<Data>* curr = root;
  
  while (curr) {
    if (item < curr->data) { // If item has value less than curr node's.
      if (curr->left){
	curr = curr->left; // Continues with the left child
      }
      else{
	break;	// item < curr->data, but left child DNE.
      }
    }
    else if (curr->data < item) { // If item has value greater than curr node's
      if (curr->right){
	curr = curr->right; // Continues with the right child
      }
      else{
	break; // curr->data < item, but right child DNE.
      }
    }
    else {
       BSTIterator<Data> iteratorCurr(curr);
       secondTmp = false;  // Item == curr->data
       std::pair<BSTIterator<Data>, bool> returnPairCurr(iteratorCurr,secondTmp);
       return returnPairCurr;
    }
  }

  // Ready to insert
  BSTNode<Data>* newNode = new BSTNode<Data>(item);
  if (item < curr->data) {
    curr->left = newNode;
    newNode->parent = curr;
  }
  else if (curr->data < item){
    curr->right = newNode;
    newNode->parent = curr;
  }	
  else{
    //return false;
  }

  BSTIterator<Data> iteratorEnd(newNode);
  secondTmp = true;
  std::pair<BSTIterator<Data>, bool> returnPairEnd(iteratorEnd,secondTmp);

  ++isize;
  return returnPairEnd;
}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  BSTNode<Data>* curr = root;
  while (curr) {
    if (curr->data < item) {
      curr = curr->right; // Continues to the right child.
    }
    else if (item < curr->data) {
      curr = curr->left;  // Continues to the left child
    }
    else {
      BSTIterator<Data> returnIterator(curr); // Is found
      return returnIterator;
    }
  }
  return BSTIterator<Data>(nullptr);

}

  
/** Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}


/** Return the height of the BST.
 */
template <typename Data> 
int BST<Data>::height() const
{
  if (isize == 0){
     return -1; // Empty tree
  }
  
  if (isize == 1){
     return 0; // Only root node
  }
  int height = heightHelper(root);
  return height;
}


/* Helper function that gets the height of a tree */
template <typename Data> 
int BST<Data>::heightHelper(BSTNode<Data>* root) const{
  if (root){
   int maxHeight = std::max(heightHelper(root->left),heightHelper(root->right));
   return 1 + maxHeight;
  }
  else{
     return -1;
  }
}

/** Return true if the BST is empty, else false.
 */ 
template <typename Data>
bool BST<Data>::empty() const
{
  if (isize == 0){
     return true;
  }
  return false;
}


/** Return an iterator pointing to the first (smallest) item in the BST.
 */ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  BSTNode<Data>* curr = root;
  while (curr->left){
     curr = curr->left;
  }
  return curr;
}

/** do a postorder traversal, deleting nodes
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
  if (!n){
     return;
  }
  // If left child exists, recursive call on left child
  if (n->left){
     deleteAll(n->left);
  }
  // If right child exists, recursive call on right child
  if (n->right){
     deleteAll(n->right);
  }
  // If left and right child are taken care of, deletes current node
  delete n;
  return;
}



#endif //BST_HPP

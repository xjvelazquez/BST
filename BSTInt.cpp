
#include "BSTInt.h"
#include <iostream>

using namespace std;

/* Function definitions for a int-based BST class */


/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
  if (!root) {
    root = new BSTNodeInt(item);
	cout << "Creates root node: "<< root << endl;
    ++isize;
    return true;
  }

  BSTNodeInt* curr = root;
  
  while (curr) {
    if (item < curr->data) {
      if (curr->left){
	curr = curr->left; // Continues with the left child
      }
      else{
	break;	// item < curr->data, but left child DNE.
      }
    }
    else if (curr->data < item) {
      if (curr->right){
	curr = curr->right; // Continues with the right child
      }
      else{
	break;	// curr->data < item, but right child DNE.
      }
    }
    else {
      return false;  // Item == curr->data
    }
  }

  // Ready to insert
  BSTNodeInt* newNode = new BSTNodeInt(item);
  if (item < curr->data) {
	cout << "if in insert" << endl;
	cout << "This is curr->data: " << curr->data << endl;
	cout << "This is item: " << item << endl;
    curr->left = newNode;
    newNode->parent = curr;
  }
  else if (curr->data < item){
	cout << "else if in insert" << endl;
	cout << "This is curr->data: " << curr->data << endl;
	cout << "This is item: " << item << endl;
    curr->right = newNode;
    newNode->parent = curr;
  }	
  else{
	cout << "else in insert" << endl;
    return false;
  }

  ++isize;
  return true;

}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
  BSTNodeInt* curr = root;
  while (curr) {
    if (curr->data < item) {
      curr = curr->right; // Continues to the right child.
    }
    else if (item < curr->data) {
      curr = curr->left;  // Continues to the left child
    }
    else {
      return true; // Is found
    }
  }
  return false;
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
  return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
    height of an empty tree is -1
 */
int BSTInt::height() const
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

int BSTInt::heightHelper(BSTNodeInt* root) const{
  if (root){
     return 1 + max(heightHelper(root->left),heightHelper(root->right));
  }
  else{
     return -1;
  }
}


/** Return true if the BST is empty, else false. 
 */
bool BSTInt::empty() const 
{
  if (isize == 0){
     return true;
  }
  return false;
}




/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt* n)
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

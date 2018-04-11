#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2016
 * Author: Christine Alvarado and YOU
 * TODO: Add more tests
 */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);


    vector<int> z;
    z.push_back(10);
    z.push_back(7);
    z.push_back(12);
    z.push_back(9);
    z.push_back(17);
    z.push_back(19);
    z.push_back(21);
    z.push_back(20);


    /* Create an instance of BST holding int */
    BSTInt b;
    BSTInt c; // Empty 
    BSTInt d; // Complex BST

    // Could use: for(auto item : v) { instead of the line below
    for(int item : v) {
        bool pr = b.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item 
                 << endl;
            return -1;
        }
    }

    for(int item2 : z) {
	bool pr2 = d.insert(item2);
	if(!pr2){
	    cout << "Incorrect bool return value when inserting " << item2
		<< endl;
	    return -1;
	}
    }


    /* Test size. */
    cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
        cout << "... which is incorrect." << endl;
        return -1;
    }

    /* Test find return value. */
    // Test the items that are already in the tree
    for(int item : v) {
        if(!b.find(item)) {
            cout << "Incorrect return value when finding " << item << endl;
            return -1;
        }
    }

    // Test for find, value that is not in the BST
    if (b.find(2)){
	cout << "Incorrect" << endl;
	return -1;
    }

    // Test for insert, trys to add value already in BST
    int num = 100;
    bool result = b.insert(num);
    if (result){
	cout << "Incorrectly adds repeated value: " << num << endl;
	return -1;
    }
    else{
	cout << "Correctly catches repeated value, does not insert" << endl;
    }

    // Test for insert, trys to add value already in BST
    num = -33;
    result = b.insert(num);
    if (result){
	cout << "Incorrectly adds repeated value: " << num << endl;
	return -1;
    }
    else{
	cout << "Correctly catches repeated value, does not insert" << endl;
    }

    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

    /*
    // Test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;

    */

    // ADD MORE TESTS HERE.  You might also want to change what is input
    // into the vector v.
    
    // Test for the height 
    int height = b.height();
    if (height != 2){
 	cout << "Test failed! Incorrect height: " << height << endl;
	return -1;
    }
    else{
	cout << "Correct! Height is: " << height << endl;
    }


    // Testing empty BST for height
    int height2 = c.height();
    if (height2 != -1){
 	cout << "Test failed! Incorrect height: " << height2 << endl;
	return -1;
    }
    else{
	cout << "Correct! Height is: " << height2 << endl;
    }

    // Testing height for more complex BST
    int height3 = d.height();
    if (height3 != 5){
 	cout << "Test failed! Incorrect height: " << height3 << endl;
	return -1;
    }
    else{
	cout << "Correct! Height is: " << height3 << endl;
    }

    // Testing empty() 
    bool result2 = c.empty();
    if (result2){
	cout << "Correct!" << endl; // BST is empty
    }
    else{
	cout << "Incorrect!" << endl;
	return -1;
    }


    cout << "All tests passed!" << endl;
    return 0;
}

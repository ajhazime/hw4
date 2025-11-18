#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <cmath>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};


/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
		AVLNode<Key, Value>* getRoot() const {
			return (AVLNode<Key, Value>*)this->root_;
		}
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void rotateLeft(AVLNode<Key,Value>* pivot);
		void rotateRight(AVLNode<Key,Value>* pivot);


};

/*
  -----------------------------------------------
  STart implementations for the AVLTree class.
  -----------------------------------------------
*/

template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* pivot){
	AVLNode<Key, Value>* rightChild = pivot->getRight();
	if(rightChild == nullptr){
		return;
	}

	AVLNode<Key, Value>* rightChildLeft = rightChild->getLeft();
	AVLNode<Key, Value>* parent = pivot->getParent();


	//Rotate the node
	rightChild->setLeft(pivot);
	pivot->setParent(rightChild);
	pivot->setRight(rightChildLeft);

	if(rightChildLeft != nullptr){
		rightChildLeft->setParent(pivot);
	}
	//attach 
	rightChild->setParent(parent);
	if(parent == nullptr){
		this->root_ = rightChild;

	} else if (pivot == parent->getLeft()){
		parent->setLeft(rightChild);
	} else { 
		parent->setRight(rightChild);	
	}

	if(rightChild->getBalance() == 0 ){
		pivot->setBalance(1);
		rightChild->setBalance(-1);
	} else {
		pivot->setBalance(0);
		rightChild->setBalance(0);
	}

	return; 
}


template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* pivot){

	AVLNode<Key, Value>* leftChild = pivot->getLeft();
	if(leftChild == nullptr){
		return;
	}

	AVLNode<Key, Value>* leftChildRight = leftChild->getRight();
	AVLNode<Key, Value>* parent = pivot->getParent();


	//Rotate the node
	leftChild->setRight(pivot);
	pivot->setParent(leftChild);
	pivot->setLeft(leftChildRight);

	if(leftChildRight != nullptr){
		leftChildRight->setParent(pivot);
	}
	//attach 
	leftChild->setParent(parent);
	if(parent == nullptr){
		this->root_ = leftChild;

	} else if (pivot == parent->getLeft()){
		parent->setLeft(leftChild);
	} else { 
		parent->setRight(leftChild);	
	}


	if(leftChild->getBalance() == 0){
		pivot->setBalance(-1);
		leftChild->setBalance(1);
	} else {
		pivot->setBalance(0);
		leftChild->setBalance(0);
	}

	return;
}



/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
		if(this->root_ == nullptr){
			this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
			return;
		}


	Node<Key, Value>* currNode = this->root_;
	Node<Key, Value>* parent = nullptr;



	while(currNode != nullptr){

		parent = currNode;


		if(new_item.first == currNode->getKey()){
			currNode->setValue(new_item.second);
			return;
		}
		else if(new_item.first < currNode->getKey()){
			currNode = currNode->getLeft();
		}
		else {
			currNode = currNode->getRight();
		}
	}

	//curr null
	AVLNode<Key, Value>* parentAVLNode = (AVLNode<Key, Value>*) parent; //cast parent as AVLnode* 
	AVLNode<Key, Value>* newAVLNode = new AVLNode<Key, Value>(new_item.first, new_item.second, parentAVLNode);
	//insert new
	if(parent->getKey() < new_item.first){
		parent->setRight(newAVLNode);
	}
	else { 
		parent->setLeft(newAVLNode);
	}

	//balance 
	AVLNode<Key, Value>* childAVLNode = newAVLNode;
	AVLNode<Key, Value>* balanceParent = parentAVLNode;

	//walk up to root
	while(balanceParent != nullptr){
		if(childAVLNode == balanceParent->getLeft()){
			balanceParent->updateBalance(-1); 
		} else {
			balanceParent->updateBalance(1); 
		}
		if(balanceParent->getBalance() == 1 || balanceParent->getBalance() == -1){ //go up 
			childAVLNode = balanceParent;
			balanceParent = balanceParent->getParent();
			continue; // next iter
		}

		if(balanceParent->getBalance() == 2){ //right hevy
			if(balanceParent->getRight()->getBalance() == -1){
				rotateRight(balanceParent->getRight());
			}
			rotateLeft(balanceParent);
		} else if (balanceParent->getBalance() == -2){ //left hevy
			if(balanceParent->getLeft()->getBalance() == 1){
				rotateLeft(balanceParent->getLeft());
			}
			rotateRight(balanceParent);
		}
		break;
	}

	return;
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
		AVLNode<Key, Value>* node = (AVLNode<Key, Value>*)this->internalFind(key);

		if(node == nullptr){
			return;
		}

		if(node->getLeft() != nullptr && node->getRight() != nullptr){
			AVLNode<Key, Value>* predecessor = (AVLNode<Key, Value>*) this->predecessor(node);
			nodeSwap(node, predecessor);
		}

		AVLNode<Key, Value>* child = nullptr;
		if(node->getLeft() != nullptr){
			child = node->getLeft();
		} else {
			child = node->getRight();
		}

	AVLNode<Key, Value>* parent = node->getParent();
	int8_t balanceSum = 0;

	if(child != nullptr){
		child->setParent(parent);
	}

	if(parent == nullptr){
		this->root_ = child;
	} else {
		if(node == parent->getLeft()){
			parent->setLeft(child);
			balanceSum = 1;
		}else {
			parent->setRight(child);
			balanceSum  = -1;		
		}
	}
	delete node;
	


	//rebalance tree 
	AVLNode<Key, Value>* currNode = parent;

	while(currNode != nullptr){
		currNode->updateBalance(balanceSum);

		

		if(currNode->getBalance() == 0){
			AVLNode<Key, Value>* p = currNode->getParent();
			if(p != nullptr){
				if(currNode == p->getLeft()){
					balanceSum = 1;
				} else {
					balanceSum = -1;
				}
			}
			currNode = currNode->getParent();
			continue; // walk up 
		}

		if(currNode->getBalance() == 1 || currNode->getBalance() == -1){
			break;
		}

		if (currNode->getBalance() == -2){
			AVLNode<Key, Value>* l = currNode->getLeft();
			if(l->getBalance() == 1){
				rotateLeft(l);
			}
			rotateRight(currNode);
			break;
		} else if (currNode->getBalance() == 2){
			AVLNode<Key, Value>* r = currNode->getRight();
			if(r->getBalance() == -1){
				rotateRight(r);
			}
			rotateLeft(currNode);
			break;
		}

		AVLNode<Key, Value>* parentNode = currNode->getParent();
		if(parentNode != nullptr){
			if(currNode == parentNode->getLeft()){
				balanceSum = 1;
			} else {
				balanceSum = -1;
			}
		}
		currNode = parentNode;

	}

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif

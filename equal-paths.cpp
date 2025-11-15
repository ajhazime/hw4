#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm> 
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

bool maxDepth(Node* root, int& height){
	if (root == nullptr){
		height = 0;
		return true;
	}


	if( (root->left == nullptr) && (root->right == nullptr) ){
		height = 1;
		return true;
	}

	int leftTH = 0;
	int rightTH = 0;
	bool leftBool = 1;
	bool rightBool = 1;

	if(root->left){
		leftBool = maxDepth(root->left, leftTH);
	}
	if(root->right){
		rightBool = maxDepth(root->right, rightTH);
	}

	height = 1 + max(leftTH, rightTH);

	if(root->right == nullptr || root->left == nullptr){
		return leftBool && rightBool;
	}
	return leftBool && rightBool && (leftTH == rightTH);
}




bool equalPaths(Node * root)
{
	int height = 0;
	return maxDepth(root, height);

}


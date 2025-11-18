#include <iostream>
#include <string>

#include "bst.h"
#include "avlbst.h"


using namespace std;

template<typename Key, typename Value>
void validateAndPrint(AVLTree<Key, Value>& t ){
	std::cout << "AVLVALID?: " << (t.isBalanced() ? " YES " : " NOOOO ") <<std::endl;
}

template<typename Key, typename Value>
void debugTree(AVLTree<Key, Value>& t, const std::string& label){
	cout << "\n\n====== " <<label << "\n====\n\n";
	t.print();
	std::cout << "AVLVALID?: " << (t.isBalanced() ? " YES " : " NOOOO ") <<std::endl;
	std::cout << "============\n\n\n";
}

template<typename Key, typename Value>
bool checkParents(Node<Key, Value>* node){
	if(!node){
		return true;
	}

	if(node->getLeft() && node->getLeft()->getParent() != node){
		cout <<"PARENT ERROR LEFT NODE: " << node->getKey() <<"\n\n";
		return false;
	}

	if(node->getRight() && node->getRight()->getParent() != node){
		cout <<"PARENT ERROR right NODE: " << node->getKey() <<"\n\n";
		return false;
	}
	return checkParents(node->getLeft()) && checkParents(node->getRight());
}	


template<typename Key, typename Value>
void validateAll(AVLTree<Key, Value>& t, std::string label){
	debugTree(t,label);
	cout << "Parents OK?" << (checkParents(t.getRoot()) ? "YES" :"NO") <<endl;
}




int main(){

	

	AVLTree<int, int> t;

	std::cout << "TEST LL Rotation" << '\n' << std::endl;
	t.insert({3,1});
	t.insert({2,1});

	t.insert({1,1});


	std::cout <<"\n\n CLEARING TREE " << std::endl;
	t.clear();
	std::cout <<"\n\n CLEARED TREE \n\n" << std::endl;

	std::cout << "\n\nTEST RR Rotation\n\n" << '\n' << std::endl;
	t.insert({1,1});

	t.insert({2,1});
	t.insert({3,1});


	std::cout <<"\n\n CLEARING TREE " << std::endl;
	t.clear();
	std::cout <<"\n\n CLEARED TREE \n\n" << std::endl;




	std::cout << "\n\nTEST LR Rotation\n\n" << '\n' << std::endl;
	t.insert({3,1});
	t.insert({1,1});
	t.insert({2,1});



	std::cout <<"\n\n CLEARING TREE " << std::endl;
	t.clear();
	std::cout <<"\n\n CLEARED TREE \n\n" << std::endl;


	std::cout << "\n\nTEST RL Rotation\n\n" << '\n' << std::endl;

	t.insert({1,1});
	t.insert({3,1});
	t.insert({2,1});

	std::cout <<"\n\n CLEARING TREE " << std::endl;
	t.clear();
	std::cout <<"\n\n CLEARED TREE \n\n" << std::endl;



	std::cout <<"\n\n\n=== Test More Complex Sequence ===\n ";
	int seq[] = {10,5,15,3,8,7,9,20,25,30,22};
	for(int x: seq){
		std::cout << "INSERTING:" << x << std::endl;
		t.insert({x,1});
	validateAll(t, "After insert: " + std::to_string(x));
	}


	std::cout <<"\n\n\n=====TESTINGREMOVE\n\n" << std::endl;
	int removearr[] = {10,15,5,8,7,30};
	for(int x: removearr){
		cout << "REMOVING: " << x << endl;
		t.remove(x);
	validateAll(t, "After remove: " + std::to_string(x));
	}


	return 0;
}

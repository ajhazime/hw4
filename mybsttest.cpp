#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;

int main(){

	BinarySearchTree<int, int> t;

	std::cout << "tree created" << '\n' << std::endl;
	t.print();

	t.insert({2,1});
	std::cout << "===\n insert 2,1 \n===" << std::endl;
	t.print();
	t.insert({1,1});
	std::cout << "===\n insert 1,1 \n===" << std::endl;
	t.print();
	t.insert({3,1});
	std::cout << "===\n insert 3,1 \n===" << std::endl;
	t.print();
	t.remove(2);
	std::cout << "===\n remove 2 \n==="<< std::endl;;
	t.print();


	return 0;
}

#include "Tree.h"

typedef BinaryTree<int> BTree;

int main()
{
	BTree* bTree = new BTree;
	for (int i = 1; i <= 7; i++)
	{
		int* index = new int;
		*index = *(&i);
		bTree->Insert(BTree::Create(&index));
		/*string* name = new string;
		*name = "string";
		bTree->Insert(BTree::Create(&name));*/
	}
}
#include "Tree.h"

//typedef BinaryTree<int> BTree;
typedef BinaryTree<string> BTree;

int main()
{
	BTree* bTree = new BTree;
	//for (int i = 1; i <= 7; i++)
	//{
	//	int* index = new int;
	//	*index = *(&i);
	//	bTree->InsertNode(BTree::Create(&index));
	//	/*string* name = new string;
	//	*name = "string";
	//	bTree->InsertNode(BTree::Create(&name));*/
	//}

	/*int* index = new int;
	*index = 5;
	bTree->InsertNode(BTree::Create(&index));

	index = new int;
	*index = 2;
	bTree->InsertNode(BTree::Create(&index));
	
	index = new int;
	*index = 7;
	bTree->InsertNode(BTree::Create(&index));

	index = new int;
	*index = 1;
	bTree->InsertNode(BTree::Create(&index));

	index = new int;
	*index = 3;
	bTree->InsertNode(BTree::Create(&index));

	index = new int;
	*index = 6;
	bTree->InsertNode(BTree::Create(&index));
	
	index = new int;
	*index = 8;
	bTree->InsertNode(BTree::Create(&index));

	bTree->PrintTree(TreeOrder::Preorder);
	bTree->PrintTree(TreeOrder::Inorder);
	bTree->PrintTree(TreeOrder::Postorder);

	bTree->RemoveAll();*/

	string* name = new string;
	*name = "g";
	bTree->InsertNode(BTree::Create(&name));

	name = new string;
	*name = "b";
	bTree->InsertNode(BTree::Create(&name));

	name = new string;
	*name = "a";
	bTree->InsertNode(BTree::Create(&name));

	name = new string;
	*name = "c";
	bTree->InsertNode(BTree::Create(&name));

	name = new string;
	*name = "y";
	bTree->InsertNode(BTree::Create(&name));

	name = new string;
	*name = "i";
	bTree->InsertNode(BTree::Create(&name));

	name = new string;
	*name = "h";
	bTree->InsertNode(BTree::Create(&name));

	name = new string;
	*name = "g";
	bTree->RemoveNode(name);

	bTree->PrintTree(TreeOrder::Preorder);
	bTree->PrintTree(TreeOrder::Inorder);
	bTree->PrintTree(TreeOrder::Postorder);

	bTree->RemoveAll();


	
	cout << "end" << endl;
}
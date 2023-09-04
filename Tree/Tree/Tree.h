#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum TreeOrder
{
	Preorder,
	Inorder,
	Postorder,
	Levelorder,
	Max
};

template<typename T>
class BinaryTree
{
public:
	struct Node;

public:
	static Node* Create(T** data)
	{
		Node* node = new Node();
		node->Data = *data;
		node->Left = NULL;
		node->Right = NULL;

		return node;
	}

public:
	void InsertNode(Node* InNode)
	{
		if (m_RootNode == NULL)
		{
			m_RootNode = InNode;
			cout << "Insert Node Succse!" << endl;

			return;
		}

		Insert(InNode, m_RootNode);
	}

	void RemoveNode(T* InData)
	{
		if (m_RootNode == NULL)
		{
			return;
		}

		Node* remove = Remove(m_RootNode, InData);
		if (remove == NULL)
		{
			cout << "Remove Node Fail!" << endl;
			return;
		}
		cout << "Remove Node Succes!" << endl;
	}

	void RemoveAll()
	{
		if (m_RootNode == NULL)
		{
			return;
		}

		RemoveAllode(m_RootNode);
	}

	Node* FindNode(T* InData)
	{
		if (m_RootNode == NULL)
		{
			return NULL;
		}

		Node* find = Find(m_RootNode, InData);
		if (find == NULL)
		{
			cout << "Remove Node Fail!" << endl;
			return;
		}
		cout << "Remove Node Succes!" << endl;
	}

	void PrintTree(TreeOrder InOrder)
	{
		if (m_RootNode == NULL)
		{
			return;
		}

		switch (InOrder)
		{
		case TreeOrder::Preorder:
			cout << "Preorder!" << endl;
			PrintPreorder(m_RootNode);
			break;

		case TreeOrder::Inorder:
			cout << "Inorder!" << endl;
			PrintInorder(m_RootNode);
			break;

		case TreeOrder::Postorder:
			cout << "Postorder!" << endl;
			PrintPostorder(m_RootNode);
			break;

		default:
			break;
		}

		cout << endl;
	}

private:
	void Insert(Node* InNode, Node* RootNode = NULL)
	{
		//cout << strcmp(typeid(*InNode->Data).name(), "string") << endl;
		string name = typeid(*InNode->Data).name();

		if (name.find("int") != string::npos)
		{
			//cout << "int" << endl;
			
			int result = IntDataOrder(RootNode->Data, InNode->Data);

			if (result == 1)
			{
				if (RootNode->Left == NULL)
				{
					RootNode->Left = InNode;
				}
				else
				{
					Insert(InNode, RootNode->Left);
				}

				return;
			}
			else if (result == -1)
			{
				if (RootNode->Right == NULL)
				{
					RootNode->Right = InNode;
				}
				else
				{
					Insert(InNode, RootNode->Right);
				}

				return;
			}

		}
		else if (name.find("string") != string::npos)
		{
			//cout << "string" << endl;
			int result = StringDataOrder(RootNode->Data, InNode->Data);

			if (result == 1)
			{
				if (RootNode->Left == NULL)
				{
					RootNode->Left = InNode;
				}
				else
				{
					Insert(InNode, RootNode->Left);
				}

				return;
			}
			else if (result == -1)
			{
				if (RootNode->Right == NULL)
				{
					RootNode->Right = InNode;
				}
				else
				{
					Insert(InNode, RootNode->Right);
				}

				return;
			}
		}
	}

	int IntDataOrder(T* RootData, T* InsertData)
	{
		if (*RootData < *InsertData)
		{
			return -1;
		}
		else if (*RootData > *InsertData)
		{
			return 1;
		}

		return 0;
	}

	int StringDataOrder(T* RootData, T* InsertData)
	{
		stringstream RootString;
		stringstream InsertString;

		RootString << *RootData;
		InsertString << *InsertData;

		if (RootString.str().compare(InsertString.str()) > 0)
		{
			return 1;
		}
		else if (RootString.str().compare(InsertString.str()) < 0)
		{
			return -1;
		}

		return 0;
	}

private:
	Node* Remove(Node* InRoot, T* InData)
	{
		if (InRoot == NULL)
		{
			return NULL;
		}

		string name = typeid(*InData).name();
		int result = -99999;
		if (name.find("int") != string::npos)
		{
			result = IntDataOrder(InRoot->Data, InData);
		}
		else if (name.find("string") != string::npos)
		{
			result = StringDataOrder(InRoot->Data, InData);
		}

		if (result == 0)
		{
			Node* temp;
			if (InRoot->Left != NULL && InRoot->Right != NULL)
			{
				temp = GetMinNode(InRoot->Right);
				InRoot->Data = temp->Data;
				InRoot->Right = Remove(InRoot->Right, temp->Data);
			}
			else
			{
				temp = InRoot;
				if (InRoot->Left == NULL)
				{
					InRoot = InRoot->Right;
				}
				else if (InRoot->Right == NULL)
				{
					InRoot = InRoot->Left;
				}

				//delete temp->Data;
				delete temp;
			}
		}
		else if (result == 1)
		{
			InRoot->Left = Remove(InRoot->Left, InData);
		}
		else if (result == -1)
		{
			InRoot->Right = Remove(InRoot->Right, InData);
		}

		return InRoot;
	}

	void RemoveAllode(Node* InNode)
	{
		if (InNode == NULL)
		{
			return;
		}

		Node* temp = InNode;
		RemoveAllode(InNode->Left);
		RemoveAllode(InNode->Right);

		delete temp->Data;
		delete temp;

		m_RootNode = NULL;
	}

private:
	Node* Find(Node* InRoot, T* InData)
	{
		if (InRoot == NULL)
		{
			return NULL;
		}

		string name = typeid(*InData).name();
		int result = -99999;
		if (name.find("int") != string::npos)
		{
			result = IntDataOrder(InRoot->Data, InData);
		}
		else if (name.find("string") != string::npos)
		{
			result = StringDataOrder(InRoot->Data, InData);
		}
		
		if (result == 0)
		{
			return InRoot;
		}
		else if (result == 1)
		{
			Find(InRoot->Left, InData);
		}
		else if (result == -1)
		{
			Find(InRoot->Right, InData);
		}

		return NULL;
	}

private:
	void PrintPreorder(Node* InNode)
	{
		if (InNode == NULL)
		{
			return;
		}

		cout << *InNode->Data << " -> ";
		PrintPreorder(InNode->Left);
		PrintPreorder(InNode->Right);
	}
	
	void PrintInorder(Node* InNode = NULL)
	{
		if (InNode == NULL)
		{
			return;
		}

		PrintInorder(InNode->Left);
		cout << *InNode->Data << " -> ";
		PrintInorder(InNode->Right);
	}

	void PrintPostorder(Node* InNode = NULL)
	{
		if (InNode == NULL)
		{
			return;
		}

		PrintPostorder(InNode->Left);
		PrintPostorder(InNode->Right);
		cout << *InNode->Data << " -> ";
	}

private:
	Node* GetMinNode(Node* InNode)
	{
		if (InNode == NULL)
		{
			return NULL;
		}

		if (InNode->Left != NULL)
		{
			GetMinNode(InNode->Left);
		}
		else
		{
			return InNode;
		}
	}

	Node* GetMaxNode(Node* InNode)
	{
		if (InNode == NULL)
		{
			return NULL;
		}

		if (InNode->Right != NULL)
		{
			GetMinNode(InNode->Right);
		}
		else
		{
			return InNode;
		}
	}

public:
	struct Node
	{
		T* Data;
		Node* Left;
		Node* Right;
	};

private:
	Node* m_RootNode = NULL;
};
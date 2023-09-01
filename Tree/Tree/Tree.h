#pragma once

#include <iostream>
#include <string>

using namespace std;

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

public:
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
			cout << "string" << endl;
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
		return -9999;
	}

	void RemoveAll()
	{
		if (m_RootNode == NULL)
		{
			return;
		}

		RemoveNode(m_RootNode);
	}

	void RemoveNode(Node* InNode)
	{
		if (InNode == NULL)
		{
			return;
		}

		Node* temp = InNode;
		RemoveNode(InNode->Left);
		RemoveNode(InNode->Right);

		delete temp->Data;
		delete temp;
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
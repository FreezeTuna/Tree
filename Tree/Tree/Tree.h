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
		SetBalanceFactor(m_RootNode);
		ReplaceNode(m_RootNode);
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
			cout << "Find Node Fail!" << endl;
			return NULL;
		}
		cout << "Find Node Succes!" << endl;

		return find;
	}

	void SetNodeBF()
	{
		if (m_RootNode == NULL)
		{
			return;
		}

		SetBalanceFactor(m_RootNode);
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
		int dataOrder = GetDataOrder(RootNode, InNode->Data);

		if (dataOrder == 1)
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
		else if (dataOrder == -1)
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

		int dataOrder = GetDataOrder(InRoot, InData);

		if (dataOrder == 0)
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
		else if (dataOrder == 1)
		{
			InRoot->Left = Remove(InRoot->Left, InData);
		}
		else if (dataOrder == -1)
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

		int dataOrder = GetDataOrder(InRoot, InData);
		
		if (dataOrder == 0)
		{
			return InRoot;
		}
		else if (dataOrder == 1)
		{
			Find(InRoot->Left, InData);
		}
		else if (dataOrder == -1)
		{
			Find(InRoot->Right, InData);
		}
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

private:
	int SetBalanceFactor(Node* InNode)
	{
		if (InNode == NULL)
		{
			return -999;
		}

		int left = 0, right = 0;
		int result = 0;

		result = SetBalanceFactor(InNode->Left);

		if (result == -999)
		{
			left = 0;
		}
		else
		{
			if (result < 0)
			{
				result = result * -1;
			}

			left = result;
			left += 1;
		}

		result = SetBalanceFactor(InNode->Right);

		if (result == -999)
		{
			right = 0;
		}
		else
		{
			if (result > 0)
			{
				result = result * -1;
			}

			right = result;
			right -= 1;
		}

		//cout << left << "  " << right << endl;
		cout << *InNode->Data << " : " << left + right << endl;
		InNode->BF = left + right;

		if (abs(left) < abs(right))
		{
			return abs(right);
		}
		/*else if (abs(left) > abs(right))
		{*/
		return abs(left);
		//}
	}

	void ReplaceNode(Node* InNode)
	{
		if (InNode == NULL)
		{
			return;
		}

		ReplaceNode(InNode->Left);
		ReplaceNode(InNode->Right);

		if (abs(InNode->BF) > 1)
		{
			if (InNode->BF > 0)
			{
				if (InNode->Left->BF > 0)
				{
					Node* parentNode = GetParentNode(m_RootNode, InNode->Data);
					RightRotation(InNode, parentNode);
				}
				else if (InNode->Left->BF < 0)
				{
					LeftRotation(InNode->Left, InNode);

					Node* parentNode = GetParentNode(m_RootNode, InNode->Data);
					RightRotation(InNode, parentNode);
				}
			}
			else if (InNode->BF < 0)
			{
				if (InNode->Right->BF < 0)
				{
					Node* parentNode = GetParentNode(m_RootNode, InNode->Data);
					LeftRotation(InNode, parentNode);
				}
				else if (InNode->Right->BF > 0)
				{
					RightRotation(InNode->Right, InNode);

					Node* parentNode = GetParentNode(m_RootNode, InNode->Data);
					LeftRotation(InNode, parentNode);
				}
			}
		}

		SetBalanceFactor(m_RootNode);
		cout << endl;
	}

	void LeftRotation(Node* InNode, Node* InRoot = NULL)
	{
		if (InNode == NULL)
		{
			return;
		}

		Node* tempInNodeRight = InNode->Right;
		Node* tempInNode = InNode;

		if (InNode->Right != NULL)
		{
			Node* temp = InNode->Right->Left;

			InNode->Right->Left = InNode;
			InNode->Right = temp;
		}


		if (InRoot != NULL)
		{
			// RR의 회전 경우
			if (InNode == InRoot->Right)
			{
				InRoot->Right = tempInNodeRight;
			}
			// RL의 회전 경우
			else
			{
				InRoot->Left = tempInNodeRight;
			}
		}
		else if (tempInNode == m_RootNode)
		{
			m_RootNode = tempInNodeRight;
		}
	}
	
	void RightRotation(Node* InNode, Node* InRoot = NULL)
	{
		if (InNode == NULL)
		{
			return;
		}
		
		Node* tempInNodeLeft = InNode->Left;
		Node* tempInNode = InNode;

		if (InNode->Left != NULL)
		{
			Node* temp = InNode->Left->Right;

			InNode->Left->Right = InNode;
			InNode->Left = temp;
		}

		if (InRoot != NULL)
		{
			//	LL의 회전 경우
			if (InNode == InRoot->Right)
			{
				InRoot->Right = tempInNodeLeft;
			}
			//	LR의 회전 경우
			else
			{
				InRoot->Left = tempInNodeLeft;
			}
		}
		else if (tempInNode == m_RootNode)
		{
			m_RootNode = tempInNodeLeft;
		}
	}

private:
	int GetDataOrder(Node* InRoot, T* InData)
	{
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

		return result;
	}

	Node* GetParentNode(Node* InRoot, T* InData)
	{
		if (InRoot == NULL)
		{
			return NULL;
		}

		int dataOrder = GetDataOrder(InRoot, InData);

		if (dataOrder == 1)
		{
			if (GetDataOrder(InRoot->Left, InData) == 0)
			{
				return InRoot;
			}
			else
			{
				GetParentNode(InRoot->Left, InData);
			}
		}
		else if (dataOrder == -1)
		{
			if (GetDataOrder(InRoot->Right, InData) == 0)
			{
				return InRoot;
			}
			else
			{
				GetParentNode(InRoot->Right, InData);
			}
		}
		else
		{
			return NULL;
		}
	}

public:
	struct Node
	{
		T* Data;
		int BF = -99;
		Node* Left;
		Node* Right;
	};

private:
	Node* m_RootNode = NULL;
};
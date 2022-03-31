#include <iostream>
#include <vector>
#include <locale.h>
#include <cassert>

using namespace std;

class BinaryTree
{
public:
	class Node
	{
	public:
		int m_key;
		Node *m_left_child;
		Node *m_right_child;
		
		Node(int key = 0, Node *left_child = nullptr, Node *right_child = nullptr)
		{
			m_key = key;
			m_left_child = left_child;
			m_right_child = right_child;
		}
		int get_node_key();
		int get_node_children_amount();
	
	};
	BinaryTree() {};
	BinaryTree();//to do: copy
	~BinaryTree();
	Node *node(const int node_index)
	{
		return node(m_root, node_index);
	}
	Node *node(Node *sub_tree_root, int node_index);
	Node *node_recursive(const int nodeIndex);
	Node *node_recursive(Node *sub_tree_root, const int nodeIndex);
	Node *node_recursive(const int nodeIndex, const vector<Node*> &current_level_nodes);
	
	void print_tree(Node*);
	void delete_tree(const int node_index);
	void delete_subtrees(const int node_index);
	bool is_empty(const int node_index);
	int get_tree_height(const int node_index);
	int get_nodes_amount(const int node_index);
	int get_min_key(const int node_index);
	int get_max_key(const int node_index);
	bool add_node(const int node_index, const int key);
	bool delete_node(const int node_index);

private:
	Node *m_root = nullptr;
	void delete_tree(Node*);
	void delete_subtrees(Node*);
	int get_tree_height(Node*, int &max_height);
	int get_nodes_amount(Node*, int &amount);
	int get_min_key(Node*, int &min_key);
	int get_max_key(Node*, int &max_key);
	bool add_node(Node*, const int key);
	bool delete_node(Node*);
	Node *find_parent_node(Node*, Node*);
};

int BinaryTree::Node::get_node_key()
{
	return(this->m_key);
}

int BinaryTree::Node::get_node_children_amount()
{
	if (m_left_child && m_right_child)
	{
		return 2;
	}
	if (m_left_child || m_right_child)
	{
		return 1;
	}
	return 0;
}

BinaryTree::~BinaryTree()
{
	delete_tree(m_root);
}

void BinaryTree::delete_tree(const int node_index)
{
	delete_tree(node(node_index));
}

void BinaryTree::delete_tree(Node *subTreeRoot)
{
	if (subTreeRoot == nullptr)
	{
		return;
	}
	if (subTreeRoot->m_left_child != nullptr)
	{
		delete_tree(subTreeRoot->m_left_child);
	}
	if (subTreeRoot->m_right_child != nullptr)
	{
		delete_tree(subTreeRoot->m_right_child);
	}

	delete subTreeRoot;
}

void BinaryTree::delete_subtrees(Node* subTreeRoot)
{
	if (subTreeRoot->m_left_child)
	{
		delete_tree(subTreeRoot->m_left_child);
		subTreeRoot->m_left_child = nullptr;
	}
	if (subTreeRoot->m_right_child)
	{
		delete_tree(subTreeRoot->m_right_child);
		subTreeRoot->m_right_child = nullptr;
	}
}

int BinaryTree::get_tree_height(const int node_index)
{
	int max_height = 0;
	return get_tree_height(node(node_index), max_height);
}

int BinaryTree::get_tree_height(Node *node, int &max_height)
{
	int current_height = 1;
	if (node == nullptr)
	{
		return 0;
	}
	if (node->m_left_child)
	{
		current_height++;
		get_tree_height(node->m_left_child, max_height);
	}
	if (node->m_right_child)
	{
		current_height++;
		get_tree_height(node->m_right_child, max_height);
	}
	if (current_height > max_height)
	{
		max_height = current_height;
	}
	return max_height;
}

int BinaryTree::get_nodes_amount(const int node_index)
{
	int amount = 0;
	return get_nodes_amount(node(node_index), amount);
}



int BinaryTree::get_nodes_amount(Node *node, int &amount)
{
	if (node == nullptr)
	{
		return 0;
	}
	if (node->m_left_child)
	{
		amount++;
		get_tree_height(node->m_left_child, amount);
	}
	if (node->m_right_child)
	{
		amount++;
		get_tree_height(node->m_right_child, amount);
	}
	return amount;
}

int BinaryTree::get_min_key(const int node_index)
{
	assert(node(node_index) != nullptr && "get_min_key: node was nullptr");
	int min_key = node(node_index)->m_key;
	return get_min_key(node(node_index), min_key);
}

int BinaryTree::get_min_key(Node* node, int &min_key)
{
	if (node->m_left_child)
	{
		get_min_key(node->m_left_child, min_key);
	}
	if (node->m_right_child)
	{
		get_min_key(node->m_right_child, min_key);
	}
	if (node->m_key < min_key)
	{
		min_key = node->m_key;
	}
	return min_key;
}

int BinaryTree::get_max_key(const int node_index)
{
	assert(node(node_index) != nullptr && "get_max_key: node was nullptr");
	int max_key = node(node_index)->m_key;
	return get_max_key(node(node_index), max_key);
}

int BinaryTree::get_max_key(Node *node, int & max_key)
{
	if (node->m_left_child)
	{
		get_min_key(node->m_left_child, max_key);
	}
	if (node->m_right_child)
	{
		get_min_key(node->m_right_child, max_key);
	}
	if (node->m_key > max_key)
	{
		max_key = node->m_key;
	}
	return max_key;
}

bool BinaryTree::add_node(const int node_index, const int key)
{
	return add_node(node(node_index), key);
}

 bool BinaryTree::add_node(Node *node, const int key)
{
	 if (node == nullptr)
	 {
		 if (m_root == nullptr)
		 {
			 m_root = new Node(key);
			 return true;
		 }
		 else
		 {
			 return false;
		 }
	}
	 if (node->m_left_child == nullptr)
	 {
		 node->m_left_child = new Node(key);
		 return true;
	 }
	 else if (node->m_right_child == nullptr)
	 {
		 node->m_right_child = new Node(key);
		 return true;
	 }
	 else
	 {
		 if (rand() % 2 == 0)
		 {
			 add_node(node->m_left_child, key);
			 return true;
		 }
		 else
		 {
			 add_node(node->m_right_child, key);
			 return true;
		 }
	 }
	 //return false;
}

 bool BinaryTree::delete_node(const int node_index)
 {
	 return delete_node(node(node_index));
 }


 bool BinaryTree::delete_node(Node *node)
 {
	 if (node == nullptr)
	 {
		 return true;
	 }
	 if (node != m_root)
	 {
		 if (node->m_left_child == nullptr && node->m_right_child == nullptr)
		 {
			 Node *temp;
			 temp = find_parent_node(node, m_root);
			 if (temp->m_left_child == node)
			 {
				 temp->m_left_child = nullptr;
			 }
			 else
			 {
				 temp->m_right_child = nullptr;
			 }
			 delete node;
			 return true;
		 }
		 else if (node->m_left_child != nullptr || node->m_right_child != nullptr)
		 {
			 Node *temp;
			 temp = find_parent_node(node, m_root);
			 if (temp->m_left_child == node)
			 {
				 if (node->m_left_child != nullptr)
				 {
					 temp->m_left_child = node->m_left_child;
				 }
				 else
				 {
					 temp->m_left_child = node->m_right_child;
				 }
			 }
			 else
			 {
				 if (node->m_left_child != nullptr)
				 {
					 temp->m_right_child = node->m_left_child;
				 }
				 else
				 {
					 temp->m_right_child = node->m_right_child;
				 }
			 }
			 delete node;
			 return true;
		 }
		 else if (node->m_left_child != nullptr && node->m_right_child != nullptr)
		 {
			 Node *parent, *tmp;
			 tmp = m_root;
			 parent = find_parent_node(node, m_root);
			 if (parent->m_left_child == node)
			 {
				parent->m_left_child = node->m_left_child;
				while (tmp->m_left_child != nullptr)
				{
					tmp = tmp->m_left_child;
				}
				tmp->m_left_child = node->m_right_child;
			 }
			 else
			 {
				parent->m_right_child = node->m_left_child;
				while (tmp->m_left_child != nullptr)
				{
					tmp = tmp->m_left_child;
				}
				tmp->m_left_child = node->m_right_child;
			 }
			 delete node;
			 return true;
		 }
	 }
	 if (node->m_left_child != nullptr && node->m_right_child != nullptr)
	 {
		 Node *tmp;
		 tmp = m_root;
		 while (tmp->m_left_child != nullptr)
		 {
			 tmp = tmp->m_left_child;
		 }
		 tmp->m_left_child = node->m_right_child;
		 m_root = node->m_left_child;
		 delete node;
		 return true;
	 }
	 else if (node->m_left_child != nullptr)
	 {
		 m_root = node->m_left_child;
		 delete node;
		 return true;
	 }
	 else
	 {
		 m_root = node->m_right_child;
		 delete node;
		 return true;
	 }
	 return false;
 }

 BinaryTree::Node *BinaryTree::find_parent_node(Node *node, Node *current_node)
 {
	 if (current_node->m_left_child != nullptr)
	 {
		 if (current_node->m_left_child == node)
		 {
			 return current_node;
		 }
		 find_parent_node(node, current_node->m_left_child);
	 }
	 if (current_node->m_right_child != nullptr)
	 {
		 if (current_node->m_right_child == node)
		 {
			 return current_node;
		 }
		 find_parent_node(node, current_node->m_right_child);
	 }
 }

void BinaryTree::delete_subtrees(const int node_index)
{
	delete_subtrees(node(node_index));
}

bool BinaryTree::is_empty(const int node_index)
{
	if (node(node_index) == nullptr)
	{
		return true;
	}
	return false;
}



BinaryTree::Node *BinaryTree::node(const int nodeIndex)
{
	return node(m_root, nodeIndex);
}

BinaryTree::Node *BinaryTree::node(Node *subTreeRoot, int nodeIndex)
{
	if (nodeIndex == 0) 
	{
		return subTreeRoot;
	}
	else if (subTreeRoot == nullptr) 
	{
		return nullptr;
	}

	vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() != 0 && nodeIndex >= currentLevelNodes.size()) 
	{
		vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node *node : currentLevelNodes) 
		{
			if (node->m_left_child) 
			{
				nextLevelNodes.push_back(node->m_left_child);
			}

			if (node->m_right_child) 
			{
				nextLevelNodes.push_back(node->m_right_child);
			}
		}

		nodeIndex -= currentLevelNodes.size();
		currentLevelNodes.swap(nextLevelNodes);
	}

	if (currentLevelNodes.size() == 0) 
	{
		return nullptr;
	}
	else 
	{
		return currentLevelNodes[nodeIndex];
	}
}

BinaryTree::Node *BinaryTree::node_recursive(const int nodeIndex)
{
	return node_recursive(m_root, nodeIndex);
}

BinaryTree::Node *BinaryTree::node_recursive(Node *subTreeRoot, const int nodeIndex)
{
	if (nodeIndex == 0) 
	{
		return subTreeRoot;
	}
	else if (subTreeRoot == nullptr) 
	{
		return nullptr;
	}

	vector<Node *> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);
	return node_recursive(nodeIndex, currentLevelNodes);
}

BinaryTree::Node *BinaryTree::node_recursive(const int nodeIndex, const vector<Node *> &currentLevelNodes)
{
	if (currentLevelNodes.size() == 0) 
	{
		return nullptr;
	}
	else if (nodeIndex < currentLevelNodes.size()) 
	{
		return currentLevelNodes[nodeIndex];
	}

	vector<Node *> nextLevelNodes;
	nextLevelNodes.reserve(currentLevelNodes.size() * 2);

	for (Node *node : currentLevelNodes) 
	{
		if (node->m_left_child) 
		{
			nextLevelNodes.push_back(node->m_left_child);
		}

		if (node->m_right_child) 
		{
			nextLevelNodes.push_back(node->m_right_child);
		}
	}

	return node_recursive(nodeIndex - currentLevelNodes.size(), nextLevelNodes);
}



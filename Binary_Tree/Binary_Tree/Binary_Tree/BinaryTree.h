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
	BinaryTree(const BinaryTree &bt);
	~BinaryTree();
	Node *node(const int node_index)
	{
		return node(m_root, node_index);
	}
	Node *node(Node *sub_tree_root, int node_index);
	
	void delete_tree(const int node_index = 0);
	void delete_subtrees(const int node_index = 0);
	bool is_empty(const int node_index = 0);
	int get_tree_height(const int node_index = 0);
	int get_nodes_amount(const int node_index = 0);
	int get_min_key(const int node_index = 0);
	int get_max_key(const int node_index = 0);
	bool add_node(const int key, const int node_index = 0);
	bool delete_node(const int node_index = 0);
	bool delete_node_by_key(const int key);
	bool is_balanced(const int node_index = 0);
	int get_keys_sum(const int node_index = 0);
	int get_node_index(const int key, const int node_index = 0);
	int get_key_by_index(const int node_index = 0);
	int get_node_lvl_by_key(const int key, const int node_index = 0);
	vector<int> get_all_tree_keys(const int node_index = 0);
	BinaryTree operator=(const BinaryTree &bt);
	void print_tree_leaves(const int node_index = 0);
	BinaryTree copy_subtree(const int node_index = 0);
	void print_lvl(const int lvl);
	void print_tree();
	
private:
	Node *m_root = nullptr;
	void delete_tree(Node*);
	void delete_subtrees(Node*);
	int get_tree_height(Node*);
	int get_nodes_amount(Node*, int &amount);
	int get_min_key(Node*, int &min_key);
	int get_max_key(Node*, int &max_key);
	bool add_node(Node*, const int key);
	bool delete_node(Node*);
	Node *find_parent_node(Node*, Node*);
	bool is_balanced(Node*);
	int get_keys_sum(Node*, int &sum);
	int get_node_index(Node*, const int key);
	int get_node_lvl_by_key(Node*, const int key);
	vector<int> get_all_tree_keys(Node*);
	Node* copy_tree(const Node*);  
	BinaryTree copy_subtree(const Node*);
	void print_tree_leaves(Node*);

	void print_lvl(Node*, const int lvl, const int current_lvl = 0);

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

BinaryTree::BinaryTree(const BinaryTree &bt)
{
	m_root = copy_tree(bt.m_root);
}

BinaryTree::~BinaryTree()
{
	if (m_root != nullptr)
	{
		delete_tree(m_root);
	}
}

void BinaryTree::delete_tree(const int node_index)
{
	delete_tree(node(node_index));
}

void BinaryTree::delete_tree(Node *node)
{
	if (node == nullptr)
	{
		return;
	}
	if (node == m_root)
	{
		m_root = nullptr;
	}
	if (node->m_left_child != nullptr)
	{
		delete_tree(node->m_left_child);
	}
	if (node->m_right_child != nullptr)
	{
		delete_tree(node->m_right_child);
	}
	delete node;
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
	return get_tree_height(node(node_index));
}

int BinaryTree::get_tree_height(Node *subtree_root)
{
	if (subtree_root == nullptr)
	{
		return 0;
	}
	int height = 0;
	vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(subtree_root);

	while (currentLevelNodes.size() != 0)
	{
		height++;
		vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
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
		currentLevelNodes.swap(nextLevelNodes);
	}

	return height;
}

int BinaryTree::get_nodes_amount(const int node_index)
{
	int amount = 1;
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
		get_nodes_amount(node->m_left_child, amount);
	}
	if (node->m_right_child)
	{
		amount++;
		get_nodes_amount(node->m_right_child, amount);
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
		get_max_key(node->m_left_child, max_key);
	}
	if (node->m_right_child)
	{
		get_max_key(node->m_right_child, max_key);
	}
	if (node->m_key > max_key)
	{
		max_key = node->m_key;
	}
	return max_key;
}

bool BinaryTree::add_node(const int key, const int node_index)
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
			 if (temp != nullptr)
			 {
				 if (temp->m_left_child == node)
				 {
					 temp->m_left_child = nullptr;
				 }
				 else
				 {
					 temp->m_right_child = nullptr;
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
	 else if (node->m_right_child != nullptr)
	 {
		 m_root = node->m_right_child;
		 delete node;
		 return true;
	 }
	 else
	 {
		 m_root = nullptr;
		 delete node;
		 return true;
	 }
	 return false;
 }

bool BinaryTree::delete_node_by_key(const int key)
 {
	int node_index = get_node_index(key);
	return delete_node(node(node_index));
 }

 BinaryTree::Node *BinaryTree::find_parent_node(Node *child, Node *subtree_root)
 {
	 if (subtree_root == nullptr)
	 {
		 return nullptr;
	 } if (subtree_root->m_left_child == child || subtree_root->m_right_child == child)
	 {
		 return subtree_root;
	 }
	 vector<Node*> currentLevelNodes;
	 currentLevelNodes.push_back(subtree_root);

	 while (currentLevelNodes.size())
	 {
		 vector<Node*> nextLevelNodes;
		 nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		 for (Node* node : currentLevelNodes)
		 {
			 if (node->m_left_child != nullptr)
			 {
				 if (node->m_left_child == child)
				 {
					 return node;
				 }
				 nextLevelNodes.push_back(node->m_left_child);
			 }

			 if (node->m_right_child != nullptr)
			 {
				 if (node->m_right_child == child)
				 {
					 return node;
				 }
				 nextLevelNodes.push_back(node->m_right_child);
			 }
		 }
		 currentLevelNodes.swap(nextLevelNodes);
	 }
	 return nullptr;
 }

bool BinaryTree::is_balanced(const int node_index)
 {
	return is_balanced(node(node_index));
 }

 bool BinaryTree::is_balanced(Node *node)
 {
	 if (node == nullptr)
	 {
		 return true;
	 }
	 if (abs(get_tree_height(node->m_left_child) - get_tree_height(node->m_right_child)) > 1)
	 {
		 return false;
	 }
	 return is_balanced(node->m_left_child) && is_balanced(node->m_right_child);
 }

 int BinaryTree::get_keys_sum(Node *node, int &sum)
 {
	 if (node->m_left_child)
	 {
		 sum += node->m_left_child->m_key;
		 get_keys_sum(node->m_left_child, sum);
	 }
	 if (node->m_right_child)
	 {
		 sum += node->m_right_child->m_key;
		 get_keys_sum(node->m_right_child, sum);
	 }
	 return sum;
 }

 int BinaryTree::get_keys_sum(const int node_index)
 {
	 assert(node(node_index) != nullptr && "get_keys_sum: node was nullptr");
	 int sum = node(node_index)->m_key;
	 return get_keys_sum(node(node_index), sum);
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

int BinaryTree::get_node_index(const int key, const int node_index)
{
	return get_node_index(node(node_index), key);
}

int BinaryTree::get_node_index(Node* node, const int key)
{
	if (node == nullptr)
	{
		return -1;
	}
	int node_index = 0;
	if (node->m_key == key)
	{
		return node_index;
	}
	vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(node);

	while (currentLevelNodes.size() != 0)
	{
		vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node *node : currentLevelNodes)
		{
			if (node->m_left_child)
			{
				node_index++;
				if (node->m_left_child->m_key == key)
				{
					return node_index;
				}
				nextLevelNodes.push_back(node->m_left_child);
			}

			if (node->m_right_child)
			{
				node_index++;
				if (node->m_right_child->m_key == key)
				{
					return node_index;
				}
				nextLevelNodes.push_back(node->m_right_child);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
	return -1;
}

int BinaryTree::get_key_by_index(const int node_index)
{
	 return node(node_index)->m_key;
}

int BinaryTree::get_node_lvl_by_key(const int key, const int node_index)
{
	return get_node_lvl_by_key(node(node_index), key);
}



int BinaryTree::get_node_lvl_by_key(Node *node, const int key)
{
	if (node == nullptr)
	{
		return 0;
	}
	int lvl = 1;
	if (node->m_key == key)
	{
		return lvl;
	}

	vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(node);

	while (currentLevelNodes.size())
	{
		lvl++;
		std::vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node* node : currentLevelNodes)
		{
			if (node->m_left_child != nullptr)
			{
				if (node->m_left_child->m_key == key)
				{
					return lvl;
				}
				nextLevelNodes.push_back(node->m_left_child);
			}

			if (node->m_right_child != nullptr)
			{
				if (node->m_right_child->m_key == key)
				{
					return lvl;
				}
				nextLevelNodes.push_back(node->m_right_child);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
	return 0;
}

vector<int> BinaryTree::get_all_tree_keys(const int node_index)
{
	return get_all_tree_keys(node(node_index));
}

vector<int> BinaryTree::get_all_tree_keys(Node *node)
{
	if (node == nullptr)
	{
		return vector<int>();
	}
	vector<int> nodes_keys;
	vector<Node*> currentLevelNodes;
	currentLevelNodes.push_back(node);
	nodes_keys.push_back(node->m_key);

	while (currentLevelNodes.size() != 0)
	{
		vector<Node*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (Node *node : currentLevelNodes)
		{
			if (node->m_left_child)
			{
				nodes_keys.push_back(node->m_left_child->m_key);
				nextLevelNodes.push_back(node->m_left_child);
			}

			if (node->m_right_child)
			{
				nodes_keys.push_back(node->m_right_child->m_key);
				nextLevelNodes.push_back(node->m_right_child);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
	return nodes_keys;
}

BinaryTree::Node* BinaryTree::copy_tree(const Node* node)
{
	Node *root = nullptr;
	if (node != nullptr)
	{
		root = new Node(node->m_key);
		root->m_left_child = copy_tree(node->m_left_child);
		root->m_right_child = copy_tree(node->m_right_child);
	}
	return root;
}

BinaryTree BinaryTree::copy_subtree(const int node_index)
{
	return copy_subtree(node(node_index));
}

BinaryTree BinaryTree::copy_subtree(const Node *node)
{
	BinaryTree copy;
	copy.copy_tree(node);
	return copy;
}

void BinaryTree::print_lvl(const int lvl)
{
	print_lvl(m_root, lvl);
}

void BinaryTree::print_tree()
{
	int tree_height = get_tree_height();
	int spaces_count = 0;
	int k = 1;
	cout << "tree_height = " << tree_height << endl;
	for (int i = 0; i < tree_height; i++)
	{
		k *= 2;
		spaces_count = (1 << tree_height) - k;
		for (int j = 0; j < spaces_count; j++)
		{
			cout << " ";
		}
		print_lvl(m_root, i);
		cout << endl;
	}
}

void BinaryTree::print_lvl(Node *node, const int lvl, const int current_lvl)
{
	if (node == m_root && node == nullptr)
	{
		cout << "\nthe tree is empty";
		return;
	}
	if (node == nullptr)
	{
		int amount = 1 << (lvl - current_lvl);
		for (int i = 0; i < amount; i++)
		{
			cout << "xx  ";
		}
	}
	else
	{
		if (current_lvl == lvl)
		{
			cout << node->m_key << "  ";
		}
		else
		{
			print_lvl(node->m_left_child, lvl, current_lvl + 1);
			print_lvl(node->m_right_child, lvl, current_lvl + 1);
		}
	}
}

void BinaryTree::print_tree_leaves(const int node_index)
{
	print_tree_leaves(node(node_index));
}

void BinaryTree::print_tree_leaves(Node *node)
{
	if (node == nullptr)
	{
		return;
	}
	if (node->m_left_child == nullptr && node->m_right_child == nullptr)
	{
		cout << node->m_key << " ";
	}
	else
	{
		print_tree_leaves(node->m_left_child);
		print_tree_leaves(node->m_right_child);
	}
}

BinaryTree BinaryTree::operator=(const BinaryTree &bt)
{
	if (&bt != this)
	{
		if (m_root != nullptr)
		{
			delete_tree();
		}
		m_root = copy_tree(bt.m_root);
		return *this;
	}
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




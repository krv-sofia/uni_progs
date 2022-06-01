#include "SearchTree.h"

class BalancedSearchTree : public SearchTree
{
public:
	BalancedSearchTree() {};
	BalancedSearchTree(const SearchTree &st) : SearchTree(st) {};
	~BalancedSearchTree() {};

	bool add_node(const int key, const int node_index = 0) override;
	bool delete_node(const int node_index = 0) override;
	bool delete_node_by_key(const int key) override;
	BalancedSearchTree operator=(const BalancedSearchTree &bst);
	BalancedSearchTree copy_subtree(const int node_index = 0);

private:
	int count_balance(Node*);
	bool add_node(Node*, const int key);
	bool delete_node(Node*);
	void remove_min_key(Node*);
	void balance_recount(Node*);
	BalancedSearchTree copy_subtree(const Node*);
	Node* right_turn(Node*);
	Node* left_turn(Node*);
	Node* double_right_turn(Node*);
	Node* double_left_turn(Node*);
	Node *find_min_key(Node*);
	Node* make_balanced(Node*);
};

int BalancedSearchTree::count_balance(Node *node)
{
	return get_tree_height(node->m_right_child) - get_tree_height(node->m_left_child);
}

BalancedSearchTree BalancedSearchTree::operator=(const BalancedSearchTree &bst)
{
	if (&bst != this)
	{
		if (m_root != nullptr)
		{
			delete_tree();
		}
		m_root = copy_tree(bst.m_root);
		return *this;
	}
}

BalancedSearchTree BalancedSearchTree::copy_subtree(const int node_index)
{
	return copy_subtree(node(node_index));
}

BalancedSearchTree BalancedSearchTree::copy_subtree(const Node *node)
 {
	 BalancedSearchTree copy;
	 copy.m_root = copy_tree(node);
	 return copy;
 }

bool BalancedSearchTree::add_node(const int key, const int node_index)
 {
	 return add_node(node(node_index), key);
 }

bool BalancedSearchTree::add_node(Node *node, const int key)
{
	if (node == nullptr)
	{
		if (m_root == nullptr)
		{
			m_root = new Node(key);
			m_root->m_balance = 0;
			return true;
		}
		else
		{
			return false;
		}
	}
	if (key > node->m_key)
	{
		if (node->m_right_child == nullptr)
		{
			node->m_right_child = new Node(key);
			node->m_balance = count_balance(node);
			while (node != m_root)
			{
				Node *parent = find_parent_node(node, m_root);
				parent->m_balance = count_balance(parent);
				node = parent;
				if (abs(node->m_balance) == 2)
				{
					make_balanced(node);
				}
			}
			return true;
		}
		else
		{
			add_node(node->m_right_child, key);
			return true;
		}
	}
	else if (key < node->m_key)
	{
		if (node->m_left_child == nullptr)
		{
			node->m_left_child = new Node(key);
			node->m_balance = count_balance(node);
			while (node != m_root)
			{
				Node *parent = find_parent_node(node, m_root);
				parent->m_balance = count_balance(parent);
				node = parent;
				if (abs(node->m_balance) == 2)
				{
					make_balanced(node);
				}
			}
			return true;
		}
		else
		{
			add_node(node->m_left_child, key);
			return true;
		}
	}
	return false;
}
 
BinaryTree::Node* BalancedSearchTree::right_turn(Node *node)
 {
	 if (node == nullptr || node->m_left_child == nullptr)
	 {
		 return nullptr;
	 }
	 Node *left_child = node->m_left_child;
	 Node *middle_child = left_child->m_right_child;
	 left_child->m_right_child = node;
	 node->m_left_child = middle_child;
	 Node *parent = find_parent_node(node, m_root);
	 if (parent != nullptr)
	 {
		 if (parent->m_left_child == node)
		 {
			 parent->m_left_child = left_child; 
		 }
		 else
		 {
			 parent->m_right_child = left_child;
		 }
	 }
	 else
	 {
		 m_root = left_child;
	 }
	 if (left_child->m_left_child)
	 {
		 left_child->m_left_child->m_balance = count_balance(left_child->m_left_child);
	 }
	 left_child->m_balance = count_balance(left_child);
	 node->m_balance = count_balance(node);
	 return left_child;
 }

 BinaryTree::Node* BalancedSearchTree::left_turn(Node *node)
 {
	 if (node == nullptr || node->m_right_child == nullptr)
	 {
		 return nullptr;
	 }
	 Node *right_child = node->m_right_child;
	 Node *middle_child = right_child->m_left_child;
	 right_child->m_left_child = node;
	 node->m_right_child = middle_child;
	 Node *parent = find_parent_node(node, m_root);
	 if (parent != nullptr)
	 {
		 if (parent->m_left_child == node)
		 {
			 parent->m_left_child = right_child;
		 }
		 else
		 {
			 parent->m_right_child = right_child;
		 }
	 }
	 else
	 {
		 m_root = right_child;
	 }
	 if (right_child->m_right_child)
	 {
		 right_child->m_right_child->m_balance = count_balance(right_child->m_right_child);
	 }
	 right_child->m_balance = count_balance(right_child);
	 node->m_balance = count_balance(node);
	 return right_child;
 }

 BinaryTree::Node* BalancedSearchTree::double_right_turn(Node *node)
 {
	 left_turn(node->m_left_child);
	 return right_turn(node);
 }

 BinaryTree::Node* BalancedSearchTree::double_left_turn(Node *node)
 {
	 right_turn(node->m_right_child);
	 return left_turn(node);
 }

 BinaryTree::Node* BalancedSearchTree::make_balanced(Node *node)
 {
	 if (node->m_balance == 2)
	 {
		 if (node->m_right_child->m_balance < 0)
		 {
			 return double_left_turn(node);
		 }
		 return left_turn(node);
	 }
	 else if (node->m_balance == -2)
	 {
		 if (node->m_left_child->m_balance > 0)
		 {
			return double_right_turn(node);
		 }
		 return right_turn(node);
	 }
	 else
	 {
		 return node;
	 }
 }

 bool BalancedSearchTree::delete_node(const int node_index)
 {
	return delete_node(node(node_index));
 }

bool BalancedSearchTree::delete_node_by_key(const int key)
 {
	int node_index = get_node_index(key);
	if (node_index == -1)
	{
		return false;
	}
	return delete_node(node(node_index));
 }

BinaryTree::Node *BalancedSearchTree::find_min_key(Node *node)
{
	if (node->m_left_child != nullptr)
	{
		return find_min_key(node->m_left_child);
	}
	else
	{
		return node;
	}
}

void BalancedSearchTree::remove_min_key(Node *min_key)
{
	Node *parent = find_parent_node(min_key, m_root);
	if (parent->m_left_child == min_key)
	{
		if (min_key->m_right_child != nullptr)
		{
			parent->m_left_child = min_key->m_right_child;
		}
		else
		{
			parent->m_left_child = nullptr;
		}
	}
	else
	{
		if (min_key->m_right_child != nullptr)
		{
			parent->m_right_child = min_key->m_right_child;
		}
		else
		{
			parent->m_right_child = nullptr;
		}
	}
	parent->m_balance = count_balance(parent);
	balance_recount(parent);
}

void BalancedSearchTree::balance_recount(Node *parent)
{
	if (abs(parent->m_balance) == 2)
	{
		parent = make_balanced(parent);
	}
	while (parent != m_root && parent->m_balance == 0)
	{
		Node *grandparent = find_parent_node(parent, m_root);
		if (grandparent->m_left_child == parent)
		{
			grandparent->m_balance++;
		}
		else
		{
			grandparent->m_balance--;
		}
		parent = grandparent;
		if (abs(parent->m_balance) == 2)
		{
			parent = make_balanced(parent);
		}
	}
}

 bool BalancedSearchTree::delete_node(Node *node)
 {
	 if (node == nullptr)
	 {
		 return false;
	 }
	 if (node == m_root && node->m_left_child == nullptr && node->m_right_child == nullptr)//только корень
	 {
		 m_root = nullptr;
		 delete node;
		 return true;
	 }
	 if (node->m_left_child == nullptr && node->m_right_child == nullptr)//удаляем лист
	 {
		 Node *parent = find_parent_node(node, m_root);
		 if (parent->m_left_child == node)
		 {
			 parent->m_left_child = nullptr;
			 parent->m_balance++;
			 balance_recount(parent);
		 }
		 else
		 {
			 parent->m_right_child = nullptr;
			 parent->m_balance--;
			 balance_recount(parent);
		 }
		 delete node;
		 return true;
	 }
	 else if (node->m_right_child != nullptr)//есть правое поддерево
	 {
		 Node *min_key = find_min_key(node->m_right_child);
		 if (node == m_root)
		 {
			 if (m_root->m_right_child != min_key)
			 {
				 remove_min_key(min_key);
			 }
			 m_root = min_key;
			 if (node->m_left_child != nullptr)
			 {
				 min_key->m_left_child = node->m_left_child;
			 }
			 if (node->m_right_child != min_key)
			 {
				 min_key->m_right_child = node->m_right_child;
			 }
			 //min_key->m_balance = node->m_balance;
			 min_key->m_balance = count_balance(min_key);
			 if (abs(min_key->m_balance) == 2)
			 {
				make_balanced(min_key);
			 }
			 delete node;
			 return true;
		 }
		 remove_min_key(min_key);
		 Node *parent = find_parent_node(node, m_root);
		 if (parent->m_left_child == node)
		 {
			 parent->m_left_child = min_key;
		 }
		 else
		 {
			 parent->m_right_child = min_key;
		 }
		 if (node->m_left_child != nullptr)
		 {
			 min_key->m_left_child = node->m_left_child;
		 }
		 if (node->m_right_child != min_key && node->m_right_child != nullptr)
		 {
			 min_key->m_right_child = node->m_right_child;
		 }
		 min_key->m_balance = count_balance(min_key);
		 if (abs(min_key->m_balance) == 2)
		 {
			make_balanced(min_key);
		 }
		 parent->m_balance = count_balance(parent);
		 if (abs(parent->m_balance) == 2)
		 {
			 parent = make_balanced(parent);
		 }
		 delete node;
		 return true;
	 }
	 else//есть только левое поддерево
	 {
		 if (node == m_root)
		 {
			 m_root = node->m_left_child;
			 delete node;
			 return true;
		 }
		 Node *parent = find_parent_node(node, m_root);
		 if (parent->m_left_child == node)
		 {
			 parent->m_left_child = node->m_left_child;
		 }
		 else
		 {
			 parent->m_right_child = node->m_left_child;
		 }
		 parent->m_balance = count_balance(parent);
		 balance_recount(parent);
		 delete node;
		 return true;
	 }
 }

 
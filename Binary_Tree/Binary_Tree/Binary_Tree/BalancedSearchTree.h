#include "SearchTree.h"

class BalancedSearchTree : public SearchTree
{
public:
	BalancedSearchTree() {};
	BalancedSearchTree(const SearchTree &st) : SearchTree(st) {};
	~BalancedSearchTree() {};

	bool add_node(const int key, const int node_index = 0) override;
	BalancedSearchTree operator=(const BalancedSearchTree &bst);
	BalancedSearchTree copy_subtree(const int node_index = 0);

private:
	
	BalancedSearchTree copy_subtree(const Node*);
	bool add_node(Node*, const int key, bool &h);
	bool does_need_balance(Node*, int key);
	void right_turn(Node*);
	void left_turn(Node*);
	void double_right_turn(Node*);
	void double_left_turn(Node*);
};


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
	 bool h = true;
	 return add_node(node(node_index), key, h);
 } 

 bool BalancedSearchTree::does_need_balance(Node *temp, int key)
 {
	 bool needs_balance = true;
	 if (temp->balance == 0)
	 {
		 needs_balance = false;
	 }
	 return needs_balance;
 }

 void BalancedSearchTree::right_turn(Node *node)
 {
	 if (node == nullptr || node->m_left_child == nullptr)
	 {
		 return;
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
	 if (left_child->balance == -1)
	 {
		 left_child->balance = 0;
		 node->balance = 0;
	 }
	 else
	 {
		 left_child->balance = 1;
		 node->balance = -1;
	 }
 }

 void BalancedSearchTree::left_turn(Node *node)
 {
	 if (node == nullptr || node->m_right_child == nullptr)
	 {
		 return;
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
	 if (right_child->balance == 1)
	 {
		 right_child->balance = 0;
		 node->balance = 0;
	 }
	 else
	 {
		 right_child->balance = -1;
		 node->balance = 1;
	 }
 }

 void BalancedSearchTree::double_right_turn(Node *node)
 {
	 left_turn(node->m_left_child);
	 right_turn(node);
 }

 void BalancedSearchTree::double_left_turn(Node *node)
 {
	 right_turn(node->m_right_child);
	 left_turn(node);
 }

 bool BalancedSearchTree::add_node(Node *node, const int key, bool &needs_balance)
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
	 Node *temp;
 	 temp = node;
	 if (get_node_index(key) != -1)
	 {
		 return false;
	 }
	 if (key >= temp->m_key)
	 {
		 if (temp->m_right_child == nullptr)
		 {
			 temp->m_right_child = new Node(key);
			 temp->balance++;
		 }
		 else
		 {
			 add_node(temp->m_right_child, key, needs_balance);
		 }
		 temp->balance = get_tree_height(temp->m_right_child) - get_tree_height(temp->m_left_child);
		 if (temp->balance < 2)//балансировка не требуется
		 {
			 return true;
		 }
		 else
		 {
			 if (temp->m_right_child->balance > -1)
			 {
				left_turn(temp);
			 }
			 else
			 {
				double_left_turn(temp);
			 }
			 needs_balance = false;
			 return true;
		 }
	 }
	 if (key < temp->m_key)
	 {
		 if (temp->m_left_child == nullptr)
		 {
			 temp->m_left_child = new Node(key);
			 cout << endl << key;
			 temp->balance--;
		 }
		 else
		 {
			add_node(temp->m_left_child, key, needs_balance);
		 }
		 temp->balance = get_tree_height(temp->m_right_child) - get_tree_height(temp->m_left_child);
		 if (temp->balance > -2)
		 {
			 return true;
		 }
		 else
		 {
			 if (temp->m_left_child->balance < 1)
			 {
				 right_turn(temp);
				 temp = temp->m_left_child;
			 }
			 else 
			 {
				 double_right_turn(temp);
			 }
			 needs_balance = false;
			 return true;
		 }
	 } 
	 return false;
 }

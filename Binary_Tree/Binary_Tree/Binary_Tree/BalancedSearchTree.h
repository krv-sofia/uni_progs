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
	bool does_need_balance(Node*, int, int key);
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

 bool BalancedSearchTree::does_need_balance(Node *temp, int same_key_node, int key)
 {
	 bool needs_balance = true;
	 if(same_key_node != -1)//вершина с таким ключом уже есть
	 {
		 needs_balance = false;
	 }
	 if (abs(temp->balance) != 2)//баланс вершины не стал хуже
	 {
		 needs_balance = false;
	 }
	 if (is_balanced(temp->m_left_child) && is_balanced(temp->m_right_child))//нижние уровни сбалансированны
	 {
		 needs_balance = false;
	 }
	 return needs_balance;
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
	 int same_key_node = get_node_index(key);
	 bool needs_balance;
	 if (key >= temp->m_key)
	 {
		 if (temp->m_right_child == nullptr)
		 {
			 temp->m_right_child = new Node(key);
			 temp->balance++;
			 return true;
		 }
		 else
		 {
			 add_node(temp->m_right_child, key, needs_balance);
		 }
		 needs_balance = does_need_balance(temp, same_key_node, key);
		 if (needs_balance == false)
		 {
			 return true;
		 }
		 else
		 {
			 if (temp->balance == -1)
			 {
				 temp->balance = 0;
				 needs_balance = false;
				 return true;
			 }
			 if (temp->balance == 0)
			 {
				 temp->balance = 1;
				 return true;
			 }
			 if (temp->balance == 1)
			 {
				 temp->balance = 2;
				 if (temp->m_right_child->balance == 1)
				 {
					 //левый поворот относительно temp
					 temp->balance = 0;
					 temp->m_right_child->balance = 0;
				 }
				 if (temp->m_right_child->balance == -1)
				 {
					 Node *p;
					 p = temp->m_right_child->m_left_child;
					 //правый поворот относительно temp->m_right_child
					 //левый поворот относительно temp
					 if (p->balance == 1)
					 {
						 temp->balance = -1;
						 temp->m_right_child->balance = 0;
					 }
					 if (p->balance == -1)
					 {
						 temp->balance = 0;
						 temp->m_right_child->balance = 1;
					 }
					 if (p->balance == 0)
					 {
						 temp->balance = 0;
						 temp->m_right_child->balance = 0;
					 }
					 p->balance = 0;
					 temp = p;
					 //двукратный поворот налево??
				 }
				 needs_balance = false;
				 return true;
			 }
		 }
	 }
	 if (key < temp->m_key)
	 {
		 if (temp->m_left_child == nullptr)
		 {
			 temp->m_left_child = new Node(key);
			 temp->balance--;
			 return true;
		 }
		 else
		 {
			add_node(temp->m_left_child, key, needs_balance);
		 }
		 needs_balance = does_need_balance(temp, same_key_node, key);
		 if (needs_balance == false)
		 {
			 return true;
		 }
		 else
		 {
			 if (temp->balance == 1)
			 {
				 temp->balance = 0;
				 needs_balance = false;
				 return true;
			 }
			 if (temp->balance == 0)
			 {
				 temp->balance = -1;
				 return true;
			 }
			 if (temp->balance == -1)
			 {
				 temp->balance = -2;
				 if (temp->m_left_child->balance == -1)
				 {
					 //правый поворот относительно temp
					 temp->balance = 0;
					 temp->m_left_child->balance = 0;
					 temp = temp->m_left_child;//???
				 }
				 else if (temp->m_left_child->balance == 1)
				 {
					 Node *p = temp->m_left_child->m_right_child;
					 //поворот налево относительно temp->m_left_child
					 //поворот направо относительно temp
					 if (temp->balance == -1)
					 {
						 temp->balance = 1;
						 temp->m_left_child->balance = 0;
					 }
					 if (temp->balance == 1)
					 {
						 temp->balance = 0;
						 temp->m_left_child->balance = -1;
					 }
					 if (temp->balance == 0)
					 {
						 temp->balance = 0;
						 temp->m_left_child->balance = 0;
					 }
					 temp->balance = 0;
					 temp = p;//????
				 }
				 needs_balance = false;
				 return true;
			 }
		 }
	 }
	//
	 
	 return false;
 }

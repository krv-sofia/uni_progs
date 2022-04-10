#include "BinaryTree.h"

class SearchTree : public BinaryTree
{
public:
	SearchTree() {};
	SearchTree(const SearchTree &st) : BinaryTree(st) {};
	~SearchTree() {};

	int get_min_key(const int node_index = 0) override;
	int get_max_key(const int node_index = 0) override;
	bool add_node(const int key, const int node_index = 0) override;
	bool delete_node(const int node_index = 0) override;
	bool delete_node_by_key(const int key) override;
	int get_node_lvl_by_key(const int key, const int node_index = 0) override;
	SearchTree operator=(const SearchTree &st);
	SearchTree copy_subtree(const int node_index = 0);

private:
	int get_min_key(Node*);
	int get_max_key(Node*);
	bool add_node(Node*, const int key);
	bool delete_node(Node*);
	int get_node_lvl_by_key(Node*, const int key);
	SearchTree copy_subtree(const Node*);
};

int SearchTree::get_min_key(const int node_index)
{
	return get_min_key(node(node_index));
}

int SearchTree::get_min_key(Node* node)
{
	assert(node != nullptr && "get_min_key: node was nullptr");
	while (node->m_left_child != nullptr)
	{
		node = node->m_left_child;
	}
	return node->m_key;
}
int SearchTree::get_max_key(const int node_index)
{
	return get_max_key(node(node_index));
}

int SearchTree::get_max_key(Node* node)
{
	assert(node != nullptr && "get_max_key: node was nullptr");
	while (node->m_right_child != nullptr)
	{
		node = node->m_right_child;
	}
	return node->m_key;
}

bool SearchTree::add_node(const int key, const int node_index)
{
	return add_node(node(node_index), key);
}



bool SearchTree::add_node(Node *node, const int key)
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
	while (temp != nullptr)
	{
		while (key >= temp->m_key && temp->m_right_child != nullptr)
		{
			temp = temp->m_right_child;
		}
		if (key >= temp->m_key)
		{
			temp->m_right_child = new Node(key);
			return true;
		}
		while (key < temp->m_key && temp->m_left_child != nullptr)
		{
			temp = temp->m_left_child;
		}
		if (key < temp->m_key)
		{
			temp->m_left_child = new Node(key);
			return true;
		}
	}
	return false;
}

bool SearchTree::delete_node(const int node_index)
{
	return delete_node(node(node_index));
}

bool SearchTree::delete_node(Node *node)
{
	if (node == nullptr)
	{
		return true;
	}
	if (node != m_root)
	{
		Node *parent, *temp;
		parent = find_parent_node(node, m_root);
		if (node->m_left_child != nullptr && node->m_right_child != nullptr)
		{
			if (parent->m_right_child == node)
			{
				parent->m_right_child = node->m_left_child;
				temp = node->m_left_child;
				while (temp->m_right_child != nullptr)
				{
					temp = temp->m_right_child;
				}
				temp->m_right_child = node->m_right_child;
				delete node;
				return true;
			}
			else
			{
				parent->m_left_child = node->m_right_child;
				temp = node->m_right_child;
				while (temp->m_left_child != nullptr)
				{
					temp = temp->m_left_child;
				}
				temp->m_left_child = node->m_left_child;
				delete node;
				return true;
			}
		}
		else if (node->m_left_child != nullptr)
		{
			if (parent->m_left_child == node)
			{
				parent->m_left_child = node->m_left_child;
				delete node;
				return true;
			}
			else
			{
				parent->m_right_child = node->m_left_child;
				delete node;
				return true;
			}
		}
		else if (node->m_right_child != nullptr)
		{
			if (parent->m_left_child == node)
			{
				parent->m_left_child = node->m_right_child;
				delete node;
				return true;
			}
			else
			{
				parent->m_right_child = node->m_right_child;
				delete node;
				return true;
			}
		}
		else
		{
			if (parent->m_left_child == node)
			{
				parent->m_left_child = nullptr;
				delete node;
				return true;
			}
			else
			{
				parent->m_right_child = nullptr;
				delete node;
				return true;
			}
		}
	}
	else
	{
		if (node->m_left_child != nullptr && node->m_right_child != nullptr)
		{
			Node *temp, *temp2;
			temp = node->m_left_child;
			m_root = node->m_right_child;
			temp2 = m_root;
			while (temp2->m_left_child != nullptr)
			{
				temp2 = temp2->m_left_child;
			}
			temp2->m_left_child = temp;
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
	}
	return false;
}

bool SearchTree::delete_node_by_key(const int key)
{
	int node_index = get_node_index(key);
	return delete_node(node(node_index));
}

int SearchTree::get_node_lvl_by_key(const int key, const int node_index)
{
	return get_node_lvl_by_key(node(node_index), key);
}

int SearchTree::get_node_lvl_by_key(Node *node, const int key)
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
	Node *temp;
	temp = node;
	while (temp != nullptr)
	{
		while (key > temp->m_key)
		{
			if (temp->m_right_child != nullptr)
			{
				temp = temp->m_right_child;
				lvl++;
			}
			else
			{
				return -1;
			}
		}
		while (key < temp->m_key)
		{ 
			if (temp->m_left_child != nullptr)
			{
				temp = temp->m_left_child;
				lvl++;
			}
			else
			{
				return -1;
			}
		}
		if (key == temp->m_key)
		{
			return lvl;
		}
	}
	return -1;
}

SearchTree SearchTree::operator=(const SearchTree &st)
{
	if (&st != this)
	{
		if (m_root != nullptr)
		{
			delete_tree();
		}
		m_root = copy_tree(st.m_root);
		return *this;
	}
}

SearchTree SearchTree::copy_subtree(const int node_index)
{
	return copy_subtree(node(node_index));
}

SearchTree SearchTree::copy_subtree(const Node *node)
{
	SearchTree copy;
	copy.m_root = copy_tree(node);
	return copy;
}
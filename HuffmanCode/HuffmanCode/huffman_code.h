#include "boolean_vector.h"
#include <list>
#include <fstream>
#include <algorithm>

class HuffmanTree
{
public:
	class HuffmanNode
	{
	public:
		int m_freq;
		HuffmanNode *m_left_child;
		HuffmanNode *m_right_child;
		BooleanVector bv = BooleanVector(256);
		HuffmanNode(int freq = 0, HuffmanNode *left_child = nullptr, HuffmanNode *right_child = nullptr)
		{
			m_left_child = left_child;
			m_right_child = right_child;
			m_freq = freq;
		}
	};

	HuffmanNode *m_root = nullptr;
	HuffmanTree() {};
	~HuffmanTree();
	void delete_tree(HuffmanNode*);
};

class HuffmanCode : public HuffmanTree
{
public:
	struct
	{
		bool operator()(HuffmanNode* a, HuffmanNode* b) const
		{
			return a->m_freq < b->m_freq;
		}
	} freqCompare;

	int* count_symbols_freq(const string &file_name);
	list<HuffmanNode*> create_sorted_list(int *table);
	void build(const string &file_name);
	HuffmanNode* create_tree(list <HuffmanNode*>);
};

HuffmanTree::~HuffmanTree()
{
	if (m_root != nullptr)
	{
		delete_tree(m_root);
	}
}

void HuffmanTree::delete_tree(HuffmanNode *node)
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

int* HuffmanCode::count_symbols_freq(const string &file_name)
{
	int *table = new int[256];
	for (int i = 0; i < 256; i++)
	{
		table[i] = 0;
	}
	ifstream file(file_name);
	if (!file.is_open())
	{
		cerr << "Can't open file";
		return false;
	}
	char symbol;
	while (!file.eof())
	{
		symbol = file.get();
		table[(unsigned char)symbol]++;
	}
	file.close();
	return table;
}


list<HuffmanTree::HuffmanNode*> HuffmanCode::create_sorted_list(int *table)
{
	std::list<HuffmanNode*> nodes_list;
	for (int i = 0; i < 256; i++)
	{
		if (table[i] > 0)
		{
			HuffmanNode* node = new HuffmanNode(table[i]);
			node->bv.set_bit(1, i);
			nodes_list.push_back(node);
		}
	}
	nodes_list.sort(freqCompare);
	for (HuffmanNode* temp : nodes_list)
	{
		for (int i = 0; i < 256; i++)
		{
			if (temp->bv[i] != 0)
			{
				cout << (char)i;
			}
		}
		cout << " " << "(" << temp->m_freq << ")" << endl;
	}
	return nodes_list;
}

void HuffmanCode::build(const string &file_name)
{
	int *tab = new int[256];
	std::list<HuffmanNode*> nodes_list;
	tab = count_symbols_freq(file_name);
	nodes_list = create_sorted_list(tab);
	create_tree(nodes_list);
}

HuffmanTree::HuffmanNode* HuffmanCode::create_tree(list<HuffmanNode*> nodes_list)
{
	HuffmanTree symbols_tree;
	while (nodes_list.size() != 1)
	{
		HuffmanNode *temp1, *temp2, *mergedNode;
		temp1 = nodes_list.front();
		nodes_list.pop_front();
		temp2 = nodes_list.front();
		nodes_list.pop_front();
		mergedNode = new HuffmanNode;
		mergedNode->bv = temp1->bv | temp2->bv;
		mergedNode->m_freq = temp1->m_freq + temp2->m_freq;
		mergedNode->m_left_child = temp1;
		mergedNode->m_right_child = temp2;
		nodes_list.push_front(mergedNode);
		nodes_list.sort(freqCompare);
	}
	symbols_tree.m_root = nodes_list.front();
	for (HuffmanNode* temp : nodes_list)
	{
		for (int i = 0; i < 256; i++)
		{
			if (temp->bv[i] != 0)
			{
				cout << (char)i;
			}
		}
		cout << " " << "(" << temp->m_freq << ")" << endl;
	}
	return m_root;
}

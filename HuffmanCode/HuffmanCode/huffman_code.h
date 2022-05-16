#include "boolean_vector.h"
#include <list>
#include <fstream>
#include <algorithm>
#include <vector>

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
	void print_lvl_to_file(HuffmanNode*, const int lvl, ofstream &fileName, const int current_lvl = 0);
	int get_tree_height(HuffmanNode*);
	HuffmanTree(const HuffmanTree &ht);
	HuffmanNode *copy_tree(const HuffmanNode*);
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
	HuffmanTree create_tree(list <HuffmanNode*>);
	void print_tree_to_file(HuffmanNode*);
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

int HuffmanTree::get_tree_height(HuffmanNode *subtree_root)
{
	if (subtree_root == nullptr)
	{
		return 0;
	}
	int height = 0;
	vector<HuffmanNode*> currentLevelNodes;
	currentLevelNodes.push_back(subtree_root);

	while (currentLevelNodes.size() != 0)
	{
		height++;
		vector<HuffmanNode*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (HuffmanNode* node : currentLevelNodes)
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

HuffmanTree::HuffmanTree(const HuffmanTree &ht)
{
	m_root = copy_tree(ht.m_root);
}

HuffmanTree::HuffmanNode *HuffmanTree::copy_tree(const HuffmanNode *hnode)
{
	HuffmanNode *root = nullptr;
	if (hnode != nullptr)
	{
		root = new HuffmanNode(hnode->m_freq);
		root->bv = hnode->bv;
		//cout << "root->bv: " << root->bv << endl;
		//cout << "hnode->bv: " << hnode->bv << endl;
		//cout << "root->m_freq: " << root->m_freq << endl;
		//cout << "hnode->m_freq: " << hnode->m_freq << endl;
		root->m_left_child = copy_tree(hnode->m_left_child);
		root->m_right_child = copy_tree(hnode->m_right_child);
	}
	return root;
}

void HuffmanTree::print_lvl_to_file(HuffmanNode *node, const int lvl, ofstream &fileName, const int current_lvl)
{
	if (!fileName.is_open())
	{
		cerr << "Can't create file";
		return;
	}
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
			fileName << "xx  ";
		}
	}
	else
	{
		if (current_lvl == lvl)
		{
			for (int i = 0; i < 256; i++)
			{
				if (node->bv[i] != 0)
				{
					fileName << (char)i;
				}
			}
			fileName << " " << "(" << node->m_freq << ")";
		}
		else
		{
			print_lvl_to_file(node->m_left_child, lvl,fileName, current_lvl + 1);
			print_lvl_to_file(node->m_right_child, lvl, fileName, current_lvl + 1);
		}
	}
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
	print_tree_to_file(create_tree(nodes_list).m_root);
}

HuffmanTree HuffmanCode::create_tree(list<HuffmanNode*> nodes_list)
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
	/*int tree_height = get_tree_height(symbols_tree.m_root);
	int spaces_count = 0;
	int k = 1;
	for (int i = 0; i < tree_height; i++)
	{
		k *= 2;
		spaces_count = (1 << tree_height) - k;
		for (int j = 0; j < spaces_count; j++)
		{
			cout << " ";
		}
		symbols_tree.print_lvl(symbols_tree.m_root, i);
		cout << endl;
	}*/
	return symbols_tree;
}

void HuffmanCode::print_tree_to_file(HuffmanNode *tree_root)
{
	ofstream huffman_tree_file("huffman_tree_file.txt");
	if (!huffman_tree_file.is_open())
	{
		cerr << "Can't create file";
		return;
	}
	int tree_height = get_tree_height(tree_root);
	int spaces_count = 0;
	int k = 1;
	for (int i = 0; i < tree_height; i++)
	{
		/*k *= 2;
		spaces_count = (1 << tree_height) - k;
		for (int j = 0; j < spaces_count; j++)
		{
			huffman_tree_file << " ";
		}*/
		print_lvl_to_file(tree_root, i, huffman_tree_file);
		huffman_tree_file << endl;
	}
	huffman_tree_file.close();
}

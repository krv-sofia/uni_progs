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
		BooleanVector m_symbol = BooleanVector(256);
		BooleanVector m_symbol_code;
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
	HuffmanNode *node(HuffmanNode *sub_tree_root, int node_index);
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
	int encode(const string &huffman_tree, const string &file_name);
	void get_symbols_codes(HuffmanTree::HuffmanNode*, BooleanVector code_bv, list<HuffmanNode*>&);
	HuffmanTree create_tree(list <HuffmanNode*>);
	void print_tree_to_file(HuffmanNode*, const string &huffman_tree_file = "huffman_tree_file.txt");
	HuffmanTree import_tree(const string &file_name);
	bool make_codes_file(BooleanVector, const string &file_name);
	bool decode(const string &file_name, const string &huffman_tree);
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
			if (node != nullptr && node->m_left_child)
			{
				nextLevelNodes.push_back(node->m_left_child);
			}

			if (node != nullptr && node->m_right_child)
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
		root->m_symbol = hnode->m_symbol;
		root->m_symbol_code = hnode->m_symbol_code;
		root->m_left_child = copy_tree(hnode->m_left_child);
		root->m_right_child = copy_tree(hnode->m_right_child);
	}
	return root;
}

HuffmanTree::HuffmanNode *HuffmanTree::node(HuffmanTree::HuffmanNode *subTreeRoot, int nodeIndex)
{
	if (nodeIndex == 0)
	{
		return subTreeRoot;
	}
	else if (subTreeRoot == nullptr)
	{
		return nullptr;
	}

	vector<HuffmanTree::HuffmanNode *> currentLevelNodes;
	currentLevelNodes.push_back(subTreeRoot);

	while (currentLevelNodes.size() != 0 && nodeIndex >= currentLevelNodes.size())
	{
		vector<HuffmanTree::HuffmanNode *> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (HuffmanTree::HuffmanNode *node : currentLevelNodes)
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

void HuffmanTree::print_lvl_to_file(HuffmanNode *node, const int lvl, ofstream &fileName, const int current_lvl)
{
	if (!fileName.is_open())
	{
		cerr << "print_lvl_to_file: Can't create file";
		return;
	}
	if (node == m_root && node == nullptr)
	{
		if (node == nullptr)
		{
			int amount = 1 << (lvl - current_lvl);
			for (int i = 0; i < amount; i++)
			{
				fileName << -1 << " ";
			}
		}
		return;
	}
	
	if (current_lvl == lvl)
	{
		fileName << node->m_symbol.weight() << ", " << node->m_freq << " ";
		for (int i = 0; i < 256; i++)
		{
			if (node->m_symbol[i] != 0)
			{
				fileName << (char)i;
			}
		}
		fileName << " ";
	}
	else
	{
		print_lvl_to_file(node->m_left_child, lvl, fileName, current_lvl + 1);
		print_lvl_to_file(node->m_right_child, lvl, fileName, current_lvl + 1);
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
		if (!file.eof())
		{
			table[(unsigned char)symbol]++;
		}
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
			node->m_symbol.set_bit(1, i);
			nodes_list.push_back(node);
		}
	}
	nodes_list.sort(freqCompare);
	/*for (HuffmanNode* temp : nodes_list)
	{
		for (int i = 0; i < 256; i++)
		{
			if (temp->m_symbol[i] != 0)
			{
				cout << (char)i;
			}
		}
		cout << " " << "(" << temp->m_freq << ")" << endl;
	}*/
	return nodes_list;
}

void HuffmanCode::build(const string &file_name)
{
	int *tab = new int[256];
	std::list<HuffmanNode*> nodes_list;
	tab = count_symbols_freq(file_name);
	nodes_list = create_sorted_list(tab);
	HuffmanTree tree = create_tree(nodes_list);
	print_tree_to_file(tree.m_root);                           
}

int HuffmanCode::encode(const string &huffman_tree, const string &file_name)
{
	ifstream tree_file(huffman_tree);
	if (!tree_file)
	{
		build(file_name);
	}
	HuffmanTree symbols_tree = import_tree(huffman_tree);
	BooleanVector bv1(1, 1);
	BooleanVector bv2(1, 0);
	std::list<HuffmanNode*> leaves_list;
	get_symbols_codes(symbols_tree.m_root->m_left_child, bv2, leaves_list);
	get_symbols_codes(symbols_tree.m_root->m_right_child, bv1, leaves_list);
	ifstream initial_file(file_name);
	if (!initial_file.is_open())
	{
		cerr << "Can't open file";
		return -1;
	}
	BooleanVector codes;
	int size = 0;
	while (!initial_file.eof())
	{
		BooleanVector symbol(256);
		unsigned char temp = initial_file.get();
		symbol.set_bit(1, (unsigned char)temp);
		{
			for (HuffmanTree::HuffmanNode* symbols_node : leaves_list)
			{
				if (symbols_node->m_symbol == symbol && !initial_file.eof())
				{
					codes.enlarge(symbols_node->m_symbol_code.get_size());
					codes |= symbols_node->m_symbol_code;
					size += symbols_node->m_symbol_code.get_size();
				}
			}
		}
		
	}
	//cout << endl << "SIZE: " << size << endl;
	//cout << endl << "SIZE BV: " << codes.get_size() << endl;
	if (!make_codes_file(codes, "encoded_text.txt"))
	{
		return -1;
	}
	initial_file.close();
	tree_file.close();
	return (double)(codes.m_size)/(symbols_tree.m_root->m_freq * 8) * 100;
}

bool HuffmanCode::make_codes_file(BooleanVector codes, const string &file_name)
{
	ofstream encoded_text("encoded_text.txt", ios::binary);
	if (!encoded_text.is_open())
	{
		cerr << "encode: Can't create file";
		return false;
	}
	if (codes.get_size() % 8 == 0)
	{
		encoded_text << 0;
	}
	else
	{
		encoded_text << 8 - codes.get_size() % 8;
	}
	for (int i = 0; i < codes.m_memory; i++)
	{
		BooleanVector bv(8, 1);
		encoded_text << codes.vector[i];
		bv.vector[0] &= codes.vector[i];
		//cout << bv;
	}
	//cout << endl << "codes size: " << codes.get_size() << endl;
	encoded_text.close();
	return true;
}

bool HuffmanCode::decode(const string &file_name, const string &huffman_tree)
{
	HuffmanTree symbols_tree = import_tree(huffman_tree);
	ifstream encoded_file(file_name, ios::binary);
	ofstream decoded_file("decoded_file.txt");
	if (!decoded_file.is_open())
	{
		cerr << "decode: Can't create decoded file";
		return false;
	}
	if (!encoded_file.is_open())
	{
		cerr << "decode: Can't open the encoded file";
		return false;
	}
	int extra_bits = encoded_file.get() - '0';
	BooleanVector bv;
	unsigned char ch;
	int count = 0;
	
	while (!encoded_file.eof())
	{
		ch = encoded_file.get();
		if (!encoded_file.eof())
		{
			bv.enlarge(8);
			bv.vector[bv.m_memory - 1] = ch;
			count++;
		}
	}
	//cout << endl << count;
	bv.m_size -= extra_bits;
	//cout << endl << bv << endl << bv.m_size;
	HuffmanTree::HuffmanNode* temp = symbols_tree.m_root;
	//cout << endl;
	for (int i = bv.m_size-1; i >= 0; i--)
	{
		if (bv[i] == 1)
		{
			if (temp->m_right_child)
			{
				//cout << bv[i];
				temp = temp->m_right_child;
			}
			else
			{
				for (int j = 0; j < 256; j++)
				{
					if (temp->m_symbol[j] != 0)
					{
						decoded_file << (unsigned char)j;
						//cout << " " << (unsigned char)j << " ";
					}
				}
				//cout << bv[i];
				temp = symbols_tree.m_root->m_right_child;
			}
		}
		if (bv[i] == 0)
		{
			if (temp->m_left_child)
			{
				//cout << bv[i];
				temp = temp->m_left_child;
			}
			else
			{
				for (int j = 0; j < 256; j++)
				{
					if (temp->m_symbol[j] != 0)
					{
						decoded_file << (unsigned char)j;
						//cout << " " << (unsigned char)j << " ";
					}
				}
				//cout << bv[i];
				temp = symbols_tree.m_root->m_left_child;
			}
		}
	}
	for (int i = 0; i < 256; i++)
	{
		if (temp->m_symbol[i] != 0)
		{
			decoded_file << (unsigned char)i;
		}
	}
	encoded_file.close();
	decoded_file.close();
	return true;
}

void HuffmanCode::get_symbols_codes(HuffmanTree::HuffmanNode* symbols_node, BooleanVector code_bv, list<HuffmanNode*>& leaves_list)
{
	if (symbols_node == nullptr)
	{
		return;
	}
	if (symbols_node->m_left_child == nullptr && symbols_node->m_right_child == nullptr)
	{
		symbols_node->m_symbol_code = code_bv;
		/*for (int i = 0; i < 256; i++)
		{
			if (symbols_node->m_symbol[i] != 0)
			{
				cout << (unsigned char)i;
			}
		}
		cout << " CODE: " << code_bv << endl;*/
		leaves_list.push_back(symbols_node);
	}
	else
	{
		code_bv.enlarge(1);
		get_symbols_codes(symbols_node->m_left_child, code_bv, leaves_list);
		get_symbols_codes(symbols_node->m_right_child, code_bv|BooleanVector(1, 1), leaves_list);
	}
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
		mergedNode->m_symbol = temp1->m_symbol | temp2->m_symbol;
		mergedNode->m_freq = temp1->m_freq + temp2->m_freq;
		mergedNode->m_left_child = temp1;
		mergedNode->m_right_child = temp2;
		nodes_list.push_front(mergedNode);
		nodes_list.sort(freqCompare);
	}
	symbols_tree.m_root = nodes_list.front();
	/*for (HuffmanNode* temp : nodes_list)
	{
		for (int i = 0; i < 256; i++)
		{
			if (temp->m_symbol[i] != 0)
			{
				cout << (unsigned char)i;
			}
		}
		cout << " " << "(" << temp->m_freq << ")" << endl;
	}*/
	return symbols_tree;
}

void HuffmanCode::print_tree_to_file(HuffmanNode *tree_root, const string &huffman_tree_file)
{
	ofstream tree_file(huffman_tree_file, ios::binary);
	if (!tree_file.is_open())
	{
		cerr << "print_tree_to_file: Can't create file";
		return;
	}
	int tree_height = get_tree_height(tree_root);
	int spaces_count = 0;
	int k = 1;
	for (int i = 0; i < tree_height; i++)
	{
		print_lvl_to_file(tree_root, i, tree_file);
		tree_file << endl;
	}
	tree_file.close();
}

HuffmanTree HuffmanCode::import_tree(const string &file_name)
{
	ifstream tree_file(file_name);
	if (!tree_file.is_open())
	{
		cerr << "Can't open file";
		return HuffmanTree();
	}
	HuffmanTree ht;
	int lenght, freq;
	tree_file >> lenght;
	tree_file.get();
	tree_file >> freq;
	tree_file.get();
	ht.m_root = new HuffmanTree::HuffmanNode();
	for (int i = 0; i < lenght; i++)
	{
		unsigned char symbol = tree_file.get();
		ht.m_root->m_symbol.set_bit(1, (unsigned char)symbol);
	}
	ht.m_root->m_freq = freq;
	vector<HuffmanTree::HuffmanNode*> currentLevelNodes;
	currentLevelNodes.push_back(ht.m_root);
	while (currentLevelNodes.size() != 0 && !tree_file.eof())
	{
		vector<HuffmanTree::HuffmanNode*> nextLevelNodes;
		nextLevelNodes.reserve(currentLevelNodes.size() * 2);

		for (HuffmanTree::HuffmanNode* node : currentLevelNodes)
		{
			int length, freq;
			tree_file >> length;
			if (length > 0)
			{
				tree_file.get();
				tree_file >> freq;
				tree_file.get();
				node->m_left_child = new HuffmanTree::HuffmanNode();
				for (int i = 0; i < length; i++)
				{
					unsigned char symbol = tree_file.get();
					node->m_left_child->m_symbol.set_bit(1, (unsigned char)symbol);
				}
				node->m_left_child->m_freq = freq;
				nextLevelNodes.push_back(node->m_left_child);
			}
			else
			{
				nextLevelNodes.push_back(nullptr);
			}
			tree_file >> length;
			if (length > 0)
			{
				tree_file.get();
				tree_file >> freq;
				tree_file.get();
				node->m_right_child = new HuffmanTree::HuffmanNode();
				for (int i = 0; i < length; i++)
				{
					unsigned char symbol = tree_file.get();
					node->m_right_child->m_symbol.set_bit(1, (unsigned char)symbol);
				}
				node->m_right_child->m_freq = freq;
				nextLevelNodes.push_back(node->m_right_child);
			}
			else
			{
				nextLevelNodes.push_back(nullptr);
			}
		}
		currentLevelNodes.swap(nextLevelNodes);
	}
	tree_file.close();
	return ht;
}



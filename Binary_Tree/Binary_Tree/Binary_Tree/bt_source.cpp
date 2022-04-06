#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include <locale.h>
#include <ctime>

using namespace std;
void main()
{
	srand(time(0));
	BinaryTree bt;
	BinaryTree bt2;
	BinaryTree bt3;
	int treeSize = 20;//� 40 ���������(
	for (int i = 0; i < treeSize; i++)
	{
		bt.add_node(i);
	}
	//BinaryTree bt2(bt);
	//bt3 = bt2 = bt;
	cout << "print:\n";
	bt.print_tree();
	/*bt2.print_tree();
	bt3.print_tree();*/
	//bt.delete_subtrees();
	//bt2.print_tree();
	//cout << endl << bt.get_node_index(4) << endl << bt.get_key_by_index(4);
	vector<int> vector = bt.get_all_tree_keys();
	cout << endl << "All nodes keys: ";
	for (int i = 0; i < vector.size(); i++)
	{
		cout << "  " << vector[i];
	}
	cout << endl;
	//bt.delete_tree();
	//bt.delete_node_by_key(0);
	//bt.print_tree();
	if (bt.is_balanced())
	{
		cout << endl << "tree is balanced" << endl;
	}
	else
	{
		cout << endl << "tree isn't balanced" << endl;
	}
	//bt.print_tree_leaves();
}
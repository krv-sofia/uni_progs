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
	int treeSize = 1024;
	for (int i = 0; i < treeSize; i++)
	{
		bt.add_node(i);
	}
	for (int i = 0; i < treeSize; i++)
	{
		cout << bt.get_nodes_amount() << " " <<
			bt.get_tree_height() << endl;
		cout << bt.delete_node_by_key(i) << endl;	
	}
	cout << bt.get_nodes_amount() << " " << bt.get_tree_height() << endl;
	return;
}
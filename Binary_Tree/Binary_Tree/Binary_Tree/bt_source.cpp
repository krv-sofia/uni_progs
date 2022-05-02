#include "BalancedSearchTree.h"
#include <locale.h>
#include <ctime>

using namespace std;
void main()
{

	srand(time(0));
	BalancedSearchTree bst;
	BalancedSearchTree bst2;
	const int treeSize = 170;
	vector <int> test;
	for (int i = 0; i < treeSize; i++)
	{
		int x = rand() % 1000;
		test.push_back(x);
	}
	cout << "keys: ";
	for (int x : test)
	{
		cout << x << " ";
	}
	for (int x : test)
	{
		bst.add_node(x);
		if (bst.is_balanced())
		{
			cout << endl << "tree is balanced" << endl;
		}
		else
		{
			cout << endl << "tree isn't balanced" << endl;
			bst2.print_tree();
			bst2.add_node(x);
		}
	}
	bst.print_tree();
	for (int x : test)
	{
		bst2 = bst;
		if (bst.delete_node_by_key(x))
		{
			cout << endl << "Node " << x << " was successfully deleted" << endl;
		}
		else
		{
			cout << endl << "Node " << x << " wasn't deleted" << endl;
		}
		if (bst.is_balanced())
		{
			cout << endl << "tree is balanced" << endl;
		}
		else
		{
			cout << endl << "tree isn't balanced" << endl;
			cout << endl << "Couldn't delete node " << x << endl;
			bst2.print_tree();
			bst2.delete_node_by_key(x);
		}
	}
	if (bst.is_empty())
	{
		cout << "Tree is empty" << endl;
	}
	else
	{
		cout << "Tree isn't empty" << endl;
	}
}


//	for (int i = 0; i < treeSize; i++)
//	{
//		bst.add_node(rand() % 1000);
//	}
//	if (bst.is_balanced())
//	{
//		cout << endl << "tree is balanced" << endl;
//	}
//	else
//	{
//		cout << endl << "tree isn't balanced" << endl;
//	}
//	for (int i = 0; i < treeSize; i++)
//	{
//		bst2 = bst;
//		bst2.print_tree();
//		if (bst.delete_node_by_key(i))
//		{
//			cout << endl << "Node " << i << " was successfully deleted" << endl;
//		}
//		else
//		{
//			cout << endl << "Node wasn't deleted" << endl;
//		}
//		if (bst.is_balanced())
//		{
//			cout << endl << "tree is balanced" << endl;
//			bst.print_tree();
//		}
//		else
//		{
//			cout << endl << "tree isn't balanced" << endl;
//			bst2.print_tree();
//			bst2.delete_node_by_key(i);
//		}
//	}
//	if (bst.is_empty())
//	{
//		cout << "Tree is empty" << endl;
//	}
//	else
//	{
//		cout << "Tree isn't empty" << endl;
//	}
//}

	
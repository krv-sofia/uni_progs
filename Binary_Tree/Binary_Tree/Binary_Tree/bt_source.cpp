#include "BalancedSearchTree.h"
#include <locale.h>
#include <ctime>

using namespace std;
void main()
{
	srand(time(0));
	BalancedSearchTree bst;
	const int treeSize = 15;
	//int a[treeSize] = { 1, 5, 43 };
	for (int i = 0; i < treeSize; i++)
	{
		bst.add_node(rand() % 100);
		//bst.add_node(a[i]);
		bst.print_tree();
	}
	//BalancedSearchTree bst2(bst);
	bst.print_tree();
	if (bst.is_balanced())
	{
		cout << endl << "tree is balanced" << endl;
	}
	else
	{
		cout << "tree isn't balanced" << endl;
	}

	/*for (int i = 0; i < treeSize; i++)
	{
		cout << st.get_nodes_amount() << " " << st.get_tree_height() << endl;
		cout << st.delete_node_by_key(i) << endl;	
	}
	cout << st.get_nodes_amount() << " " << st.get_tree_height() << endl;
	return;*/
}
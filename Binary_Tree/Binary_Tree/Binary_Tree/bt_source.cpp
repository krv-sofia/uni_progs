#include "BalancedSearchTree.h"
#include <locale.h>
#include <ctime>

using namespace std;
void main()
{
	srand(time(0));
	BalancedSearchTree bst;
	int treeSize = 10;
	for (int i = 0; i < treeSize; i++)
	{
		bst.add_node(rand()%10);
	}
	BalancedSearchTree bst2(bst);
	bst2.print_tree();
	/*for (int i = 0; i < treeSize; i++)
	{
		cout << st.get_nodes_amount() << " " << st.get_tree_height() << endl;
		cout << st.delete_node_by_key(i) << endl;	
	}
	cout << st.get_nodes_amount() << " " << st.get_tree_height() << endl;
	return;*/
}
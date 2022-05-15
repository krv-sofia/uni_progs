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
	vector <int> test = { 722, 908, 480, 602, 399, 976, 831, 385, 795, 173, 376, 809, 535, 296, 459, 366, 405, 201, 111, 732, 600, 535, 149, 491, 975, 473, 528, 470, 813, 799, 520, 849, 125, 56, 800, 146, 268, 133, 484, 970, 919, 630, 359, 739, 111, 123, 644, 179, 898, 838, 611, 562, 516, 303, 246, 121, 142, 968, 588, 59, 821, 803, 310, 368, 262, 800, 249, 776, 465, 627, 467, 445, 499, 406, 161, 348, 241, 123, 976, 558, 529, 260, 155, 289, 267, 982, 61, 268, 825, 699, 735, 548, 131, 903, 956, 264, 885, 150, 762, 947, 277, 252, 988, 611, 792, 389, 846, 102, 116, 446, 425, 325, 555, 891, 664, 651, 606, 275, 514, 207, 936, 48, 705, 599, 245, 244, 449, 144, 523, 945, 709, 140, 688, 319, 375, 444, 364, 763, 750, 790, 856, 461, 309, 408, 775, 987, 26, 638, 444, 565, 108, 80, 468, 537, 361, 599, 365, 416, 438, 561, 16, 624, 728, 395, 75, 819, 75, 255, 865, 80 };
	/*for (int i = 0; i < treeSize; i++)
	{
		int x = rand() % 1000;
		test.push_back(x);
	}*/
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
			//cout << endl << "tree is balanced" << endl;
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

	
#include "hash function.h"
#include <string.h>
using namespace std;

int main()
{
	 Hash_table <string>ht(5);
	 Hash_table <string>ht2;
	 ht.add_key(3, "hi");
	 ht.add_key(17, "hello");
	 ht.add_key(3, "afsfsdf");
	 ht.add_key(47, "top of the morning");
	 ht.add_key(124, "gm");
	 ht.add_key(13, "asdf");
	 ht.add_key(5, "tired");
	 ht.add_key(32, "shhhiiii");
	 ht.add_key(8, "hungry");
	 ht.add_key(25, "wertefdd");
	 ht.add_key(20, "wow");
	 ht.print();
	 ht2 = ht;
	 cout << endl << endl;
	 //ht2.print();
	 ht2.delete_key(3);
	 ht2.delete_key(17);
	 ht2.delete_key(47);
	 ht2.delete_key(124);
	 ht2.delete_key(13);
	 ht2.delete_key(5);
	 ht2.delete_key(32);
	 ht2.delete_key(8);
	 ht2.delete_key(25);
	 ht2.delete_key(20);
	 cout << endl << "AFTER DELETING: " << endl;
	 ht2.print();
	 ht2.add_key(13, "aooao");
	 cout << endl << "AFTER ADDING AGAIN: " << endl;
	 ht2.print();
	 cout << endl;
	 cout << endl << "second hash function: ";
	 ht.change_hash_function(hf2);
	 ht.print();
	 cout << endl;
	 cout << endl << "third hash function: ";
	 ht.change_hash_function(hf3);
	 ht.print();
	 cout << endl;
	 cout << endl << "first hash function again: ";
	 ht.change_hash_function(hf1);
	 ht.print();
}
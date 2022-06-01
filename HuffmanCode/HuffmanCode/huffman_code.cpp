#include "huffman_code.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HuffmanCode hc;
	hc.build("text.txt");
	cout << endl << "Compression ratio: " << hc.encode("huffman_tree_file.txt", "text.txt") << "%";
	if (hc.decode("encoded_text.txt", "huffman_tree_file.txt"))
	{
		cout << endl << "The text was successfully decoded";
	}
	else
	{
		cout << endl << "Couldn't decode the text";
	}
}

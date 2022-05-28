#include "huffman_code.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HuffmanCode hc;
	hc.build("text.txt");
	cout << endl << "Compression ratio: " << hc.encode("huffman_tree_file.txt", "text.txt") << "%";
}

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <random>
#include <time.h>

using namespace std;

bool createFileWithRandomNumbers(const string &fileName, const int numbersCount, const int maxNumberValue)
{
	ofstream f1(fileName);
	if (!f1.is_open())
	{
		cerr << "Can't create file";
		return false;
	}
	int num;
	mt19937 gen(time(0));
	uniform_int_distribution<int> uid(0, maxNumberValue);
	for (int i = 0; i < numbersCount; i++)
	{
		num = uid(gen);
		f1 << num << " ";
	}
	f1.close();
	return true;
}

bool doesFileContainSortedArray(const string &fileName)
{
	ifstream f1(fileName);
	if (!f1.is_open())
	{
		cerr << "Can't open file";
		return false;
	}
	int num1, num2;
	f1 >> num1;
	f1 >> num2;
	while (!f1.eof())
	{
		if (num1 > num2)
		{
			return false;
		}
		num1 = num2;
		f1 >> num2;
	}
	f1.close();
	return true;
}
int main()
{
	createFileWithRandomNumbers("test.txt", 10, 1000000);
	cout << doesFileContainSortedArray("test.txt") ? true : false;
}
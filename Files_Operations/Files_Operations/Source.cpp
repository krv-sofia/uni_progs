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

bool fileSplit(const string &fileName)
{
	const int filesAmount = 3;
	fstream **file = new fstream*[filesAmount];
	string *file_name = new string[filesAmount];
	for (int i = 0; i < filesAmount; i++)
	{
		file_name[i] = "f" + to_string(i) + ".txt";
		file[i] = new fstream;
		file[i]->open(file_name[i], ios::out);
		if (!file[i]->is_open())
		{
			cerr << "Can't create file";
			return false;
		}
	}
	ifstream originalFile(fileName);
	if (!originalFile.is_open())
	{
		cerr << "Can't open the original file";
		return false;
	}

	int *perfectDistribution = new int[filesAmount];
	int *segmentsCount = new int[filesAmount];
	int lvlCount = 1, j = 0;
	for (int i = 0; i < filesAmount - 1; i++)
	{
		perfectDistribution[i] = segmentsCount[i] = 1;
	}
	perfectDistribution[filesAmount-1] = segmentsCount[filesAmount-1] = 0;
	int num1, num2;
	originalFile >> num1;
	while (true)
	{
		while (!originalFile.eof())
		{

			if (num1 == -1)
			{
				num1 = num2;
			}
			*file[j] << num1 << " ";
			originalFile >> num2;
			if (num1 > num2)
			{
				num1 = -1;
				*file[j] << num1 << " ";
				break;
			}
			else
			{
				num1 = num2;
			}
		segmentsCount[j]--;
	}
		if (!originalFile.eof())
		{
			if (segmentsCount[j] < segmentsCount[j + 1])
			{
				j++;
			}
			else if (segmentsCount[j] == 0)
			{
				lvlCount++;
				int temp = perfectDistribution[0];
				j = 0;
				for (int k = 0; k < filesAmount-2; k++)
				{
					segmentsCount[k] = perfectDistribution[k + 1] - perfectDistribution[k] + temp;
					perfectDistribution[k] = perfectDistribution[k + 1] + temp;
				}
			}
			else
			{
				j = 0;
			}
		}
		else
		{
			break;
		}
	}
	for (int i = 0; i < filesAmount-1; i++)
	{
		file[i]->close();
	}
	return true;
}


int main()
{
	createFileWithRandomNumbers("test.txt", 10, 100);
	//cout << doesFileContainSortedArray("test.txt") ? true : false;
	fileSplit("test.txt");
}
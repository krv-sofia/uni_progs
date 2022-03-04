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

bool fileContainsSortedArray(const string &fileName)
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

bool resultFile(const string &fileName, const char *name = "result.txt")
{
	ifstream file(fileName);
	if (!file.is_open())
	{
		cerr << "Can't open file to print the result";
		return false;
	}
	ofstream result(name);
	if (!result.is_open())
	{
		cerr << "Can't create file to print the result";
		return false;
	}
	int num;
	while (!file.eof())
	{
		file >> num;
		if (num >= 0)
		{
			result << " " << num;
		}
	}
	file.close();
	result.close();
	return true;
}

bool fileSort(const string &fileName)
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
			for (int j = 0; j < filesAmount; j++)
			{
				delete file[j];
			}
			delete[]file;
			return false;
		}
	}
	ifstream originalFile(fileName);
	if (!originalFile.is_open())
	{
		cerr << "Can't open the original file";
		for (int i = 0; i < filesAmount; i++)
		{
			delete file[i];
		}
		delete[]file;
		return false;
	}

	int *perfectDistribution = new int[filesAmount];
	int *segmentsCount = new int[filesAmount];
	int lvlCount = 1, j = 0;
	for (int i = 0; i < filesAmount - 1; i++)
	{
		perfectDistribution[i] = segmentsCount[i] = 1;
	}
	perfectDistribution[filesAmount - 1] = segmentsCount[filesAmount - 1] = 0;
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
			*file[j] << " " << num1;
			originalFile >> num2;
			if (num1 > num2)
			{
				num1 = -1;
				*file[j] << " " << num1;
				break;
			}
			else
			{
				num1 = num2;
			}
		}
		if (originalFile.eof())
		{
			*file[j] << " " << -1;
		}
		segmentsCount[j]--;
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
				for (int k = 0; k < filesAmount - 1; k++)
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

	for (int i = 0; i < filesAmount; i++)
	{
		file[i]->close();
	}
	//merging

	for (int i = 0; i < filesAmount - 1; i++)
	{
		file[i]->open(file_name[i], ios::in);
		if (!file[i]->is_open())
		{
			cerr << "Can't open file";
			delete[]perfectDistribution;
			delete[]segmentsCount;
			for (int j = 0; j < filesAmount - 1; j++)
			{
				delete file[j];
			}
			delete[]file;
			return false;
		}
	}

	file[filesAmount - 1]->open(file_name[filesAmount - 1], ios::out);
	if (!file[filesAmount - 1]->is_open())
	{
		cerr << "Can't open file";
		delete[]perfectDistribution;
		delete[]segmentsCount;
		for (int i = 0; i < filesAmount; i++)
		{
			delete file[i];
		}
		delete[]file;
		return false;
	}
	while (lvlCount > 0)
	{
		int temp = perfectDistribution[filesAmount - 2];
		while (perfectDistribution[filesAmount - 2] > 0)
		{
			bool hasFictionalSegments = true;
			for (int i = 0; hasFictionalSegments && i < filesAmount - 1; i++)
			{
				if (segmentsCount[i] == 0)
				{
					hasFictionalSegments = false;
				}
			}
			if (hasFictionalSegments)
			{
				for (int i = 0; i < filesAmount - 1; i++)
				{
					segmentsCount[i]--;
				}
				segmentsCount[filesAmount - 1]++;
			}
			else
			{
				int min0 = -1;
				int min1 = -1;
				for (int i = 0; i < filesAmount - 1; i++)
				{
					if (segmentsCount[i] == 0)
					{
						if (i == 0)
						{
							*file[i] >> min0;
						}
						else
						{
							*file[i] >> min1;
						}
					}
					else
					{
						segmentsCount[i]--;
					}
				}
				while (min1 >= 0 && min0 >= 0)
				{
					if (min1 < min0)
					{
						*file[filesAmount - 1] << " " << min1;
						*file[1] >> min1;
					}
					else
					{
						*file[filesAmount - 1] << " " << min0;
						*file[0] >> min0;
					}
				}
				while (min1 >= 0)
				{
					*file[filesAmount - 1] << " " << min1;
					*file[1] >> min1;
				}
				while (min0 >= 0)
				{
					*file[filesAmount - 1] << " " << min0;
					*file[0] >> min0;
				}
				*file[filesAmount - 1] << " " << -1;
			}
			perfectDistribution[filesAmount - 2]--;
		}
		lvlCount--;
		perfectDistribution[filesAmount - 2] = perfectDistribution[0] - temp;
		perfectDistribution[0] = temp;
		file[filesAmount - 2]->close();
		file[filesAmount - 1]->close();
		file[filesAmount - 2]->open(file_name[filesAmount - 2], ios::out);
		if (!file[filesAmount - 2]->is_open())
		{
			cerr << "Can't open file";
			delete[]perfectDistribution;
			delete[]segmentsCount;
			for (int i = 0; i < filesAmount; i++)
			{
				delete file[i];
			}
			delete[]file;
			return false;
		}
		file[filesAmount - 1]->open(file_name[filesAmount - 1], ios::in);
		if (!file[filesAmount - 1]->is_open())
		{
			cerr << "Can't open file";
			delete[]perfectDistribution;
			delete[]segmentsCount;
			for (int i = 0; i < filesAmount; i++)
			{
				delete file[i];
			}
			delete[]file;
			return false;
		}
		fstream *tmpFile0 = file[filesAmount - 1];
		int tmpSegmentsCount0 = segmentsCount[filesAmount - 1];
		string tmpFileName0 = file_name[filesAmount - 1];
		for (int i = filesAmount - 1; i > 0; i--)
		{
			file[i] = file[i - 1];
			file_name[i] = file_name[i - 1];
			segmentsCount[i] = segmentsCount[i - 1];
		}
		file[0] = tmpFile0;
		segmentsCount[0] = tmpSegmentsCount0;
		file_name[0] = tmpFileName0;
	}


	for (int i = 0; i < filesAmount; i++)
	{
		file[i]->close();
	}
	resultFile(file_name[0]);
	delete[]perfectDistribution;
	delete[]segmentsCount;
	for (int i = 0; i < filesAmount; i++)
	{
		delete file[i];
	}
	delete[]file;
}


int main()
{
	for (int i = 0; i < 10; i++)
	{
		createFileWithRandomNumbers("test.txt", 1000, 100);
		fileSort("test.txt");
		if (fileContainsSortedArray)
		{
			cout << "\nTest passed";
		}
		else
		{
			cout << "\nTest failed";
		}
	}
}
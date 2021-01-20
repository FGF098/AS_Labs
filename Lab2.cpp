#include <iostream>

using namespace std;

void swap(unsigned array[], int index1, int index2) // function for swapping
{
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

int partition(unsigned bolts[], unsigned nuts[], int from, int till) // splitting on parts for both arrays in same ways
{
	unsigned choosenBolt = bolts[till - 1];
	
	for (int i = 0; i < till; i++) // seaching same value and swapping to same position
	{
		if(nuts[i] == choosenBolt)
		{
			swap(nuts, i, till - 1);
			break;
		}
	}
	
	int choosenNut = nuts[till - 1];
	
	int i1 = from - 1;
	int i2 = from - 1;
	
	for (int j = from; j <= till - 2; j++) // sorting for both arrays
	{
		if (bolts[j] <= choosenNut)
		{
			++i1;
			swap(bolts, i1, j);
		}
		if (nuts[j] <= choosenBolt)
		{
			++i2;
			swap(nuts, i2, j);
		}
	}
	
	// swapping base element to their place
	swap(bolts, i1 + 1, till - 1);
	swap(nuts, i2 + 1, till - 1);
	
	if(i1 == i2)
	{
		return i1 + 1;
	}
	else
	{
		perror("Different arrays for partition");
		return -1;
	}
}

int quickSort(unsigned bolts[], unsigned nuts[], int from, int till)
{
	int border;
	if(from < till - 1)
	{
		border = partition(bolts, nuts, from, till);
		quickSort(bolts, nuts, from, border);
		quickSort(bolts, nuts, border + 1, till);
	}
}

int quickSort(unsigned bolts[], unsigned nuts[], int size)
{
	quickSort(bolts, nuts, 0, size);
}

bool checkSame(unsigned array[], int index)
{
	bool same = false;
	
	for(int i = 0; i < index; i++)
	{
		if(array[i] == array[index])
		{
			same = true;
			break;
		}
	}
	
	return same;
}

bool checkNoPair(unsigned filled[], int size, unsigned current[], int index)
{
	bool flag = true;
	
	for(int i = 0; i < size; ++i)
	{
		if(current[index] == filled[i])
		{
			flag = false;
			break;
		}
	}
	
	return flag;
}

void printArray(unsigned array[], int size, string name)
{
	cout << name << ":" << endl;
	for(int i = 0; i < size; ++i)
	{
		cout << "| " << array[i] << " ";
	}
	cout << "|" << endl;
}

int main()
{
	int size;
	
	do
	{
		cout << "Input size : ";
		cin >> size;
	}
	while(size <= 0);
	
	unsigned bolts[size];
	
	bool same;
	
	for(int i = 0; i < size; i++)
	{
		do
		{
			cout << "Input bolt No " << i << " size : ";
			cin >> bolts[i];
			same = checkSame(bolts, i);
			if(same)
			{
				cout << "Sizes can't be same!" << endl;
			}
		}
		while(same);
	}
	
	printArray(bolts, size, "Bolts");
	
	unsigned nuts[size];
	
	bool noPair;
	
	for(int i = 0; i < size; i++)
	{
		do
		{
			cout << "Input nut No " << i << " size : ";
			cin >> nuts[i];
			same = checkSame(nuts, i);
			if(same)
			{
				cout << "Sizes can't be same!" << endl;
			}
			noPair = checkNoPair(bolts, size, nuts, i);
			if(noPair)
			{
				cout << "Element must have pair in another array!" << endl;
			}
		}
		while(same || noPair);
	}
	
	printArray(bolts, size, "Bolts");
	
	printArray(nuts, size, "Nuts");
	
	cout << "Sort:" << endl;
	
	quickSort(bolts, nuts, size);
	
	printArray(bolts, size, "Bolts");
	
	printArray(nuts, size, "Nuts");
	
	return 0;
}

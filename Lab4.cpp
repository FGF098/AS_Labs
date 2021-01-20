#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>
#include <climits>
#include <ctime>

using namespace std;

void FirstSecond(vector<pair<bool, unsigned char>> * array)
{
	unsigned size = array->size();
	
	vector<pair<bool, unsigned char>> * result = new vector<pair<bool, unsigned char>>(size);
	
	unsigned k = 0;
	unsigned i;
	for(i = 0; i < size; i++)
	{
		if(!(*array)[i].first)
		{
			(*result)[k] = (*array)[i];
			++k;
		}
	}
	for(i = 0; i < size; i++)
	{
		if((*array)[i].first)
		{
			(*result)[k] = (*array)[i];
			++k;
		}
	}
	
	*array = *result;
}

void FirstThird(vector<pair<bool, unsigned char>> * array)
{
	unsigned size = array->size();
	
	unsigned p = 0;
	
	for(unsigned i = 0; i < size; i++)
	{
		if(!(*array)[i].first)
		{
			swap((*array)[i], (*array)[p]);
			++p;
		}
	}
}

void SecondThird(vector<pair<bool, unsigned char>> * array)
{
	unsigned size = array->size();
	
	bool flag;
	
	unsigned i;
	
	do
	{
		flag = false;
		
		for(i = 0; i < size - 1; ++i)
		{
			if((*array)[i].first && !(*array)[i + 1].first)
			{
				swap((*array)[i], (*array)[i + 1]);
				flag = true;
			}
		}
	}
	while(flag);
}

vector<pair<bool, unsigned char>> randBuild(unsigned size)
{
	vector<pair<bool, unsigned char>> array(size);
	
	for(unsigned i = 0; i < size; ++i)
	{
		array[i].first = (bool)(rand() % 2);
		array[i].second = (unsigned char)(rand() % 100 + 1);
	}
	
	return array;
}

void print(vector<pair<bool, unsigned char>> array)
{
	unsigned size = array.size();
	
	unsigned i;
	
	for(i = 0; i < size; ++i)
	{
		cout << array[i].first << " ";
	}
	cout << endl;
	
	for(i = 0; i < size; ++i)
	{
		cout << array[i].second << " ";
	}
	cout << endl;
}

vector<pair<bool, unsigned char>> copy(vector<pair<bool, unsigned char>> array)
{
	unsigned size = array.size();
	
	vector<pair<bool, unsigned char>> result(size);
	
	for(unsigned i = 0; i < size; ++i)
	{
		result[i].first = array[i].first;
		result[i].second = array[i].second;
	}
	
	return result;
}

int main()
{
	srand(time(NULL));
	
	unsigned size = 10;
	
	vector<pair<bool, unsigned char>> original = randBuild(size);
	print(original);
	
	cout << "First and second:" << endl;
	
	vector<pair<bool, unsigned char>> firstSecond = copy(original);
	FirstSecond(&firstSecond);
	print(firstSecond);
	
	cout << "First and third:" << endl;
	
	vector<pair<bool, unsigned char>> firstThird = copy(original);
	FirstThird(&firstThird);
	print(firstThird);
	
	cout << "Second and third:" << endl;
	
	vector<pair<bool, unsigned char>> secondThird = copy(original);
	SecondThird(&secondThird);
	print(secondThird);
	
	system("pause");
	
	return 0;
}

// for console input/output
#include <iostream>

// for pseudo random generating
#include <cstdlib>
#include <ctime>

// for file working
#include <cstdio>

// for easier initialization of collections
#include <vector>
#include <forward_list>

using namespace std;

// using
// long long for data value
// int for indexes & number values
// long for file cursor position

// === static data === start ===

const int sizeOfData = sizeof(long long);

const int StartLenght = 100;

static int numberOfFiles = 3;

static vector<string> fileNames;

// === static data === end ===

// === QuickSort === start ===

void Swap(long long array[], int index1, int index2) // function for swapping
{
	long long temp = array[index1];
	
	array[index1] = array[index2];
	
	array[index2] = temp;
}

// for all QuickSort functions: end is included!

int Partition (long long array[], int start, int end)
{
	long long pivotValue = array[end];
	
	int lastSmaller = start - 1;
	
	for(int current = start; current <= end - 1; ++current)
	{
		if(array[current] <= pivotValue)
		{
			++lastSmaller;
			
			Swap(array, current, lastSmaller);
		}
	}
	
	Swap(array, lastSmaller + 1, end);
	
	return lastSmaller + 1;
}

void QuickSort(long long array[], int start, int end)
{
	if(start < end)
	{
		int pivotIndex = Partition(array, start, end);
		
		QuickSort(array, start, pivotIndex - 1);
		
		QuickSort(array, pivotIndex + 1, end);
	}
}

void QuickSort(long long array[], int size)
{
	QuickSort(array, 0, size - 1);
}

// === QuickSort === end ===

// === Start file & data initiation === start ===

void GenerateFileNames()
{
	const int MIN_NUMBER_OF_FILES = 3;
	
	cout << " === Generating file names === start === " << endl;
	
	cout << "Generating file names for " << numberOfFiles << " files." << endl;
	
	if(numberOfFiles < MIN_NUMBER_OF_FILES)
	{
		numberOfFiles = MIN_NUMBER_OF_FILES;
		
		cout << "Generating file names warning: number of files is too low - it's setted to " << MIN_NUMBER_OF_FILES << endl;
	}
	
	fileNames = vector<string>(numberOfFiles);
	
	for(int i = 0; i < numberOfFiles; ++i)
	{
		fileNames[i] = "data" + to_string(i) + ".fl";
		
		cout << fileNames[i] << endl;
	}
	
	cout << " === Generating file names === end === " << endl;
}

void FileReset()
{
	cout << " === File reset === start === " << endl;
	
	cout << "Reseting " << numberOfFiles << " files." << endl;
	
	FILE * filePointer;
	
	for(int i = 0; i < numberOfFiles; ++i)
	{
		if((filePointer = fopen(fileNames[i].c_str(), "wb")) != NULL)
		{
			if(fclose(filePointer) == EOF)
			{
				string errorText = "File reset error: can't close \"" + fileNames[i] + "\" after reseting.\n";
				
				perror(errorText.c_str());
				
				exit(0);
			}
			
			cout << "File \"" + fileNames[i] + "\" reseted succesfully." << endl;
		}
		else
		{
			string errorText = "File reset error: can't open/reset \"" + fileNames[i] + "\" file.\n";
			
			perror(errorText.c_str());
			
			if(fclose(filePointer) == EOF)
			{
				string errorText = "File reset error: can't close \"" + fileNames[i] + "\" after failed opening/reseting.\n";
				
				perror(errorText.c_str());
				
				exit(0);
			}
			
			exit(0);
		}
	}
	
	cout << " === File reset === end === files reseted sucessfully === " << endl;
}

void GenerateData(int numberOfElements)
{
	const int MIN_NUMBER_OF_ELEMENTS = 1000;
	
	cout << " === Generating data === start === " << endl;
	
	cout << "Generating data for " << numberOfElements << endl;
		
	if(numberOfElements < MIN_NUMBER_OF_ELEMENTS)
	{
		numberOfElements = MIN_NUMBER_OF_ELEMENTS;
		
		cout << "Generating data warning: number of elements is too low - it's setted to " << MIN_NUMBER_OF_ELEMENTS << endl;
	}
	
	FILE * mainFile;
	
	if((mainFile = fopen(fileNames[0].c_str(), "wb")) != NULL)
	{
		long long value;
		
		char * valuePointer = (char *)&value;
		
		int i, j;
		
		srand(time(NULL));
		
		for (i = 0; i < numberOfElements; ++i)
		{
			//value = 0 - RAND_MAX * RAND_MAX / 2;
			
			//value += rand() * rand();
			
			value = rand() * rand();
			
			for(j = 0; j < sizeOfData; ++j)
			{
				putc(valuePointer[j], mainFile);
			}
		}
		
		if(fclose(mainFile) == EOF)
		{
			string errorText = "File reset error: can't close \"" + fileNames[0] + "\" after reseting.\n";
			
			perror(errorText.c_str());
			
			exit(0);
		}
		
		cout << "Data generated succesfully." << endl;
	}
	else
	{
		string errorText = "File reset error: can't open \"" + fileNames[0] + "\" file.\n";
		
		perror(errorText.c_str());
		
		if(fclose(mainFile) == EOF)
		{
			string errorText = "File reset error: can't close \"" + fileNames[0] + "\" after failed opening.\n";
			
			perror(errorText.c_str());
			
			exit(0);
		}
		
		exit(0);
	}
	
	cout << " === Generating data === end === " << endl;
}

// === Start file & data initiation === end ===

// === data lines info structures === start ===

struct FileLinesInfo
{
	int fileIndex;
	
	vector<pair<int, int>> linesPositions;
};

// === data lines info strucrures === end ===

// === start data sorting and splitting === start ===

int getFibonacciNumber(int numero) // starting from 1!
{
	if (numero <= numberOfFiles - 2)
	{
		return 0;
	}
	else if(numero == numberOfFiles - 1)
	{
		return 1;
	}
	else
	{
		int result = 0;
		
		for (int i = 1; i <= numberOfFiles - 1; ++i)
		{
			result += getFibonacciNumber(numero - i);
		}
		
		return result;
	}
}



// === start data sorting and splitting === end ===

// === main function === start ===

int main()
{
	int i;
	
	cout << endl << " === QuickSort testing === start === " << endl << endl;
	
	cout << " === Input array: === " << endl;
	
	int size = 10;
	
	long long testArray[size] = {2l, 7l, 5l, 9l, 1l, 4l, 8l, 0l, 3l, 6l};
	
	for(i = 0; i < size; ++i)
	{
		printf("| %8li ", testArray[i]);
	}
	printf("|\n");
	
	cout << " === Sorted array === " << endl;
	
	QuickSort(testArray, size);
	
	for(i = 0; i < size; ++i)
	{
		printf("| %8li ", testArray[i]);
	}
	printf("|\n");
	
	cout << endl << " === QuickSort testing === end === " << endl << endl;
	
	cout << endl << " === InitFileNames testing === start === " << endl << endl;
	
	numberOfFiles = 2;
	
	cout << " === number of files = " << numberOfFiles << " === expected 3 files === " << endl;
	
	GenerateFileNames();
	
	numberOfFiles = -1;
	
	cout << " === number of files = " << numberOfFiles << " === expected 3 files === " << endl;
	
	GenerateFileNames();
	
	numberOfFiles = 16;
	
	cout << " === number of files = " << numberOfFiles << " === expected " << numberOfFiles << " files === " << endl;
	
	GenerateFileNames();
	
	cout << endl << " === InitFileNames testing === end === " << endl << endl;
	
	cout << endl << " === File reset testing === start === " << endl << endl;
	
	FileReset();
	
	cout << endl << " === File reset testing === end === " << endl << endl;
	
	cout << endl << " === Generating data testing === start === " << endl << endl;
	
	int numberOfElements = -10;
	
	cout << " === Genetating data for " << numberOfElements << " elements === expected error and generating 1000 elements data === " << endl;
	
	GenerateData(numberOfElements);
	
	cout << endl << " === Generating data testing === end === " << endl << endl;
	
	/*cout << endl << " === Fibonacci testing === start === " << endl << endl;
	
	cout << " === Preparing === " << endl;
	
	numberOfFiles = 3;
	
	GenerateFileNames();
	
	FileReset();
	
	cout << " === Standart Fibonacci numbers === " << endl;
	
	for(int i = 1; i < 10 ; ++i)
	{
		cout << getFibonacciNumber(i) << endl;
	}
	
	cout << " === Preparing === " << endl;
	
	numberOfFiles = 6;
	
	GenerateFileNames();
	
	FileReset();*/
	
	cout << " === Fibonacci numbers of 4 power === " << endl;
	
	numberOfFiles = 6;
	
	for(int i = 1; i < 16 ; ++i)
	{
		cout << getFibonacciNumber(i) << endl;
	}
	
	cout << endl << " === Fibonacci testing === end === " << endl << endl;
	
	return 0;
}

// === main functin === end ===

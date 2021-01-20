#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class DMaxHeap
{
	public:
		
		// index: 0,size-1
		
		DMaxHeap(vector<int> initValues, unsigned d);
		
		int ExtractMax(); // +
		
		void IncreaseKey(unsigned index, int newValue); // +
		
		void Insert(int newValue); // +
		
		void print();
		
		unsigned getSize();
	
	protected:
		
		unsigned numberOfChildren;
		
		unsigned size;
		
		vector<int> values;
		
		void buildMaxHeap(); // +
		
		void maxHeapify(unsigned index); // +
		
		unsigned parent(unsigned childIndex); // +
		
		unsigned child(unsigned parentIndex, unsigned childNumber); // + childNumber: 1,d
		
};

DMaxHeap::DMaxHeap(vector<int> initValues, unsigned d)
{
	if(d == 0)
	{
		perror("d-heap initialization error: \"d\" must be positive!\n");
		d = 1;
		values = vector<int>(0);
	}
	else
	{
		numberOfChildren = d;
		
		size = initValues.size();
		
		values = vector<int>(size);
		
		for(unsigned i = 0; i < size; ++i)
		{
			values[i] = initValues[i];
		}
		
		//cout << "Initiating successfully" << endl;
		
		buildMaxHeap();
	}
}

int DMaxHeap::ExtractMax()
{
	if (size < 1)
	{
		perror("Extract Max error: empty heap!\n");
		return 0;
	}
	else
	{
		int max = values[0];
		
		values[0] = values[size - 1];
		
		--size;
		values.resize(size);
		
		maxHeapify(0);
		
		return max;
	}
}

void DMaxHeap::IncreaseKey(unsigned index, int newValue)
{
	if(index >= size)
	{
		perror("Increase key error: index out of range\n");
	}
	else
	{
		if(newValue < values[index])
		{
			perror("Increase key error: new value smaller than previous\n");
		}
		else
		{
			values[index] = newValue;
			
			int temp;
			
			while(index > 0 && values[parent(index)] < values[index])
			{
				temp = values[parent(index)];
				values[parent(index)] = values[index];
				values[index] = temp;
				
				index = parent(index);
			}
		}
	}
}

void DMaxHeap::Insert(int newValue)
{
	++size;
	values.resize(size);
	values[size - 1] = INT_MIN;
	IncreaseKey(size - 1, newValue);
}

void DMaxHeap::buildMaxHeap()
{
	long length = parent(size - 1);
	
	for(long i = length; i >= 0; i--)
	{
		//cout << "Starting to heapify " << i << endl;
		maxHeapify(i);
		//cout << "Heapify of " << i << " succesful" << endl;
	}
	
	//cout << "Build max heap succesful" << endl;
}

void DMaxHeap::maxHeapify(unsigned index)
{
	unsigned children[numberOfChildren];
	
	for(unsigned i = 0; i < numberOfChildren; ++i)
	{
		children[i] = child(index, i + 1);
	}
	
	unsigned largest = index;
	
	for(unsigned i = 0; i < numberOfChildren; ++i)
	{
		if(children[i] < size)
		{
			if (values[children[i]] > values[largest])
			{
				largest = children[i];
			}
		}
	}
	
	if (largest != index)
	{
		unsigned temp = values[largest];
		values[largest] = values[index];
		values[index] = temp;
		
		maxHeapify(largest);
	}
}

unsigned DMaxHeap::parent(unsigned childIndex)
{
	return (childIndex - 1) / numberOfChildren; // unsigned is integer type, so its automatically [] it value
}

unsigned DMaxHeap::child(unsigned parentIndex, unsigned childNumber) // childNumber: 1,d
{
	if(childNumber > numberOfChildren)
	{
		perror("childNumber can't be bigger than \"d\"\n");
	}
	else if (childNumber == 0)
	{
		perror("childNumber can't be zero\n");
	}
	else
	{
		return parentIndex * numberOfChildren + childNumber;
	}
}

void DMaxHeap::print()
{
	if(size == 0)
	{
		perror("Empty d-heap\n");
	}
	else
	{
		printf("| %4i : %6i ", 0, values[0]);
		for(unsigned i = 1; i < size; ++i)
		{
			if(((i - 1) % numberOfChildren) == 0)
			{
				printf("|\n| parent : %4d ", parent(i));
			}
			printf("| %4d : %6d ", i, values[i]);
		}
		printf("|\n");
	}
}

unsigned DMaxHeap::getSize()
{
	return size;
}

int main()
{
	unsigned d = 1;
	do
	{
		cout << "Input d = ";
		cin >> d;
	}
	while (d < 2);
	
	unsigned size = 5;
	cout << "Input size = ";
	cin >> size; 
	
	vector<int> values(size);
	
	for(unsigned i = 0; i < size; ++i)
	{
		cout << "Input element No " << i << " : ";
		cin >> values[i]; 
	}
	
	cout << "d = " << d << " ; size = " << size << " ; elements:" << endl;
	for(unsigned i = 0; i < size; ++i)
	{
		cout << values[i] << " ";
	}
	cout << endl;
	
	DMaxHeap heap(values, d);
	cout << "Builded heap: " << endl;
	heap.print();
	
	cout << "Extract max = ";
	int max = heap.ExtractMax();
	cout << max << endl;
	
	cout << "New heap: " << endl;
	heap.print();
	
	cout << "Increasing key:" << endl;
	
	unsigned index = heap.getSize();
	cout << "Input increasing index: ";
	cin >> index;
	
	int newValue = INT_MIN;
	cout << "Input new bigger value: ";
	cin >> newValue;
	
	cout << "Increasing No " << index << " to " << newValue << endl;
	heap.IncreaseKey(index, newValue);
	
	cout << "New heap:" << endl;
	heap.print();
	
	cout << "Inserting new value:" << endl;
	
	newValue = INT_MAX;
	cout << "Input new value: ";
	cin >> newValue;
	
	cout << "Inserting new value = " << newValue << endl;
	
	heap.Insert(newValue);
	
	cout << "New heap:" << endl;
	heap.print();
	
	return 0;
}

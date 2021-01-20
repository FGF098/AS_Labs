#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// repeating time comparing
const unsigned REPEAT_CHECK = 10;
// repeating function for reducing effect of different performance in single run
const unsigned REPEAT_FUN = 16;

// consts for choosing quart
enum class Quart
{
	FIRST,
	SECOND
};

// holder for square 2^n size matrix and functions for it
class Matrix
{
	public:
		
		// initiate with power of two for 2^n size; bool flag select initiate new memory(and delete it after) or not
		Matrix(unsigned powerOfTwo, bool initiate = true);
		
		// getter for size (calculate as 2^n)
		unsigned long getSize() const;
		
		// getting pointer on const value
		const long long *const * getValue() const;
		
		// free memory is created new, else delete only pointers
		~Matrix();
		
		// all functions realized as static for reducing initiating processes in function for better function performance
		
		// getter for quart part of matrix
		static Matrix* getQuart (const Matrix *parent, Quart rowPos, Quart colPos);
		
		// normat matrixes adding
		static void addMatrixes(const Matrix *firstAddend, const Matrix *secondAddend, Matrix *sum);
		
		// normal matrixes subtraction
		static void subtractMatrixes(const Matrix *minuend, const Matrix *subtrahend, Matrix *difference);
		
		// classic recursive matrixes multiplying algoritm
		static void ClassicMatrixesMultiplying(const Matrix *firstFactor, const Matrix *secondFactor, Matrix *product);
		
		// Strassen recursive matrixes multiplying algoritm
		static void StrassenMatrixesMultiplying(const Matrix *firstFactor, const Matrix *secondFactor, Matrix *product);
		
		// filling matrix with pseudo randomly generated numbers
		static void fillRandom(Matrix *matrix);
		
		static unsigned long getSize(unsigned power);
		
		// printing on console function
		static void printMatrix(const Matrix *matrix);
		
	protected:
		
		// saves as power for easier creating quarts
		unsigned power;
		
		// pointer on data, may work as value[i][j]
		long long ** value;
		
		// true if created new data fields
		bool isParent = false;
};

// initiate with power of two for 2^n size; bool flag select initiate new memory(and delete it after) or not
Matrix::Matrix(unsigned powerOfTwo, bool initiate)
{
	power = powerOfTwo;
	
	if(initiate)
	{
		unsigned long size = getSize();
		
		value = new long long*[size];
		
		for(unsigned long i = 0; i < size; ++i)
		{
			value[i] = new long long[size]();
		}
		
		isParent = true;
	}
}

// getter for size (calculate as 2^n)
unsigned long Matrix::getSize() const
{
	return getSize(power);
}

// getting pointer on const value
const long long *const * Matrix::getValue() const
{
	return value;
}

// free memory is created new, else delete only pointers
Matrix::~Matrix()
{
	if(isParent)
	{
		unsigned long size = getSize();
		
		for(unsigned long i = 0; i < size; ++i)
		{
			delete [] value[i];
		}
	}
	delete [] value;
}

// getter for quart part of matrix
Matrix* Matrix::getQuart (const Matrix *parent, Quart rowPos, Quart colPos)
{
	Matrix *result = new Matrix(parent->power - 1, false);
	
	unsigned long size = result->getSize();
	
	unsigned long rowShift, colShift;
	
	switch(rowPos)
	{
		case Quart::FIRST :
			rowShift = 0;
			break;
		
		case Quart::SECOND :
			rowShift = size;
			break;
		
		default:
			rowShift = 0;
			perror("getQuart: invalid Quart value in rowPos\n");
			break;
	}
	
	switch(colPos)
	{
		case Quart::FIRST :
			colShift = 0;
			break;
		
		case Quart::SECOND :
			colShift = size;
			break;
		
		default:
			colShift = 0;
			perror("getQuart: invalid Quart value in colPos\n");
			break;
	}
	
	result->value = new long long*[size];
	
	for(unsigned long i = 0; i < size; ++i)
	{
		result->value[i] = parent->value[rowShift + i] + colShift;
	}
	
	return result;
}

// normat matrixes adding
void Matrix::addMatrixes(const Matrix *firstAddend, const Matrix *secondAddend, Matrix *sum)
{
	if(firstAddend->power == secondAddend->power && sum->power == firstAddend->power)
	{
		unsigned long size = sum->getSize();
		
		unsigned long i, j;
		
		for(i = 0; i < size; ++i)
		{
			for(j = 0; j < size; ++j)
			{
				sum->value[i][j] = firstAddend->value[i][j] + secondAddend->value[i][j];
			}
		}
	}
	else if(firstAddend->power == secondAddend->power)
	{
		perror("addMatrixes: sum different size\n");
	}
	else
	{
		perror("addMatrixes: addends different sizes\n");
	}
}

// normal matrixes subtraction
void Matrix::subtractMatrixes(const Matrix *minuend, const Matrix *subtrahend, Matrix *difference)
{
	if(minuend->power == subtrahend->power && difference->power == minuend->power)
	{
		unsigned long size = difference->getSize();
		
		unsigned long i, j;
		
		for(i = 0; i < size; ++i)
		{
			for(j = 0; j < size; ++j)
			{
				difference->value[i][j] = minuend->value[i][j] - subtrahend->value[i][j];
			}
		}
	}
	else if(minuend->power == subtrahend->power)
	{
		perror("subtractMatrixes: difference different size\n");
	}
	else
	{
		perror("subtractMatrixes: minuend and subtrahend different sizes\n");
	}
}

// classic recursive matrixes multiplying algoritm
void Matrix::ClassicMatrixesMultiplying(const Matrix *firstFactor, const Matrix *secondFactor, Matrix *product)
{
	if(firstFactor->power == secondFactor->power && product->power == firstFactor->power)
	{
		unsigned power = firstFactor->power;
		
		if(power == 0)
		{
			product->value[0][0] = firstFactor->value[0][0] * secondFactor->value[0][0];
		}
		else
		{
			Matrix *first11 = getQuart(firstFactor, Quart::FIRST, Quart::FIRST);
			Matrix *first12 = getQuart(firstFactor, Quart::FIRST, Quart::SECOND);
			Matrix *first21 = getQuart(firstFactor, Quart::SECOND, Quart::FIRST);
			Matrix *first22 = getQuart(firstFactor, Quart::SECOND, Quart::SECOND);
			
			Matrix *second11 = getQuart(secondFactor, Quart::FIRST, Quart::FIRST);
			Matrix *second12 = getQuart(secondFactor, Quart::FIRST, Quart::SECOND);
			Matrix *second21 = getQuart(secondFactor, Quart::SECOND, Quart::FIRST);
			Matrix *second22 = getQuart(secondFactor, Quart::SECOND, Quart::SECOND);
			
			Matrix *product11 = getQuart(product, Quart::FIRST, Quart::FIRST);
			Matrix *product12 = getQuart(product, Quart::FIRST, Quart::SECOND);
			Matrix *product21 = getQuart(product, Quart::SECOND, Quart::FIRST);
			Matrix *product22 = getQuart(product, Quart::SECOND, Quart::SECOND);
			
			Matrix *temp1 = new Matrix(power - 1);
			Matrix *temp2 = new Matrix(power - 1);
			
			ClassicMatrixesMultiplying(first11, second11, temp1);
			ClassicMatrixesMultiplying(first12, second21, temp2);
			addMatrixes(temp1, temp2, product11);
			
			ClassicMatrixesMultiplying(first11, second12, temp1);
			ClassicMatrixesMultiplying(first12, second22, temp2);
			addMatrixes(temp1, temp2, product12);
			
			ClassicMatrixesMultiplying(first21, second11, temp1);
			ClassicMatrixesMultiplying(first22, second21, temp2);
			addMatrixes(temp1, temp2, product21);
			
			ClassicMatrixesMultiplying(first21, second12, temp1);
			ClassicMatrixesMultiplying(first22, second22, temp2);
			addMatrixes(temp1, temp2, product22);
			
			delete temp1;
			delete temp2;
			
			delete product11;
			delete product12;
			delete product21;
			delete product22;
			
			delete second11;
			delete second12;
			delete second21;
			delete second22;
						
			delete first11;
			delete first12;
			delete first21;
			delete first22;
		}
	}
	else if(firstFactor->power == secondFactor->power)
	{
		perror("ClassicMatrixesMultiplying: product different size\n");
	}
	else
	{
		perror("ClassicMatrixesMultiplying: factors different sizes\n");
	}
}

// Strassen recursive matrixes multiplying algoritm
void Matrix::StrassenMatrixesMultiplying(const Matrix *firstFactor, const Matrix *secondFactor, Matrix *product)
{
	if(firstFactor->power == secondFactor->power && product->power == firstFactor->power)
	{
		unsigned power = firstFactor->power;
		
		if(power == 0)
		{
			product->value[0][0] = firstFactor->value[0][0] * secondFactor->value[0][0];
		}
		else
		{
			Matrix *first11 = getQuart(firstFactor, Quart::FIRST, Quart::FIRST);
			Matrix *first12 = getQuart(firstFactor, Quart::FIRST, Quart::SECOND);
			Matrix *first21 = getQuart(firstFactor, Quart::SECOND, Quart::FIRST);
			Matrix *first22 = getQuart(firstFactor, Quart::SECOND, Quart::SECOND);
			
			Matrix *second11 = getQuart(secondFactor, Quart::FIRST, Quart::FIRST);
			Matrix *second12 = getQuart(secondFactor, Quart::FIRST, Quart::SECOND);
			Matrix *second21 = getQuart(secondFactor, Quart::SECOND, Quart::FIRST);
			Matrix *second22 = getQuart(secondFactor, Quart::SECOND, Quart::SECOND);
			
			Matrix *product11 = getQuart(product, Quart::FIRST, Quart::FIRST);
			Matrix *product12 = getQuart(product, Quart::FIRST, Quart::SECOND);
			Matrix *product21 = getQuart(product, Quart::SECOND, Quart::FIRST);
			Matrix *product22 = getQuart(product, Quart::SECOND, Quart::SECOND);
			
			Matrix *m1 = new Matrix(power - 1);
			Matrix *m2 = new Matrix(power - 1);
			Matrix *m3 = new Matrix(power - 1);
			Matrix *m4 = new Matrix(power - 1);
			Matrix *m5 = new Matrix(power - 1);
			Matrix *m6 = new Matrix(power - 1);
			Matrix *m7 = new Matrix(power - 1);
			
			Matrix *temp1 = new Matrix(power - 1);
			Matrix *temp2 = new Matrix(power - 1);
			
			addMatrixes(first11, first22, temp1);
			addMatrixes(second11, second22, temp2);
			StrassenMatrixesMultiplying(temp1, temp2, m1);
			
			addMatrixes(first21, first22, temp1);
			StrassenMatrixesMultiplying(temp1, second11, m2);
			
			subtractMatrixes(second12, second22, temp1);
			StrassenMatrixesMultiplying(first11, temp1, m3);
			
			subtractMatrixes(second21, second11, temp1);
			StrassenMatrixesMultiplying(first22, temp1, m4);
			
			addMatrixes(first11, first12, temp1);
			StrassenMatrixesMultiplying(temp1, second22, m5);
			
			subtractMatrixes(first21, first11, temp1);
			addMatrixes(second11, second12, temp2);
			StrassenMatrixesMultiplying(temp1, temp2, m6);
			
			subtractMatrixes(first12, first22, temp1);
			addMatrixes(second21, second22, temp2);
			StrassenMatrixesMultiplying(temp1, temp2, m7);
			
			addMatrixes(m1, m4, temp1);
			subtractMatrixes(m7, m5, temp2);
			addMatrixes(temp1, temp2, product11);
			
			addMatrixes(m3, m5, product12);
			
			addMatrixes(m2, m4, product21);
			
			subtractMatrixes(m1, m2, temp1);
			addMatrixes(m3, m6, temp2);
			addMatrixes(temp1, temp2, product22);
			
			delete temp1;
			delete temp2;
			
			delete m1;
			delete m2;
			delete m3;
			delete m4;
			delete m5;
			delete m6; 
			delete m7;
			
			delete product11;
			delete product12;
			delete product21;
			delete product22;
			
			delete second11;
			delete second12;
			delete second21;
			delete second22;
						
			delete first11;
			delete first12;
			delete first21;
			delete first22;
		}
	}
	else if(firstFactor->power == secondFactor->power)
	{
		perror("StrassenMatrixesMultiplying: product different size\n");
	}
	else
	{
		perror("StrassenMatrixesMultiplying: factors different sizes\n");
	}
}

// filling matrix with pseudo randomly generated numbers
void Matrix::fillRandom(Matrix *matrix)
{
	unsigned long size = matrix->getSize();
	
	unsigned long i, j;
	
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size; ++j)
		{
			matrix->value[i][j] = rand() % 16; 
		}
	}
}

unsigned long Matrix::getSize(unsigned power)
{
	unsigned long result = 1;
	
	for(unsigned i = 0; i < power; ++i)
	{
		result *= 2;
	}
	
	return result;
}

// printing on console function
void Matrix::printMatrix(const Matrix *matrix)
{
	unsigned long size = matrix->getSize();
	
	unsigned long i, j;
	
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size; ++j)
		{
			printf(" | %16lld |", matrix->value[i][j]);
		}
		
		printf("\n");
	}
	
	printf("\n");
}

int main()
{
	srand(time(NULL));
	
	unsigned power = 2;
	
	Matrix *matrix1 = new Matrix(power);
	Matrix::fillRandom(matrix1);
	Matrix::printMatrix(matrix1);
	
	Matrix *matrix2 = new Matrix(power);
	Matrix::fillRandom(matrix2);
	Matrix::printMatrix(matrix2);
	
	Matrix *matrix3 = new Matrix(power);
	Matrix::ClassicMatrixesMultiplying(matrix1, matrix2, matrix3);
	Matrix::printMatrix(matrix3);
	
	Matrix *matrix4 = new Matrix(power);
	Matrix::StrassenMatrixesMultiplying(matrix1, matrix2, matrix4);
	Matrix::printMatrix(matrix4);
	
	delete matrix1;
	delete matrix2;
	delete matrix3;
	delete matrix4;
	
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto classic = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	auto strassen = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	
	Matrix *A;
	Matrix *B;
	Matrix *C;
	
	unsigned long size;
	
	unsigned j;
	
	for(unsigned i = 0; i < REPEAT_CHECK; ++i)
	{
		power = 1;
		do
		{
			++power;
			
			size = Matrix::getSize(power);
			
			A = new Matrix(power);
			B = new Matrix(power);
			C = new Matrix(power);
			
			Matrix::fillRandom(A);
			Matrix::fillRandom(B);
			
			start = std::chrono::steady_clock::now();
			for(j = 0; j < REPEAT_FUN; ++j)
			{
				Matrix::ClassicMatrixesMultiplying(A, B, C);
			}
			end = std::chrono::steady_clock::now();
			classic = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			
			cout << "Classic: size = " << size << " x" << REPEAT_FUN << " time = " << classic.count() << endl;
			
			start = std::chrono::steady_clock::now();
			for(j = 0; j < REPEAT_FUN; ++j)
			{
				Matrix::StrassenMatrixesMultiplying(A, B, C);
			}
			end = std::chrono::steady_clock::now();
			strassen = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			
			cout << "Strassen: size = " << size << " x" << REPEAT_FUN << " time = " << strassen.count() << endl;
			
			delete A;
			delete B;
			delete C;
			
		}
		while(classic.count() < strassen.count());
		
		cout << "Getting pros at size = " << size << endl << endl;
	}
	
	return 0;
}

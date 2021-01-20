#include <iostream>
#include <vector>
#include <utility>
#include <ctime>

using namespace std;

enum class Rotation
{
	NONE,
	// counterclockwise
	DEG_90,
	DEG_180,
	DEG_270
};

const int ROTATION_NUMBER = 4;

const int PRIME_NUMBER = 1073741789; // biggest prime number, smaller than INT_MAX / 2

class SquareMatrix
{
	public:
		
		SquareMatrix(int MatrixSize);
		
		SquareMatrix(int MatrixSize, SquareMatrix parent, pair<int, int> partPosition, Rotation rotationPosition = Rotation::NONE);
		
		void print();
		
		vector<pair<int, int>> Find(SquareMatrix searched);
		
	private:
		
		int size;
		
		vector<vector<unsigned char>> value;
		
		vector<int> CalcSearchedHash();
		
		int CalcStartHash(pair<int, int> position, int size);
};

SquareMatrix::SquareMatrix(int MatrixSize)
{
	size = MatrixSize;
	
	value = vector<vector<unsigned char>>(size, vector<unsigned char>(size));
	
	int i, j;
	
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size; ++j)
		{
			value[i][j] = rand() % 100 + '0';
		}
	}
}

SquareMatrix::SquareMatrix(int MatrixSize, SquareMatrix parent, pair<int, int> partPosition, Rotation rotationPosition)
{
	size = MatrixSize;
	
	value = vector<vector<unsigned char>>(size, vector<unsigned char>(size, '0'));
	
	if(size > parent.size)
	{
		perror("Size of part a matix can't be bigger than itself!\n");
	}
	else if(parent.size < size + partPosition.first || parent.size < size + partPosition.second)
	{
		perror("Getting part of a matrix error: out of index for too big part position.\n");
	}
	else
	{
		int i, j;
		
		switch(rotationPosition)
		{
			case Rotation::NONE :
				for (i = 0; i < size; ++i)
				{
					for(j = 0; j < size; ++j)
					{
						value[i][j] = parent.value[i + partPosition.first][j + partPosition.second];
					}
				}
				break;
			
			case Rotation::DEG_90 :
				for (i = 0; i < size; ++i)
				{
					for(j = 0; j < size; ++j)
					{
						value[size - 1 - j][i] = parent.value[i + partPosition.first][j + partPosition.second];
					}
				}
				break;
			
			case Rotation::DEG_180 :
				for (i = 0; i < size; ++i)
				{
					for(j = 0; j < size; ++j)
					{
						value[size - 1 - i][size - 1 - j] = parent.value[i + partPosition.first][j + partPosition.second];
					}
				}
				break;
			
			case Rotation::DEG_270 :
				for (i = 0; i < size; ++i)
				{
					for(j = 0; j < size; ++j)
					{
						value[j][size - 1 - i] = parent.value[i + partPosition.first][j + partPosition.second];
					}
				}
				break;
			
			default:
				perror("Getting part of a matrix error: invalid rotation position value.\n");
				break;
		}
	}
}

vector<int> SquareMatrix::CalcSearchedHash()
{
	vector<int> result(ROTATION_NUMBER);
	
	int i, j, colHash;
	
	for(i = 0; i < ROTATION_NUMBER; ++i)
	{
		result[i] = 0;
	}
	
	for(j = 0; j < size; ++j)
	{
		colHash = 0;
		
		for(i = 0; i < size; ++i)
		{
			colHash = (colHash * 2 + value[i][size - 1 - j]) % PRIME_NUMBER; // calculating col hash
		}
		
		result[0] = (result[0] * 2 + colHash) % PRIME_NUMBER; // calculating matrix hash using col hashes
	}
	
	for(j = 0; j < size; ++j)
	{
		colHash = 0;
		
		for(i = 0; i < size; ++i)
		{
			colHash = (colHash * 2 + value[j][i]) % PRIME_NUMBER; // calculating col hash
		}
		
		result[1] = (result[1] * 2 + colHash) % PRIME_NUMBER; // calculating matrix hash using col hashes
	}
	
	for(j = 0; j < size; ++j)
	{
		colHash = 0;
		
		for(i = 0; i < size; ++i)
		{
			colHash = (colHash * 2 + value[size - 1 - i][j]) % PRIME_NUMBER; // calculating col hash
		}
		
		result[2] = (result[2] * 2 + colHash) % PRIME_NUMBER; // calculating matrix hash using col hashes
	}
	
	for(j = 0; j < size; ++j)
	{
		colHash = 0;
		
		for(i = 0; i < size; ++i)
		{
			colHash = (colHash * 2 + value[size - 1 - j][size - 1 - i]) % PRIME_NUMBER; // calculating col hash
		}
		
		result[3] = (result[3] * 2 + colHash) % PRIME_NUMBER; // calculating matrix hash using col hashes
	}
	
	cout << "Searched Hash:" << endl;
	
	for(i = 0; i < ROTATION_NUMBER; ++i)
	{
		cout << result[i] << endl;
	}
	
	return result;
}

vector<pair<int, int>> SquareMatrix::Find(SquareMatrix searched)
{
	vector<pair<int, int>> result; // indexes of matches
	
	if(searched.size > size)
	{
		perror("Searced matrix can't be bigger than field matrix!\n");
	}
	else
	{
		vector<int> searchedHash = searched.CalcSearchedHash();
		
		int i, j, k, l, m, colHash, tempHash, power, colHash2;
		
		for(i = 0; i <= (size - searched.size); ++i)
		{
			cout << "[" << i << "] : [" << 0 << "] : ";
			
			tempHash = 0;
			
			for(l = 0; l < searched.size; ++l)
			{
				colHash = 0;
				
				for(k = 0; k < searched.size; ++k)
				{
					colHash = (colHash * 2 + value[k + i][searched.size - 1 - l]) % PRIME_NUMBER; 
				}
				
				tempHash = (tempHash * 2 + colHash) % PRIME_NUMBER;
			}
			
			cout << tempHash << endl;
			
			for(m = 0; m < ROTATION_NUMBER; ++m)
			{
				if(tempHash == searchedHash[m])
				{
					cout << "Match at [" << i << "] : [" << 0 << "] with hash: " << tempHash << endl;
					result.push_back(make_pair(i, 0));
				}
			}
			
			for(j = 1; j <= (size - searched.size); j++)
			{
				cout << "[" << i << "] : [" << j << "] : ";
				
				colHash = 0; // prev col
				
				colHash2 = 0; // right col
				
				for(k = 0; k < searched.size; ++k)
				{
					colHash = (colHash * 2 + value[i + k][j - 1]) % PRIME_NUMBER; 
					
					colHash2 = (colHash2 * 2 + value[i + k][j + size - 1]) % PRIME_NUMBER; 
				}
				
				power = 1;
				
				for(l = 1; l < searched.size; ++l)
				{
					power *= 2;
				}
				
				power %= PRIME_NUMBER;
				
				tempHash = (((tempHash - (colHash * power)) * 2) + colHash2) % PRIME_NUMBER;
				
				cout << tempHash << endl;
				
				for(m = 0; m < ROTATION_NUMBER; ++m)
				{
					if(tempHash == searchedHash[m])
					{
						cout << "Match at [" << i << "] : [" << j << "] with hash: " << tempHash << endl;
						result.push_back(make_pair(i, j));
					}
				}
			}
		}
	}
	
	return result;
}

void SquareMatrix::print()
{
	int i, j;
	
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size; ++j)
		{
			cout << value[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	srand(time(NULL));
	
	int size = 8u;
	
	cout << "Normal initiation check:" << endl;
	
	SquareMatrix matrix(size);
	
	matrix.print();
	
	cout << "Normal no-turn parting check:" << endl;
	
	matrix.print();
	
	SquareMatrix part(size / 2u, matrix, make_pair(0u, 0u));
	
	part.print();
	
	part = SquareMatrix(size / 2u, matrix, make_pair(size / 2u, size / 2u));
	
	part.print();
	
	part = SquareMatrix(size, matrix, make_pair(0u, 0u));
	
	part.print();
	
	cout << "Invalid parting check:" << endl;
	
	part = SquareMatrix(size + 1, matrix, make_pair(0u, 0u));
	
	part.print();
	
	part = SquareMatrix(size / 2u, matrix, make_pair(size / 2u + 1, size / 2u));
	
	part.print();
	
	part = SquareMatrix(size / 2u, matrix, make_pair(size / 2u, size / 2u + 1));
	
	part.print();
	
	part = SquareMatrix(size / 2u, matrix, make_pair(size / 2u + 1, size / 2u + 1));
	
	part.print();
	
	cout << "Normal 90-turn parting check:" << endl;
	
	matrix.print();
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 0u), Rotation::DEG_90);
	
	part.print();
	
	cout << "Normal 180-turn parting check:" << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 0u), Rotation::DEG_180);
	
	part.print();
	
	cout << "Normal 270-turn parting check:" << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 0u), Rotation::DEG_270);
	
	part.print();
	
	cout << "Testing finding:" << endl;
	
	cout << endl << "[0] : [0] no turn testing" << endl << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 0u), Rotation::NONE);
	
	matrix.print();
	
	part.print();
	
	matrix.Find(part);
	
	cout << endl << "[0] : [0] 90 - turn testing" << endl << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 0u), Rotation::DEG_90);
	
	matrix.Find(part);
	
	cout << endl << "[0] : [0] 180 - turn testing" << endl << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 0u), Rotation::DEG_180);
	
	matrix.Find(part);
	
	cout << endl << "[0] : [0] 270 - turn testing" << endl << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 0u), Rotation::DEG_270);
	
	matrix.Find(part);
	
	cout << endl << "[1] : [0] no turn testing" << endl << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(1u, 0u), Rotation::NONE);
	
	matrix.Find(part);
	
	cout << endl << "[0] : [1] no turn testing" << endl << endl;
	
	part = SquareMatrix(size / 2, matrix, make_pair(0u, 1u), Rotation::NONE);
	
	matrix.print();
	
	part.print();
	
	matrix.Find(part);
	
	cout << "searching succesfully" << endl;
	
	system("pause");
	
	return 0;
}

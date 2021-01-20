#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// last symbol of string[size] is \0, so match up to size - 1

vector<unsigned> NaiveStringMatcher(string text, string phrase)
{
	vector<unsigned> matchFirstPositions(0);
	
	unsigned textLength = text.length();
	unsigned phraseLength = phrase.length();
	
	if(textLength == 0)
	{
		perror("Invalid input: text has 0 length\n");
	}
	else if(phraseLength == 0)
	{
		perror("Invalid input: phrase has 0 length\n");
	}
	else if(textLength < phraseLength)
	{
		perror("Invalid input: text must be not smaller than phrase\n");
	}
	else
	{
		bool flag;
		
		unsigned diff = textLength - phraseLength;
		
		unsigned i, j;
		
		for(i = 0; i <= diff; ++i)
		{
			flag = true;
			
			for(j = 0; j < phraseLength; ++j)
			{
				if(text[i + j] != phrase[j])
				{
					flag = false;
				}
			}
			if(flag)
			{
				matchFirstPositions.push_back(i);
			}
		}
	}
	
	return matchFirstPositions;
}

vector<unsigned> ShiftTable(string phrase)
{
	unsigned phraseSize = phrase.size();
	
	vector<unsigned> shiftTable(UCHAR_MAX + 1, phraseSize);
	
	for(unsigned i = 0; i <= phraseSize - 2; ++i)
	{
		shiftTable[(unsigned char)phrase[i]] = phraseSize - 1 - i;
	}
	
	return shiftTable;
}

vector<unsigned> HorspoolStringMatcher(string text, string phrase)
{
	vector<unsigned> matchFirstPositions(0);
	
	unsigned textLength = text.length();
	unsigned phraseLength = phrase.length();
	
	if(textLength == 0)
	{
		perror("Invalid input: text has 0 length\n");
	}
	else if(phraseLength == 0)
	{
		perror("Invalid input: phrase has 0 length\n");
	}
	else if(textLength < phraseLength)
	{
		perror("Invalid input: text must be not smaller than phrase\n");
	}
	else
	{
		vector<unsigned> shiftTable = ShiftTable(phrase);
		
		unsigned i = phraseLength - 1;
		
		unsigned k;
		
		while(i <= textLength - 1)
		{
			k = 0;
			
			while(k <= phraseLength - 1 && phrase[phraseLength - 1 - k] == text[i - k])
			{
				k++;
			}
			
			if(k == phraseLength)
			{
				matchFirstPositions.push_back(i - phraseLength + 1);
			}
			
			i += shiftTable[(unsigned char)text[i]];
		}
	}
	
	return matchFirstPositions;
}

vector<unsigned> SuffixShift(string phrase)
{
	unsigned phraseLength = phrase.length();
	
	vector<unsigned> suffixShift(phraseLength, phraseLength);
	
	bool flag;
	
	long i, j, h, k;
	
	for(i = 1; i < phraseLength; ++i)
	{
		for(j = phraseLength - i - 1; j >=0; j--)
		{
			flag = true;
			
			for(h = 0; h < i; ++h)
			{
				if(phrase[j + h] != phrase[phraseLength - i + h])
				{
					flag = false;
				}
			}
			
			if(flag)
			{
				suffixShift[i] = phraseLength - (j + i);
				break;
			}
		}
		
		if(suffixShift[i] == phraseLength)
		{
			for(k = i - 1; k > 0; k--)
			{
				flag = true;
				
				for(h = 0; h < k; ++h)
				{
					if(phrase[h] != phrase[phraseLength - k + h])
					{
						flag = false;
					}
				}
				
				if(flag)
				{
					suffixShift[i] = phraseLength - k;
					break;
				}
			}
		}
	}
	
	return suffixShift;
}

vector<unsigned> BoyerMooreStringMatcher(string text, string phrase)
{
	vector<unsigned> matchFirstPositions(0);
	
	unsigned textLength = text.length();
	unsigned phraseLength = phrase.length();
	
	if(textLength == 0)
	{
		perror("Invalid input: text has 0 length\n");
	}
	else if(phraseLength == 0)
	{
		perror("Invalid input: phrase has 0 length\n");
	}
	else if(textLength < phraseLength)
	{
		perror("Invalid input: text must be not smaller than phrase\n");
	}
	else
	{
		vector<unsigned> shiftTable = ShiftTable(phrase);
		
		vector<unsigned> suffixShift = SuffixShift(phrase);
		
		unsigned i = phraseLength - 1;
		
		unsigned k;
		unsigned d, d1, d2;
		
		while(i <= textLength - 1)
		{
			k = 0;
			
			while(k <= phraseLength - 1 && phrase[phraseLength - 1 - k] == text[i - k])
			{
				k++;
			}
			
			if(k == phraseLength)
			{
				matchFirstPositions.push_back(i - phraseLength + 1);
			}
			
			if(k==0)
			{
				d1 = shiftTable[(unsigned char)text[i]];
				
				if(d1 == 0)
				{
					d = 1;
				}
				else
				{
					d = d1;
				}
			}
			else
			{
				d1 = shiftTable[(unsigned char)text[i - k]] - k;
				d2 = suffixShift[k];
				
				if(d1 > d2)
				{
					d = d1;
				}
				else
				{
					d = d2;
				}
			}
			
			i += d;
		}
	}
	
	return matchFirstPositions;
}

int main()
{
	string s1 = "hello";
	cout << s1 << endl;
	cout << s1.size() << endl;
	char c1 = CHAR_MIN;
	cout << c1 << " | " << (int)c1 << endl;
	c1 = CHAR_MAX;
	cout << c1 << " | " << (int)c1 << endl;
	c1 = 0;
	cout << c1 << " | " << (int)c1 << endl;
	c1 = 1;
	cout << c1 << " | " << (int)c1 << endl;
	cout << "======================" << endl;
	unsigned char c2 = 0;
	cout << c2 << " | " << (int)c2 << endl;
	c2 = 1;
	cout << c2 << " | " << (int)c2 << endl;
	c2 = 127;
	cout << c2 << " | " << (int)c2 << endl;
	c2 = 128;
	cout << c2 << " | " << (int)c2 << endl;
	c2 = 255;
	cout << c2 << " | " << (int)c2 << endl;
	c2 = UCHAR_MAX;
	cout << c2 << " | " << (int)c2 << endl;
	c2 = 150;
	cout << c2 << " | " << (int)c2 << endl;
	
	cout << "======================" << endl;
	
	string phrase = "BARBER";
	string text = "JIM_SAW_ME_IN_A_BARBERSHOP";
	
	vector<unsigned> shiftTable = ShiftTable(phrase);
	for(unsigned c = 0; c <= UCHAR_MAX; ++c)
	{
		cout << (unsigned char)c << " : " << shiftTable[(unsigned char)c] << endl;
	}
	
	cout << "Phrase:" << endl << phrase << endl;
	cout << "Text:" << endl << text << endl;
	
	vector<unsigned> naive = NaiveStringMatcher(text, phrase);
	
	cout << "Naive results:" << endl;
	for(unsigned i = 0; i < naive.size(); ++i)
	{
		cout << naive[i] << endl;
	}
	
	vector<unsigned> horspool = HorspoolStringMatcher(text, phrase);
	
	cout << "Horspool results:" << endl;
	for(unsigned i = 0; i < horspool.size(); ++i)
	{
		cout << horspool[i] << endl;
	}
	
	string prefixTest = "BAOBAB";
	
	cout << "Testing prefix table: " << prefixTest << endl;
	
	vector<unsigned> prefixTable = SuffixShift(prefixTest);
	
	for(int i = 1; i < prefixTable.size(); ++i)
	{
		cout << i << " : " << prefixTable[i] << endl;
	}
	
	prefixTest = "ABCBAB";
	
	cout << "Testing prefix table: " << prefixTest << endl;
	
	prefixTable = SuffixShift(prefixTest);
	
	for(int i = 1; i < prefixTable.size(); ++i)
	{
		cout << i << " : " << prefixTable[i] << endl;
	}
	
	vector<unsigned> BoyerMoore = BoyerMooreStringMatcher(text, phrase);
	
	cout << "Boyer0Moore results:" << endl;
	for(unsigned i = 0; i < BoyerMoore.size(); ++i)
	{
		cout << BoyerMoore[i] << endl;
	}
	
	return 0;
}

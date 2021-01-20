#include <iostream>
#include <vector>

using namespace std;

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

bool HorspoolStringMatcher(string text, string phrase)
{
	bool result = false;
	
	unsigned textLength = text.length();
	unsigned phraseLength = phrase.length();

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
			result = true;
			break;
		}
		
		i += shiftTable[(unsigned char)text[i]];
	}
	
	return result;
}



int main()
{
	string s;
	bool isInvalid;
	do
	{
		isInvalid = false;
		cout << "Input first string: ";
		cin >> s;
		if(s.size() < 2)
		{
			isInvalid = true;
			cout << "String must have at least 2 symbols!" << endl;
		}
	}
	while(isInvalid);
	
	string s1;
	
	do
	{
		isInvalid = false;
		cout << "Input second string: ";
		cin >> s1;
		if(s1.size() < 2)
		{
			isInvalid = true;
			cout << "String must have at least 2 symbols!" << endl;
		}
	}
	while(isInvalid);
	
	if(s.size() != s1.size())
	{
		cout << "Strings must be same size!" << endl;
	}
	else
	{
		string s2 = s1 + s1;
		auto iter = s2.begin();
		s2.erase(iter);
		iter = s2.end();
		s2.erase(iter - 1);
		
		cout << "Double string: " << s2 << endl;
		
		if(HorspoolStringMatcher(s2, s))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	
	return 0;
}

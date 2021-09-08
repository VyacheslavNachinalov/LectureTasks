#include <iostream>
#include "strutil.h"

using namespace std;

int testOneSymbol()
{
	char a[] = "c";
	char b[] = "e";
	char str[] = "abcde";
	if ((strConteins(a, str) == 2) && (strConteins(b, str) == 4))
	{
		return 0;
	}
	else return -1;
}

int testManySymbols()
{
	char a[] = "def";
	char b[] = "fgh";
	char c[] = "jkl";
	char str[] = "abcdefgh";
	if ((strConteins(a, str) == 3) && (strConteins(b, str) == 5) && (strConteins(c,str) == -1))
	{
		return 0;
	}
	else return -1;
}


int testTooManySymbols()
{
	char a[] = "abcdefgh";
	char str[] = "abc";
	if (strConteins(a, str) == -1)
	{
		return 0;
	}
	return -1;
}

void successTest(int nameTest())
{
	if (nameTest() == 0)
	{
		cout << "test is OK" << endl;
	}
	else
	{
		cout << "test is Fail" << endl;
	}
}

int main()
{
	successTest(testOneSymbol);
	successTest(testManySymbols);
	successTest(testTooManySymbols);
	return 0;
}

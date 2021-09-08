#include <iostream>
#include "strutil.h"

using namespace std;

int strConteins(char* a, char* str)
{
	int n = strlen(str) - strlen(a) + 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < strlen(a); j++)
		{
			if (a[j] != str[i+j])
			{
				break;
			}
			else if (j == strlen(a) -1)
			{
				return i;
			}
		}
	}
	return -1;
}

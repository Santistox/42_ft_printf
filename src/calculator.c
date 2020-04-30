#include <stdio.h>

/*
**  print int massive
*/

void print_num(int *num, int i, char a)
{
	int k;

	k = 0;
	while (k != i)
	{
		printf("%i", num[k]);
		k++;
	}
	printf("%c", a);
}

/*
**  addition by a column
*/

void add_by_column(int *num1, int *num2, int *rez, int bit)
{
	int i;
	int buf;

	i = bit;
	buf = 0;
	while (i-- >= 0)
	{
		rez[i] += buf;
		rez[i] = (num1[i] + num2[i] + buf) % 10;
		buf = (num1[i] + num2[i] + buf) / 10;
	}
}

/*
**  multiplication by a column
*/

void multiplication_by_column(int *num1, int *num2, int *rez, int bit)
{
	int i;
	int j;
	int k;
	int buf;
	
	i = bit;
	buf = 0;
	while (i-- >= 0)
	{
		j = bit;
		k = i + 1;
		while (j-- >= 0 && k-- >=0)
		{
			rez[k] += buf;
			rez[k] += (num1[j] * num2[i]);
			buf = rez[k] / 10;
			rez[k] = rez[k] % 10;
		}
	}
}

int main(void)
{
	int num1[] = {0, 0, 0, 0, 0, 0, 0, 1, 2}; // num 1
	int num2[] = {0, 0, 0, 0, 0, 0, 0, 1, 5}; // num 2
	int rez1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // addition result
	int rez2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // multiplication result
	print_num(num1, 9, '\n');
	print_num(num2, 9, '\n');
	add_by_column(num1, num2, rez1, 9);
	multiplication_by_column(num1, num2, rez2, 9);
	print_num(rez1, 9, '\n');
	print_num(rez2, 9, '\n');
	return(0);
}
#include <stdio.h>

void print_num(int *num, int i, char a)
{
	int k = 0;
	while (k != i)
	{
		printf("%i", num[k]);
		k++;
	}
	printf("%c", a);
}

void add_by_column(int *num1, int *num2, int *rez)
{
	int i;
	int buf;

	i = 9;
	buf = 0;
	while (i-- >= 0)
	{
		rez[i] += buf;
		rez[i] = (num1[i] + num2[i] + buf) % 10;
		buf = (num1[i] + num2[i] + buf) / 10;
	}
}

void multiplication_by_column(int *num1, int *num2, int *rez)
{
	int i;
	int j;
	int k;
	int buf;
	

	i = 9;
	buf = 0;
	while (i-- >= 0)
	{
		j = 9;
		k = i + 1;
		while (j-- >= 0 && k-- >=0)
		{
			//print_num(rez, 9, ' ');
			//printf("%i ", num1[j]);
			//printf(" {%i}{%i}{%i} | %i - %i - %i - %i\n", i, j, k, buf, rez[k], num1[j], num2[i]);
			rez[k] += buf;
			rez[k] += (num1[j] * num2[i]);
			buf = rez[k] / 10;
			rez[k] = rez[k] % 10;
		}
	}
}

int main(void)
{
	int num1[] = {0, 0, 0, 0, 0, 0, 0, 1, 2};
	int num2[] = {0, 0, 0, 0, 0, 0, 0, 1, 5};
	int rez1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int rez2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	print_num(num1, 9, '\n');
	print_num(num2, 9, '\n');
	add_by_column(num1, num2, rez1);
	multiplication_by_column(num1, num2, rez2);
	print_num(rez1, 9, '\n');
	print_num(rez2, 9, '\n');
	return(0);
}
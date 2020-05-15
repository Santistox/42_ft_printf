#include "ft_printf.h"
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
 
void add_by_column(int *num1, int *num2, int *rez, int *bit)
{
    int i;
    int j;
    int buf;
 
    i = bit[0];
    j = bit[1];
    buf = 0;
    while (--i >= 0)
    {
        j--;
        rez[j] += buf;
        rez[j] = (num1[i] + num2[j] + buf) % 10;
        buf = (num1[i] + num2[j] + buf) / 10;
    }
    rez[--j] += buf;
}
 
/*
**  multiplication by a column
*/
/*
void copy_int(int *num1, int *num2, int bit)
{
    int i;
 
    i = bit;
    while (--i >= 0)
        num1[i] = num2[i];
}

void    *ft_memset(void *b, int c, size_t len)
{
    unsigned char *temp;
 
    temp = (unsigned char *)b;
    while (len--)
        *temp++ = (unsigned char)c;
    return (b);
}
 
int *new_arr(long long unsigned int num, int bit)
{
    int i;
    int *arr;
 
    i = bit - 1;
    if (!(arr = malloc(sizeof(int *) * bit)))
        printf("FUCK\n");
    if (!(arr = ft_memset(arr, 0, bit)))
        printf("FUCK\n");
    while (i >= 0 && num >= 0)
    {
        arr[i] = num % 10;
        num /= 10;
        i--;
    }
    return (arr);
}
*/
int cut_num(int **num, int bit)
{
    int i;
    int k;
    int *tmp;

    i = 0;
    tmp = new_arr(0, bit);
	copy_int(tmp, *num, bit);
    while((*num)[i] == 0 && i < bit)
        i++;
    free(*num);
    k = bit - i;
    *num = new_arr(0, k);
    int j = 0;
    while (i < bit && j < k)
    {
        (*num)[j] = tmp[i];
        i++;
        j++;
    }
    free(tmp);
    return(k);
}

// int bit[3] = {x,y,z}
//  x - size of num1
//  y - size of num2
//  z - size of rez
void mult_by_column(int *num1, int *num2, int *rez, int *bit)
{
    int i;
    int j;
    int k;
    int f;
    int buf;
 
    i = bit[1];
    buf = 0;
    f = bit[2] - 1;
    while (i-- >= 0)
    {
        j = bit[0];
        k = f;
        while (j-- >= 0)
        {
            rez[k] += buf;
            if (j >= 0 && i >= 0)
                rez[k] += (num1[j] * num2[i]);
            buf = rez[k] / 10;
            rez[k] = rez[k] % 10;
            k -= 1;
        }
        f--;
    }
}
/*
int main(void)
{
    int bit[3] = {10,15,0};
    int *num1 = new_arr(9999,bit[0]);
    int *num2 = new_arr(9999,bit[1]);
    bit[2] = bit[0] + bit[1];
    int *rez = new_arr(0,bit[2]);
    //cut_num(&num1, bit[0]);
    print_num(num1, bit[0], '\n');
    print_num(num2, bit[1], '\n');
    mult_by_column(num1, num2, rez, bit);
    bit[2] = cut_num(&rez, bit[2]);
    print_num(rez, bit[2], '\n');
    return(0);
}*/
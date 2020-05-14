#include "ft_printf.h"

/*
** function copy numbers form num1 array to num2 array
*/

void copy_int(int *num1, int *num2, int bit)
{
    int i;
 
    i = bit;
    while (--i >= 0)
        num1[i] = num2[i];
}

/*
** function reset to 0 numbers form int array
*/

void reset_int(int *num, int bit)
{
	int i;

	i = bit;
	while (i-- >= 0)
		num[i] = 0;
}

/*
** exponentiation of the number in the array
*/

int *binpow(int num, int pow, int bit)
{
	int *num1;
	int *num2;
	int *res;
	int *bits;

	bits = new_arr(0,3);
	bits[0] = bit;
	bits[1] = bit;
	bits[2] = bit;
	num1 = new_arr(num, bits[0]);
	num2 = new_arr(num, bits[1]);
	res = new_arr(0, bits[2]);
	while (pow-- > 1)
	{
		reset_int(res, bit);
		mult_by_column(num1, num2, res, bits);
		copy_int(num1, res, bit);
	}
	free(num1);
	free(num2);
	free(bits);
	return(res);
}

/*
**	create int array and stack each character of number to cell
*/

int *new_arr(long long unsigned int num, int bit)
{
	int i;
	int *arr;

	i = bit - 1;
	if (!(arr = malloc(sizeof(int *) * bit)))
		error(403);
	if (!(arr = ft_memset(arr, 0, bit)))
		error(403);
	while (i >= 0 && num >= 0)
	{
		arr[i] = num % 10;
		num /= 10;
		i--;
	}
	return (arr);
}
// заранее чeкаем пресишн есть вообще
int *prec(int *num, int prec, t_fenv *fenv) //int prec, int compos, int bit)
{
	int *add;
	int *res;

	if (fenv->compos + prec >= fenv->res_bit || !num)
		return (num);
	if (num[fenv->compos + prec] < 5)
		return (num);
	add = new_arr(0, fenv->compos + prec);
	add[fenv->compos + prec - 1] = 1;
	res = new_arr(0, fenv->compos + prec);
	add_by_column(num, add, res, fenv->compos + prec);
	free(num);
	free(add);
	return (res);
}

/*
**	move float number to buffer from int array
*/

void	to_buff_float(t_env *env, t_fenv *fenv, int *num)
{
	int  i;

	i = 0;
	while (i <= fenv->bit && num[i] == 0 && i + 1 < fenv->compos)
		i++;
	while (i < fenv->bit && i < fenv->compos + env->precision)
	{
		if (i == fenv->compos)
			to_buff_char('.', env);
		to_buff_char(num[i] + '0', env);
		i++;
	}
}

/*
** determines the size of a number
*/

int 	num_size(t_env *env, t_fenv *fenv, int *num)
{
	int  i;
	int  k;

	i = 0;
	k = 0;
	while (i <= fenv->bit && num[i] == 0)
		i++;
	while (i < fenv->bit && i < fenv->compos + env->precision)
	{
		if (i == fenv->compos)
			k++;
		k++;
		i++;
	}
	return(k);
}

t_fenv *init_fenv(int bit, unsigned long int num)
{
	t_fenv *fenv;

	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		error(403);
	fenv->bit = bit;
	fenv->res_bit = bit;
	if (num == 0)
	{
		fenv->exp_num = 0; 
		fenv->mant_num = 0;
		fenv->sign = 0;
		fenv->exp = 0;
		fenv->compos = 1; // насчет этого уже хз 
		return (fenv);
	}
	fenv->exp_num = 1023; 
	fenv->mant_num = 52;
	fenv->sign = num >> (bit - 1);
	fenv->exp = num << 1; // 
//	printf("exp1 %lu\n", fenv->exp);
	fenv->exp = fenv->exp >> (fenv->mant_num + 1);
//	printf("exp2 %lu\n", fenv->exp);
	fenv->exp = fenv->exp - (fenv->exp_num);
	fenv->compos = fenv->bit - (fenv->mant_num - fenv->exp);
	return (fenv);
}

/*
** write formatted result to buffer
*/

void	float_output(t_env *env, t_fenv *fenv, int *res)
{
	env->offset -= num_size(env, fenv, res);
	if (fenv->sign && env->zero)
		to_buff_char('-', env);
	env->offset -= (fenv->sign && !env->space) ? 1 : 0;
	env->offset -= (!fenv->sign && env->plus) ? 1 : 0;
	if (!env->minus && !env->zero)
		to_buff_offset(env);
	if (env->plus && !fenv->sign)
		to_buff_char('+', env); 
	if (fenv->sign && !env->zero)
		to_buff_char('-', env); 
	if (!fenv->sign && env->space && !env->plus)
		to_buff_char(' ', env);
	if (env->zero)
		put_zero(env); 
	to_buff_float(env, fenv, res);
	if (env->precision == 0 && env->grille)
		to_buff_char('.', env);
	env->offset -= (env->precision == 0 && env->grille) ? 1 : 0;
	if (env->minus)
		to_buff_offset(env);
}

void	flag_f(t_env *env, va_list args)
{
	t_fenv *fenv;
	unsigned long int *ptr;
	unsigned long int num;
	unsigned long long int mant;
	double	cont;

	cont = (double)va_arg(args, double);
//	printf("CONT %.9f\n", cont);
	ptr = (unsigned long int *)&cont;
	num = *ptr;
	//printf("NUM is %lu\n", num);
	fenv = init_fenv(64, *ptr);
	mant = 0;
	if (fenv->bit == 64 && num != 0)
	{
		mant = num & 4503599627370495;
		mant = mant | 4503599627370496;
	}
	/* DEBUG */
	printf("COMPOS is %i\n", fenv->compos);
	printf("MANT is %llu\n", mant); 
	printf("EXP is %lu\n", fenv->exp);
	printf("SIGN is %u\n", fenv->sign);


	int *arr = new_arr((long long unsigned int)mant, fenv->bit);
	int *n;
	n = NULL;
	int bit = fenv->bit;
	if (fenv->mant_num - fenv->exp >= 0)
		n = binpow(5, fenv->mant_num - fenv->exp, fenv->bit);
	else
		n = binpow(2, fenv->exp - fenv->mant_num, fenv->bit);
	fenv->bit = bit;
	fenv->bits = new_arr(0,3);
	fenv->bits[0] = fenv->bit;
	fenv->bits[1] = fenv->bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];

	int *res = new_arr((long long unsigned int)0, fenv->bit);
	mult_by_column(arr, n, res, fenv->bits);
	fenv->bits[2] = cut_num(&res, fenv->bits[2]);

	if (num != 0)
		fenv->compos = fenv->res_bit - (fenv->mant_num - fenv->exp);

	/* DEBUG */
//	print_num(res, fenv->bit, '\n');
	if (!env->is_precision)
	{
		env->is_precision = 1;
		env->precision = 6;
	}

	res = prec(res, env->precision, fenv); 
	
	/* DEBUG */
	print_num(res, fenv->compos + env->precision, '\n');

	/* KOLHOZING */
	//float_output(env, fenv, res);


//	printf("%f!\n", cont);
	free(arr);
	free(n);
	free(res);
	free(fenv);
}
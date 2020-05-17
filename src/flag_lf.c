#include "ft_printf.h"

/*
** function algorithm selection
*/

void	float_flags(t_env *env, va_list args)
{
	if (env->str[env->count] == 'L')
	{
		env->count++;
		if (env->str[env->count] == 'f')
			flag_lf(env, args);
	}
	else if (env->str[env->count] == 'f')
		flag_f(env, args);
}

/*
** function of long float
*/
/*
int 	valid_float(long long int exp, uintmax_t mant)
{
	unsigned char check;

	check = *mant + 3;
	check = check & 49152;
	if (exp == 0)
		if (mant == 0)
			return (3);
	else if (exp == 32767)
	{
		if (mant == 0)
			return (2);
		if (check == 2)
	}
	return (0);
}*/

void	flag_lf(t_env *env, va_list args)
{	
	t_fenv *fenv;
	unsigned short *short_ptr;
	unsigned long int *ptr;
	unsigned long int sig;
	uintmax_t mant;
	long double	cont;
	int *arr;

	cont = (long double)va_arg(args, long double);
	short_ptr = (unsigned short *)&cont;
	ptr = (unsigned long int *)&cont;
	short_ptr = short_ptr + 4;
	mant = *ptr;
	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		error(403);
	fenv->bit = 80;
	fenv->res_bit = 80;
	fenv->exp_num = 16383; 
	fenv->mant_num = 64;
	
	sig = *short_ptr;
	fenv->sign = sig >> 15;
	fenv->exp_res = sig & 32767;
//	if (valid_float(fenv->exp_res, mant) == 0)
//	{
		fenv->exp_res = fenv->exp_res - (fenv->exp_num);
		fenv->compos = fenv->res_bit - (fenv->mant_num - fenv->exp_res);
		arr = new_arr((long long unsigned int)mant, fenv->bit);
//		print_num(arr, fenv->bit, '\n');
//	} else {

//	}

//	printf("sign is %i\n", fenv->sign);
//	printf("mant is %lu\n",mant);
//	printf("exp is %lli\n",fenv->exp_res);
//	printf("compos is %i\n",fenv->compos);
//	printf("%.30Lf DEBUG of %c\n", cont, env->str[env->count]);

	int *n;
	n = NULL;
	fenv->bits = new_arr(0,3);
	fenv->bits[0] = fenv->bit;
	fenv->bits[1] = 2 * fenv->bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];
	int bit = fenv->bit;
	if (fenv->mant_num - fenv->exp_res - 1>= 0)
		n = binpow(5, fenv->mant_num - fenv->exp_res - 1, fenv->bits[1]);
	else
		n = binpow(2, fenv->exp_res - fenv->mant_num - 1, fenv->bits[1]);
	fenv->bit = bit;
	
	int *res = new_arr((long long unsigned int)0, fenv->bits[2]);
	mult_by_column(arr, n, res, fenv->bits);
	fenv->bits[2] = cut_num(&res, fenv->bits[2]);
	fenv->res_bit = fenv->bits[2];

	if (!env->is_precision)
	{
		env->is_precision = 1;
		env->precision = 6;
	}
	fenv->compos = fenv->res_bit - (fenv->mant_num - 1 - fenv->exp_res);
//	printf("compos is %i\n",fenv->compos);
	res = prec(res, env->precision, fenv); 
//	print_num(res, fenv->bits[2], '\n');
	float_output(env, fenv, res);

	free(arr);
	free(n);
	free(res);
	free(fenv);
}

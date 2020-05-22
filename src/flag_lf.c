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

void	flag_lf(t_env *env, va_list args)
{	
	t_fenv *fenv;
	unsigned short *short_ptr;
	ul_t *ptr;
	ul_t sig;
	uintmax_t mant;
	long double	cont;
	int *arr;

	arr = NULL;
	cont = (long double)va_arg(args, long double);
	short_ptr = (unsigned short *)&cont;
	ptr = (ul_t *)&cont;
	short_ptr = short_ptr + 4;
	mant = *ptr;
	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		malloc_error();
	fenv->bit = 80;
	fenv->res_bit = 80;
	fenv->exp_num = 16383; 
	fenv->mant_num = 64;
	
	sig = *short_ptr;
	fenv->sign = sig >> 15;
	fenv->exp_res = sig & 32767;
	if (cont == 0)
	{
		float_zero(fenv, env);
		free_fenv(fenv);
		free(fenv);
		return ;
	}
	fenv->exp_res = fenv->exp_res - (fenv->exp_num);
	fenv->compos = fenv->res_bit - (fenv->mant_num - fenv->exp_res);
	arr = new_arr((long long unsigned int)mant, fenv->bit);


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
	res = prec(res, env->precision, fenv); 
	float_output(env, fenv, res);

	free(arr);
	free(n);
	free(res);
	free(fenv);
}

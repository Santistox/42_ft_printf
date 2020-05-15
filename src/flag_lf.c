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
	long long int exp;
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
	exp = sig & 32767;
//	if (valid_float(exp, mant) == 0)
//	{
		exp = exp - (fenv->exp_num);
		fenv->compos = fenv->res_bit - (fenv->mant_num - exp);
		arr = new_arr((long long unsigned int)mant, fenv->bit);
		print_num(arr, fenv->bit, '\n');
//	} else {

//	}

//	printf("sign is %i\n", fenv->sign);
//	printf("mant is %lu\n",mant);
//	printf("exp is %lli\n",exp);
//	printf("compos is %i\n",fenv->compos);
	printf("%.30Lf DEBUG of %c\n", cont, env->str[env->count]);

}

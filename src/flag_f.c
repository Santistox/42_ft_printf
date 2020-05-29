#include "ft_printf.h"

/*
** function copy numbers form num1 array to num2 array
*/

void	copy_int(int *num1, int *num2, int bit1, int bit2)
{
	int i;
	int j;

	i = bit1;
	j = bit2;
	while (--i >= 0 && --j >= 0)
	{
		num1[i] = num2[j];
	}
}

/*
** function reset to 0 numbers form int array
*/

void	reset_int(int *num, int bit)
{
	int i;

	i = bit;
	while (i-- >= 0)
		num[i] = 0;
}

/*
** exponentiation of the number in the array
*/

void	wider_arr(int **res, int **num1, int *bits)
{
	int *tmp;

	free(*res);
	bits[2] = bits[2] + bits[2] / 3;
	*res = new_arr(0, bits[2]);
	tmp = new_arr(0, bits[2]);
	copy_int(tmp, *num1, bits[2], bits[0]);
	bits[0] = bits[2];
	free(*num1);
	*num1 = new_arr(0, bits[0]);
	copy_int(*num1, tmp, bits[0], bits[0]);
	free(tmp);
}

void	binpow_help(int *bits, int bit)
{
	bits[0] = bit;
	bits[1] = bit;
	bits[2] = bit;
}

void	binpow_help_free(int **num1, int **bits, int **num2)
{
	free(*num1);
	free(*num2);
	free(*bits);
}

int		*binpow(int num, int pow, int *bit)
{
	int *num1;
	int *num2;
	int *res;
	int *bits;

	bits = new_arr(bit[1], 3);
	binpow_help(bits, bit[1]);
	num1 = new_arr(num, bits[0]);
	num2 = new_arr(num, bits[1]);
	res = (pow == 0 ? new_arr(1, bits[2]) : new_arr(0, bits[2]));
	while (pow-- > 1)
	{
		if (res[10] == 0)
		{
			free(res);
			res = new_arr(0, bits[2]);
		}
		else
			wider_arr(&res, &num1, bits);
		mult_by_column(num1, num2, res, bits);
		copy_int(num1, res, bits[0], bits[2]);
	}
	bit[1] = bits[2];
	binpow_help_free(&num1, &bits, &num2);
	return (res);
}

/*
**	create int array and stack each character of number to cell
*/

int		*new_arr(ULL num, int bit)
{
	int i;
	int *arr;

	i = bit - 1;
	if (!(arr = malloc(sizeof(int *) * bit)))
		malloc_error();
	if (!(arr = ft_memset(arr, 0, bit)))
		malloc_error();
	while (i >= 0 && num >= 0)
	{
		arr[i] = num % 10;
		num /= 10;
		i--;
	}
	return (arr);
}

int		*prec(int *num, int prec, t_fenv *fenv)
{
	int *add;
	int *res;
	int extra;
	int compos;
	int *res_bit;

	compos = fenv->compos;
	extra = (compos + prec == 0) ? 2 : 1;
	if (fenv->compos + prec >= fenv->res_bit || !num)
		return (num);
	if (num[fenv->compos + prec] < 5)
		return (num);
	add = new_arr(0, compos + prec + extra);
	add[compos + prec + extra - 1] = 1;
	res = new_arr(0, compos + prec + extra);
	res_bit = new_arr(0, 1);
	res_bit[0] = compos + prec + extra - 1;
	res_bit[1] = compos + prec + extra;
	add_by_column(num, add, res, res_bit);
	free(num);
	free(add);
	if (cut_num(&res, compos + prec + extra) == compos + prec + extra)
		fenv->compos++;
	return (res);
}

/*
**	move float number to buffer from int array
*/

void	to_buff_float_help(t_env *env, t_fenv *fenv, int *num)
{
	int i;

	i = 0;
	while (i < fenv->res_bit && i < fenv->compos + env->precision)
	{
		if (i == fenv->compos)
			to_buff_char('.', env);
		to_buff_char(num[i++] + '0', env);
	}
	while (i < fenv->compos + env->precision)
	{
		if (i++ == fenv->compos)
			to_buff_char('.', env);
		to_buff_char('0', env);
	}
}

void	to_buff_float(t_env *env, t_fenv *fenv, int *num)
{
	int i;
	int prec;

	i = 0;
	prec = env->precision;
	if (fenv->compos <= 0)
	{
		to_buff_char('0', env);
		if (prec != 0)
			to_buff_char('.', env);
		while ((fenv->compos)++ < 0 && prec-- > 0)
			to_buff_char('0', env);
		while (prec-- > 0)
			to_buff_char(num[i++] + '0', env);
	}
	else
		to_buff_float_help(env, fenv, num);
}

/*
** determines the size of a number
*/

int		num_size(t_env *env, t_fenv *fenv, int *num)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if (fenv->compos < 0)
		return (env->precision + 2);
	if (fenv->compos == 0)
		k++;
	while (i <= fenv->bit && num[i] == 0)
		i++;
	while (i < fenv->bit && i < fenv->compos + env->precision)
	{
		if (i == fenv->compos)
			k++;
		k++;
		i++;
	}
	return (k);
}

void	free_fenv(t_fenv *fenv)
{
	fenv->bit = 0;
	fenv->sign = 0;
	fenv->res_bit = 0;
	fenv->compos = 0;
	fenv->exp_num = 0;
	fenv->mant_num = 0;
	fenv->exp = 0;
	fenv->exp_res = 0;
	free(fenv->bits);
}

t_fenv	*init_fenv(int bit, UL num)
{
	t_fenv	*fenv;

	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		malloc_error();
	fenv->bit = bit;
	fenv->res_bit = bit;
	fenv->exp_num = 1023;
	fenv->mant_num = 52;
	fenv->sign = num >> (bit - 1);
	fenv->exp = num << 1;
	fenv->exp = fenv->exp >> (fenv->mant_num + 1);
	fenv->exp_res = fenv->exp - (fenv->exp_num);
	fenv->compos = fenv->bit - (fenv->mant_num - fenv->exp_res);
	fenv->bits = new_arr(0, 3);
	fenv->bits[0] = fenv->bit;
	fenv->bits[1] = 2 * fenv->bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];
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

void	float_zero(t_fenv **fenv, t_env *env)
{
	int *res;
	int i;

	i = 0;
	if (!env->is_precision)
	{
		env->is_precision = 1;
		env->precision = 6;
	}
	if (!(res = (int*)malloc(sizeof(int*) * env->precision)))
		return ;
	while (i < env->precision)
	{
		res[i] = 0;
		i++;
	}
	(*fenv)->compos = -1;
	float_output(env, *fenv, res);
	free_fenv(*fenv);
	free(*fenv);
}

int		valid_float(t_fenv *fenv, ULL mant)
{
	if (fenv->mant_num - fenv->exp_res == -972
		&& mant == 4503599627370496 && fenv->sign == 0)
		return (1);
	else if (fenv->mant_num - fenv->exp_res == -972
		&& mant == 4503599627370496 && fenv->sign == 1)
		return (2);
	else if (fenv->mant_num - fenv->exp_res == -972 && mant == 6755399441055744)
		return (3);
	return (0);
}

void	put_unval(t_fenv **fenv, t_env *env, int error)
{
	char	*str;

	str = NULL;
	if (error == 1)
		str = ft_strdup("inf");
	else
		str = (error == 2 ? ft_strdup("-inf") : ft_strdup("nan"));
	env->offset -= 3;
	env->offset += (env->space && error != 2) ? 1 : 0;
	env->offset -= (error == 2 && !env->space) ? 1 : 0;
	env->offset -= (error == 1 && env->plus) ? 1 : 0;
	env->zero = 0;
	if (!env->minus)
		to_buff_offset(env);
	if (env->plus && error == 1)
		to_buff_char('+', env);
	to_buff_str(str, env);
	if (env->minus)
		to_buff_offset(env);
	free_fenv(*fenv);
	free(*fenv);
}

int		*calc_res(ULL mant, t_fenv *fenv, int long_ch)
{
	int		*res;
	int		*arr;
	int		*n;
	int		bit;

	n = NULL;
	arr = new_arr((ULL)mant, fenv->bit);
	bit = fenv->bit;
	if (fenv->mant_num - fenv->exp_res - long_ch >= 0)
		n = binpow(5, fenv->mant_num - fenv->exp_res - long_ch, fenv->bits);
	else
		n = binpow(2, fenv->exp_res - fenv->mant_num + long_ch, fenv->bits);
	fenv->bit = bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];
	res = new_arr((ULL)0, fenv->bits[2]);
	mult_by_column(arr, n, res, fenv->bits);
	fenv->bits[2] = cut_num(&res, fenv->bits[2]);
	fenv->res_bit = fenv->bits[2];
	free(arr);
	free(n);
	return (res);
}

void	prec_def(t_env *env)
{
	if (!env->is_precision)
	{
		env->is_precision = 1;
		env->precision = 6;
	}
}

void	flag_f(t_env *env, va_list args)
{
	t_fenv	*fenv;
	UL		*ptr;
	ULL		mant;
	double	cont;
	int		*res;

	cont = (double)va_arg(args, double);
	ptr = (UL *)&cont;
	fenv = init_fenv(64, *ptr);
	if (cont == 0)
		return (float_zero(&fenv, env));
	mant = *ptr & 4503599627370495;
	mant = mant | 4503599627370496;
	if (valid_float(fenv, mant))
		return (put_unval(&fenv, env, valid_float(fenv, mant)));
	res = calc_res(mant, fenv, 0);
	fenv->compos = fenv->res_bit - (fenv->mant_num - fenv->exp_res);
	prec_def(env);
	res = prec(res, env->precision, fenv);
	float_output(env, fenv, res);
	free_fenv(fenv);
	free(res);
	free(fenv);
}

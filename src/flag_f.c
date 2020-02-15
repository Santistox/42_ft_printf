#include "ft_printf.h"

long	ft_pow(double n, int pow)
{
	return (pow ? n * ft_pow(n, pow - 1) : 1);
}

void	flag_f(t_env *env, va_list args)
{
	double		num;
	long		tmp;
	int			leng;
	char		*res;
	int			i;
	int			dig;
	long		rest;
	int			minus;

	leng = 1;
	i = 0;
	dig = 0;
	minus = 0;
	env->precision = (env->is_precision) ? env->precision : 6;
	num = va_arg(args, double);
	if (num < 0.0f)
	{
		minus = 1;
		num *= -1;
	}
	tmp = (long)num;
	if (tmp == 0)
		leng++;
	while (tmp && ++leng)
		tmp /= 10;
	res = ft_memalloc(sizeof(char) * (leng + env->precision));
	while (i++ < (leng + env->precision - 1))
		res[i] = '0';
	res[i] = '\0';
	res[leng - 1] = '.';
	i = leng - 2;
	tmp = (long)num;
	while (i >= 0)
	{
		dig = tmp % 10;
		res[i--] = dig + '0';
		tmp /= 10;
	}
	rest = (num - (long)num) * ft_pow(10, env->precision + 1);
	rest = (rest % 10 > 4) ? (rest) / 10 + 1 : rest / 10;
	i = leng + env->precision - 1;
	
	while (i > leng - 1)
	{
		dig = rest % 10;
		res[i--] = dig + '0';
		rest /= 10;
	}
	if (env->zero > 0)
	{
		res = zero_offset(env, res, minus);
		plus_minus(env, &res, minus, 0);
	}
	else if (env->offset > 0)
	{
		plus_minus(env, &res, minus, 0);
		if (minus)
			res = ft_strjoin("-", res);
		res = space_offset(env, res, 0, 0);
	}
	if (minus && res[0] != '-' && res[env->offset - leng - env->precision - 1] != '-')
		res = ft_strjoin("-", res);
	if (env->space && minus == 1 && env->minus)
		res = ft_strjoin(res, " ");
	else if (env->space)
		res = ft_strjoin(" ", res);
	env->buf = ft_strjoin(env->buf, res);
}
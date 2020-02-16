#include "ft_printf.h"

double	ft_pow(double n, int pow)
{
	return (pow ? n * ft_pow(n, pow - 1) : 1);
}

int		ft_first(double n)
{
	int		i;
	long	num;

	//printf(" + %f\n", n);
	num = (long)n;
	i = 1;
	while (num > 0l)
	{
		//printf(" - %ld\n", num);
		i = num % 10;
		num /= 10;
	}
	return (i);
}

void	flag_f(t_env *env, va_list args)
{
	double		num;
	long		tmp;
	int			leng;
	char		*res;
	int			i;
	int			dig;
	double		rest;
	double		rest_before;
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
//	res[leng - 1] = '.';
	res[leng - 1] = (env->precision > 0) ? '.' : (env->offset - leng > 1 && env->minus) ? ' ' : '\0';
	i = leng - 2;
	tmp = (long)num;
	while (i >= 0)
	{
		dig = tmp % 10;
		res[i--] = dig + '0';
		tmp /= 10;
	}
	//printf("%f\n", (num - (long)num)* ft_pow(10, env->precision + 1));
	rest = (num - (long)num) * ft_pow(10, env->precision + 1);
	//printf("%f\n", rest);
	rest_before = rest;
	rest = ((int)rest % 10 > 4) ? (rest) / 10 + 1 : rest / 10;
	if (ft_first(rest_before) > ft_first(rest) && ft_first(rest_before) > 4)
	{
		res[leng - 2] += 1;
		if (!ft_isdigit(res[leng - 2]))
			res[leng - 2] = '0';
		// сделать функцию - иттеративно прохожу по числу и увеличиваю по условию ifdigit
	}
	//printf("%f\n", rest);
	//printf("%d %d\n", ft_first(rest_before), ft_first(rest));
	i = leng + env->precision - 1;
	while (i > leng - 1)
	{
		dig = (int)rest % 10;
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
	//if (env->space && !minus && env->minus)
	//	res = ft_strjoin(res, " ");
	if (env->space && !minus)
		res = ft_strjoin(" ", res);
	env->buf = ft_strjoin(env->buf, res);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:37:50 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 15:46:34 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	error_mes(void)
{
	ft_putstr("error: combination is not allowed\n");
	exit(EXIT_FAILURE);
}

int		leng(long long int n)
{
	int numlen;

	numlen = (n < 0) ? 2 : 1;
	while ((n /= 10) > 0)
		numlen++;
	return (numlen);
}

void	flag_di_help(t_env *env, int num, char **res, int zero_minus)
{
	env->res += leng(num);
	*res = ft_itoa(num);
	if (!(env->is_precision) && !(env->zero))
		plus_minus(env, res, zero_minus, num);
	if (env->is_precision)
	{
		if (env->precision == 0 && num == 0)
		{
			free(*res);
			*res = ft_strdup("");
		}
		else
			*res = precision(env, *res, zero_minus);
		plus_minus(env, res, zero_minus, num);
	}
	if (env->zero && !env->is_precision)
	{
		*res = zero_offset(env, *res, zero_minus);
		plus_minus(env, res, zero_minus, num);
	}
	else if (env->offset)
		*res = space_offset(env, *res, zero_minus, 0);
}

void	flag_di(t_env *env, va_list args)
{
	int		num;
	char	*res;
	int		zero_minus;
	int		minus;

	minus = 0;
	zero_minus = 0;
	num = va_arg(args, int);
	if (num < 0)
		minus = 1;
	if (env->is_precision && num < 0)
		env->res++;
	if ((env->zero || env->is_precision) && num < 0)
	{
		zero_minus = 1;
		num *= -1;
	}
	flag_di_help(env, num, &res, zero_minus);
	space(env, &res, minus);
	env->buf = ft_strjoin(env->buf, res);
}

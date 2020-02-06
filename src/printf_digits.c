/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:41:57 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/04 15:31:20 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	error_mes(void)
{
	ft_putstr("error: combination is not allowed\n");
	exit(EXIT_FAILURE);
}

static int	leng(long long int n)
{
	int numlen;

	numlen = (n < 0) ? 2 : 1;
	while ((n /= 10) > 0)
		numlen++;
	return (numlen);
}

void	flag_o(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

	if (env->space || env->plus)
		error_mes();
	num = va_arg(args, unsigned int);
	res = ft_itoa_o(num);
	env->res += ft_strlen(res);
	if (env->is_precision)
	{
		if (env->precision == 0 &&  num == 0)
		{
			free(res);
			res = ft_strdup("");
		}
		else
			res = precision(env, res, 0);
	}
	if (env->zero && !env->is_precision)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0, 0);
	env->buf = ft_strjoin(env->buf, res);
}

void print(t_env *env)
{
	ft_putstr(env->buf);
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
	env->res += leng(num);
	res = ft_itoa(num);
	if (!(env->is_precision) && !(env->zero))
		plus_minus(env, &res, zero_minus, num);
	if (env->is_precision)
	{
		if (env->precision == 0 &&  num == 0)
		{
			free(res);
			res = ft_strdup("");
		}
		else
			res = precision(env, res, zero_minus);
		plus_minus(env, &res, zero_minus, num);
	}
	if (env->zero && !env->is_precision)
	{
		res = zero_offset(env, res, zero_minus);
		plus_minus(env, &res, zero_minus, num);
	}
	else if (env->offset)
		res = space_offset(env, res, zero_minus, 0);
//	if (env->is_precision || env->zero)
//		plus_minus(env, &res, zero_minus, num);
	space(env, &res, minus);
	env->buf = ft_strjoin(env->buf, res);
}

void	flag_u(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

/*
 *
 *	Why there are error with zero&minus? Question to Sanya
 *									- rlintill
 *
 * */

	if (env->space || env->plus || (env->minus && env->zero))
		error_mes();
	num = va_arg(args, unsigned int);
	res = ft_itoa(num);
//	env->res += ft_strlen(res);
	if (env->is_precision)
	{
		if (env->precision == 0 &&  num == 0)
		{
			free(res);
			res = ft_strdup("");
		}
		else
			res = precision(env, res, 0);
	}
	if (env->zero && !env->is_precision)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0, 0);
//	env->res += leng(num);
	env->buf = ft_strjoin(env->buf, res);
}

void	flag_x(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

/*
 *
 *	Why there are error with zero&minus? Question to Sanya
 *									- rlintill
 *
 * */

	if (env->space || env->plus || (env->minus && env->zero))
		error_mes();
	num = va_arg(args, unsigned int);
	res = ft_itoa_x(num);
//	env->res += ft_strlen(res);
	if (env->is_precision)
	{
		if (env->precision == 0 &&  num == 0)
		{
			free(res);
			res = ft_strdup("");
		}
		else
			res = precision(env, res, 0);
	}
	if (env->zero)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0, 0);
	env->buf = ft_strjoin(env->buf, res);

}

void	flag_x_up(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

/*
 *
 *	Why there are error with zero&minus? Question to Sanya
 *									- rlintill
 *
 * */

	if (env->space || env->plus || (env->minus && env->zero))
		error_mes();
	num = va_arg(args, unsigned int);
	res = ft_itoa_x_up(num);
//	env->res += ft_strlen(res);
	if (env->is_precision)
	{
		if (env->precision == 0 &&  num == 0)
		{
			free(res);
			res = ft_strdup("");
		}
		else
			res = precision(env, res, 0);
	}
	if (env->zero)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0, 0);
	env->buf = ft_strjoin(env->buf, res);

}

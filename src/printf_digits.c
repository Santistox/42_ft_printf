/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:41:57 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/04 11:53:02 by rlintill         ###   ########.fr       */
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

/*
 *
 *	Fucking govno code
 *	Even I don't really understant what is happening here
 *										- rlintill
 *
 *	To do with I:
 *	- check errors
 *	- hh, h, l, ll flags
 *	- norme
 *
 * */
/*
void flag_i(t_env *env, va_list args)
{
	int		num;
	int		len;
	char	*offset;
	char	*res;
	int		zero_minus;

	zero_minus = 0;
	num = va_arg(args, int);
	len = leng(num);
	if (env->is_precision && num < 0)
	{
		env->res++;
		len--;
	}
	offset = NULL;
	if ((env->zero || env->is_precision) && num < 0)
	{
		zero_minus = 1;
		num *= -1;
	}
	res = ft_itoa(num);
	if ((env->zero || env->is_precision) && !(len < env->offset || len < env->precision) && zero_minus)
		res = ft_strjoin("-", res);
	if (env->space && num >= 0 && !zero_minus)
	{
		env->buf = ft_strjoin(env->buf, " ");
		env->res++;
	}
	if (env->plus && num >= 0 && !(env->is_precision))
	{
		len++;
		if (!zero_minus && (!(env->zero || env->is_precision) || (env->zero && len >= env->offset) || (env->is_precision && len >= env->precision)))
			res = ft_strjoin("+", res);
	}
	else if (env->plus && num >= 0)
		env->res++;
	if (env->offset && len < env->offset)
	{
		offset = ft_memalloc((size_t)(env->offset - len));
		if (env->zero)
		{
			offset = ft_memset(offset, '0', env->offset - len);
			if (zero_minus)
				offset = ft_strjoin("-", offset);
			else if (env->plus)
				offset = ft_strjoin("+", offset);
		}
		else
			offset = ft_memset(offset, ' ', env->offset - len);
		if (!env->minus)
			env->buf = ft_strjoin(env->buf, offset);
		len += (env->offset - len);
	}
	if (env->is_precision && len < env->precision)
	{
		offset = ft_memalloc((size_t)(env->precision - len));
		offset = ft_memset(offset, '0', env->precision - len);
		if (zero_minus)
			offset = ft_strjoin("-", offset);
		else if (env->plus)
			offset = ft_strjoin("+", offset);
		res = ft_strjoin(offset, res);
		ft_memdel((void*)&offset);
		len += (env->precision - len);
	}
	env->buf = ft_strjoin(env->buf, res);
	if (offset != NULL && env->minus)
		env->buf = ft_strjoin(env->buf, offset);
	ft_memdel((void*)&res);
	if (offset != NULL)
		ft_memdel((void*)&offset);
	env->res += len;
}
*/




/*
 *
 *	Eto govno vse eshe ne rabotaet s otricatelnimi chislami poshlo wse na hhhhhh
 *																-rlintill
 *
 * */




void	flag_o(t_env *env, va_list args)
{
	/*
	int		num;
	char	*res;
	int		minus;

	if (env->space || env->plus)
		error_mes();
	num = va_arg(args, int);
	minus = (num < 0) ? 1 : 0;
	res = ft_itoa_o(num);
	if (num < 0)
		num *= -1;
	if (env->is_precision)
		res = precision(env, res, minus);	
	else if (env->zero)
		res = zero_offset(env, res, minus, 0);
	else if (env->offset)
		res = space_offset(env, res, minus);
	env->buf = ft_strjoin(env->buf, res);
	env->res += ft_strlen(res);
	*/
	unsigned int	num;
	char			*res;

	if (env->space || env->plus)
		error_mes();
	num = va_arg(args, unsigned int);
	res = ft_itoa_o(num);
	env->res += ft_strlen(res);
	if (env->is_precision)
		res = precision(env, res, 0);	
	if (env->zero && !env->is_precision)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0);
	env->buf = ft_strjoin(env->buf, res);
}

void print(t_env *env)
{
	ft_putstr(env->buf);
	//write(0, env->buf, env->res);
}

void	flag_di(t_env *env, va_list args)
{
	int		num;
	char	*res;
	int		zero_minus;

	zero_minus = 0;
	num = va_arg(args, int);
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
		res = precision(env, res, zero_minus);
	if (env->zero && !env->is_precision)
		res = zero_offset(env, res, zero_minus);
	else if (env->offset)
		res = space_offset(env, res, zero_minus);
	if (env->is_precision || env->zero)
		plus_minus(env, &res, zero_minus, num);
	space(env, &res, num);
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
	env->res += ft_strlen(res);
	if (env->is_precision)
		res = precision(env, res, 0);	
	if (env->zero && !env->is_precision)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0);
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
	env->res += ft_strlen(res);
	if (env->is_precision)
		res = precision(env, res, 0);	
	if (env->zero)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0);
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
	env->res += ft_strlen(res);
	if (env->is_precision)
		res = precision(env, res, 0);	
	if (env->zero)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0);
	env->buf = ft_strjoin(env->buf, res);

}

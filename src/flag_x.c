/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 12:38:17 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 13:55:50 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_x(unsigned int n)
{
	return (base_ft_itoa(n, 'a', 16));
}

char	*ft_itoa_x_up(unsigned int n)
{
	return (base_ft_itoa(n, 'A', 16));
}

void	flag_x_help(t_env *env, unsigned int num, char **res)
{
	if (env->is_precision)
	{
		if (env->precision == 0 && num == 0)
		{
			free(*res);
			*res = ft_strdup("");
		}
		else
			*res = precision(env, *res, 0);
	}
	if (env->zero && env->grille && num != 0)
		env->offset = (env->offset > 0) ? env->offset - 2 : env->offset;
}

void	flag_x(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

	if (env->space || env->plus || (env->minus && env->zero))
		error_mes();
	num = va_arg(args, unsigned int);
	res = ft_itoa_x(num);
	flag_x_help(env, num, &res);
	if (env->zero)
	{
		res = zero_offset(env, res, 0);
		if (env->grille && num != 0)
			res = ft_strjoin("0x", res);
	}
	else if (env->offset)
	{
		if (env->grille && num != 0)
			res = ft_strjoin("0x", res);
		res = space_offset(env, res, 0, 0);
	}
	if (!env->zero && !env->offset && env->grille && num != 0)
		res = ft_strjoin("0x", res);
	env->buf = ft_strjoin(env->buf, res);
}

void	flag_x_up(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

	if (env->space || env->plus || (env->minus && env->zero))
		error_mes();
	num = va_arg(args, unsigned int);
	res = ft_itoa_x_up(num);
	flag_x_help(env, num, &res);
	if (env->zero)
	{
		res = zero_offset(env, res, 0);
		if (env->grille && num != 0)
			res = ft_strjoin("0X", res);
	}
	else if (env->offset)
	{
		if (env->grille && num != 0)
			res = ft_strjoin("0X", res);
		res = space_offset(env, res, 0, 0);
	}
	if (!env->zero && !env->offset && env->grille && num != 0)
		res = ft_strjoin("0X", res);
	env->buf = ft_strjoin(env->buf, res);
}

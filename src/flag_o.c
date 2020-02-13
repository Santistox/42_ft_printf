/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:54:07 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 14:05:00 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_o(unsigned int n)
{
	return (base_ft_itoa(n, 'a', 8));
}

void	flag_o_second(t_env *env, char **res, unsigned int num)
{
	if (env->zero && env->grille && num != 0)
		env->offset = (env->offset > 0) ? env->offset - 1 : env->offset;
	if (env->zero && !env->is_precision)
	{
		*res = zero_offset(env, *res, 0);
		if (env->grille && num != 0)
			*res = ft_strjoin("0", *res);
	}
	else if (env->offset)
	{
		if (env->grille && num != 0 && *res[0] != '0')
			*res = ft_strjoin("0", *res);
		*res = space_offset(env, *res, 0, 0);
	}
	if (!env->zero && !env->offset && env->grille && num != 0 && *res[0] != '0')
		*res = ft_strjoin("0", *res);
	env->buf = ft_strjoin(env->buf, *res);
}

void	flag_o(t_env *env, va_list args)
{
	unsigned int	num;
	char			*res;

	if (env->space || env->plus)
		error_mes();
	if (env->zero && env->precision > 0)
		env->zero = 0;
	num = va_arg(args, unsigned int);
	res = ft_itoa_o(num);
	env->res += ft_strlen(res);
	if (env->is_precision)
	{
		if (env->precision == 0 && num == 0)
		{
			free(res);
			if (env->grille)
			{
				res = ft_strdup("0");
				if (env->offset)
					res = space_offset(env, res, 0, 0);
				env->buf = ft_strjoin(env->buf, res);
				return ;
			}
			res = ft_strdup("");
		}
		else
			res = precision(env, res, 0);
	}
	flag_o_second(env, &res, num);
}

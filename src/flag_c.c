/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:54:07 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 14:05:00 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_c(t_env *env, va_list args)
{
	wchar_t	c;
	char	*res;

	c = va_arg(args, unsigned int);
	res = ft_memalloc(sizeof(char) + 1);
	res[0] = c;
	res[1] = '\0';
	if (env->offset)
		res = space_offset(env, res, 0, 1);
	env->buf = ft_strjoin(env->buf, res);
}

void	flag_per(t_env *env)
{
	char *res;

	res = ft_memalloc(sizeof(char) + 1);
	res[0] = '%';
	res[1] = '\0';
	if (env->zero)
		res = zero_offset(env, res, 0);
	else if (env->offset)
		res = space_offset(env, res, 0, 1);
	env->buf = ft_strjoin(env->buf, res);
}

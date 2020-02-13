/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/13 15:12:45 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_buff_offset(t_env *env)
{
	char	*offset;

	if (env->offset > 0)
	{
		if (!(offset = ft_memalloc(sizeof(char) * env->offset + 1)))
			error(403);
		if (env->zero == 1)
			ft_memset(offset, '0', env->offset);
		else
			ft_memset(offset, ' ', env->offset);
		to_buff_str(offset, env);
	}
}

void	flag_s(t_env *env, va_list args)
{
	char	*next_arg;
	int		arg_size;
	char	*precise_str;

	next_arg = va_arg(args, char *);
	arg_size = ft_strlen(next_arg);
	if (env->precision < arg_size && env->is_precision == 1)
	{
		env->offset -= env->precision;
		if (!(precise_str = ft_memalloc(sizeof(char) * env->precision + 1)))
			error(403);
		ft_memcpy(precise_str, next_arg, env->precision);
	}
	else
	{
		env->offset -= arg_size;
		precise_str = ft_strdup(next_arg);
	}
	if (!env->minus)
		to_buff_offset(env);
	to_buff_str(precise_str, env);
	if (env->minus)
		to_buff_offset(env);
}

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

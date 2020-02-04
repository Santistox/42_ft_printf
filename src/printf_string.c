/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/04 15:28:15 by rlintill         ###   ########.fr       */
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
/*
void	flag_c(t_env *env, int offset)
{
	if (offset == 1)
		env->offset--;
	if (!env->minus && offset == 1)
		to_buff_offset(env);
	if (!env->cont)
	{
		env->count_2 += ft_strlen(env->buf) + 1;
		to_buff_char('\0', env);
		write(0, env->buf, ft_strlen(env->buf) + 1);
		ft_memdel((void*)&env->buf);
		env->buf = ft_memalloc(sizeof(char));
	}
	to_buff_char(env->cont, env);
	if (env->minus && offset == 1)
		to_buff_offset(env);
}*/

void flag_c(t_env *env, va_list args)
{
	char c;
	char *res;

	c = va_arg(args, unsigned int);
	res = ft_memalloc(sizeof(char) + 1);
	res[0] = c;
	res[1] = '\0';
	if (env->offset)
		res = space_offset(env, res, 0);
	env->buf = ft_strjoin(env->buf, res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/01/31 16:47:31 by mnidoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_buff_offset(t_env *env)
{
	char	*offset;


	if (env->offset > 0)
	{
		if (!(offset = ft_memalloc(sizeof(char) * env->offset + 1)))
		{
			ft_putstr("error: Malloc failed\n");
			exit(EXIT_FAILURE);
		}
		if (env->zero == 1)
			ft_memset(offset, '0', env->offset);
		else
			ft_memset(offset, ' ', env->offset);
		to_buff_str(offset, env);
	}
}

void	flag_s(t_env *env, va_list arg)
{
	char	*next_arg;
	int		arg_size;
	char	*precise_str;

	next_arg = va_arg(arg, char *);
	arg_size = ft_strlen(next_arg);
	if (env->precision < arg_size && env->is_precision == 1)
	{
		env->offset -= env->precision;
		if (!(precise_str = ft_memalloc(sizeof(char) * env->precision + 1)))
		{
			ft_putstr("error: Malloc failed\n");
			exit(EXIT_FAILURE);
		}
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

void	flag_c(t_env *env, va_list arg)
{
	//something went wrong
}
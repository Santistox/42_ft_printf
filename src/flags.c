/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:46:09 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 14:45:42 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**  find flag e.g. %s %c
*/

void	find_flag_continue(t_env *env, va_list args)
{
	if (env->str[env->count] == 'i' || env->str[env->count] == 'd')
		flag_di(env, args);
	else if (env->str[env->count] == 'o')
		flag_o(env, args);
	else if (env->str[env->count] == 'u')
		flag_u(env, args);
	else if (env->str[env->count] == 'x')
		flag_x(env, args);
	else if (env->str[env->count] == 'X')
		flag_x_up(env, args);
	else if (env->str[env->count] == 's')
		flag_s(env, args);
	else if (env->str[env->count] == 'c')
		flag_c(env, args);
	else if (env->str[env->count] == '%')
		flag_per(env);
	else if (env->str[env->count] == 'f')
		flag_f(env, args);
}

void	find_flag(t_env *env, va_list args)
{
	set_def(env);
	check_preflag(env);
	if (!check_flag(env->str[env->count]))
	{
		env->count--;
		return ;
	}
	if (env->plus == 1 && env->space == 1)
		env->space = 0;
	else
		env->space = env->space;
	if (env->zero == 1 && env->minus)
		env->zero = 0;
	else
		env->zero = env->zero;
	if (env->dot == 0 || env->zero != 0)
		set_offset(env->count, env);
	set_precision(env->count, env);
	if (env->space == 1 && env->offset != 0)
		env->offset -= 1;
	else
		env->offset -= env->space;
	//length_flags(env, args);
	find_flag_continue(env, args);
}

/*
**  flag validation
*/

int		check_flag(char c)
{
	if (ft_isdigit(c) || c == 's' || c == 'S' ||
		c == 'p' || c == 'd' || c == 'D' ||
		c == 'o' || c == 'O' || c == 'u' ||
		c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == '.' ||
		c == '%' || c == 'h' || c == 'l' ||
		c == 'i' || c == 'j' || c == 'z' || c == 'f')
		return (1);
	return (0);
}

/*
**  find and validate modifications of flag
*/

void	check_preflag(t_env *env)
{
	char c;

	c = env->str[env->count];
	while (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+' || c == '.')
	{
		if (env->str[env->count] == '#')
			env->grille = 1;
		else if (env->str[env->count] == '0' && env->str[env->count + 1] != '.')
			env->zero = 1;
		else if (env->str[env->count] == '-')
			env->minus = 1;
		else if (env->str[env->count] == ' ')
			env->space = 1;
		else if (env->str[env->count] == '+')
			env->plus = 1;
		else if (env->str[env->count] == '.')
		{
			env->zero = 0;
			env->dot = 1;
			env->is_precision = 1;
			env->count++;
			break ;
		}
		c = env->str[++(env->count)];
	}
}

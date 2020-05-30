/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 11:46:09 by mnidoque          #+#    #+#             */
/*   Updated: 2020/05/14 14:11:57 by mnidoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_valid_flag(char c)
{
	if (c == 's' || c == 'p' || c == 'd' ||
		c == 'D' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'x' ||
		c == 'X' || c == 'c' || c == '%' ||
		c == 'i' || c == 'f')
		return (1);
	return (0);
}

static int	check_valid_flags(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == '+' || c == ' ')
		return (1);
	return (0);
}

static int	valid_size_dbl(int i, char c, char *str)
{
	if (str[i] == c)
	{
		i++;
		if (str[i] == c)
			i++;
		if (!(check_valid_flag(str[i])))
			return (1);
	}
	return (0);
}

void		flag_valid(t_env *env)
{
	int i;
	int error;

	i = env->count;
	i += check_valid_flags(env->str[i]) ? 1 : 0;
	i += check_valid_flags(env->str[i]) ? 1 : 0;
	i += check_valid_flags(env->str[i]) ? 1 : 0;
	i += check_valid_flags(env->str[i]) ? 1 : 0;
	while (ft_isdigit(env->str[i]))
		i++;
	i += (env->str[i] == '.') ? 1 : 0;
	while (ft_isdigit(env->str[i]))
		i++;
	if (env->str[i] == 'h')
		error = valid_size_dbl(i, 'h', env->str) ? 1 : 0;
	else if (env->str[i] == 'l')
		error = valid_size_dbl(i, 'l', env->str) ? 1 : 0;
	else if (env->str[i] == 'j' || env->str[i] == 'z' || env->str[i] == 'L')
		error = !(check_valid_flag(env->str[++i])) ? 1 : 0;
	else
		error = !(check_valid_flag(env->str[i])) ? 1 : 0;
	if (error)
		env->count = i;
}

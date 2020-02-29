/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/13 14:51:54 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	error(int error_id)
{
	if (error_id == 403)
	{
		ft_putstr("error: Malloc failed\n");
		exit(EXIT_FAILURE);
	}
	if (error_id == 404)
	{
		ft_putstr("error: Combination is not allowed\n");
		exit(EXIT_FAILURE);
	}
}

/*
**  reset variables of structure
*/

void	set_def(t_env *env)
{
	env->offset = 0;
	env->precision = 0;
	env->is_precision = 0;
	env->dot = 0;
	env->grille = 0;
	env->plus = 0;
	env->minus = 0;
	env->space = 0;
	env->is_unicode = 0;
}

/*
**  create struct
*/

t_env	*malloc_env(char *str)
{
	t_env	*env;

	if (!(env = ft_memalloc(sizeof(t_env))))
		error(403);
	env->buf = (char *)malloc(sizeof(char *));
	env->str = str;
	env->count = 0;
	env->count_2 = 0;
	env->res = 0;
	return (env);
}

/*
**  printf to file
*/

int		ft_printf_fd(int fd, const char *line, ...)
{
	int		rez;
	va_list	args;
	t_env	*env;

	rez = 0;
	env = malloc_env((char*)line);
	env->fd = fd;
	va_start(args, line);
	while (env->str[env->count])
	{
		to_buff_block(env);
		if (!env->str[env->count])
			break ;
		env->count++;
		find_flag(env, args);
		if (env->unicode_error == 1)
			break ;
		env->count++;
	}
	rez = ft_strlen(env->buf) + env->count_2;
	write(env->fd, env->buf, ft_strlen(env->buf));
	free(env->buf);
	free(env);
	va_end(args);
	return (rez);
}

/*
**  main function of ft_printf 
*/

int		ft_printf(const char *line, ...)
{
	int		rez;
	va_list	args;
	t_env	*env;

	rez = 0;
	env = malloc_env((char*)line);
	env->fd = 1;
	va_start(args, line);
	while (env->str[env->count])
	{
		to_buff_block(env);
		if (!env->str[env->count])
			break ;
		env->count++;
		find_flag(env, args);
		if (env->unicode_error == 1)
			break ;
		env->count++;
	}
	rez = ft_strlen(env->buf) + env->count_2;
	write(env->fd, env->buf, ft_strlen(env->buf));
	free(env->buf);
	free(env);
	va_end(args);
	return (rez);
}

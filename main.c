/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/01/27 18:20:48 by mnidoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	to_buff_str(char *str, t_env *env)
{
	char *to_free;

	to_free = env->buf;
	env->buf = ft_strjoin(env->buf, str);
	ft_memdel((void*)&to_free);
	ft_memdel((void*)&str);
}

void	to_buff_char(char c, t_env *env)
{
	char	*str_c;

	if (!(str_c = ft_memalloc(sizeof(char) * 2)))
		malloc_error();
	str_c[0] = c;
	str_c[1] = '\0';
	to_buff_str(str_c, env);
}

void	to_buff_block(t_env *env)
{
	env->first_char_pos = env->i;
	while (env->str[env->i] && env->str[env->i] != '%')
	{
		put_char_to_buf(env->str[env->i], env);
		env->i++;
	}
	if (env->str[env->i] == '%')
		env->percent_pos = env->i;
}

t_env	*malloc_env(char *str)
{
	t_env	*env;

	if (!(env = ft_memalloc(sizeof(t_env))))
	{
		ft_putstr("error: Malloc failed\n");
		exit();
	}
	env->buf = ft_memalloc(sizeof(char *));
	env->str = str;
	env->count = 0;
	return (e);
}

int ft_printf(const char *line, ...)
{
	int		rez;
	va_list	args;
	t_env	*env;

	rez = 0;
	env = malloc_env((char*)line);
	va_start(args, line);
	while (env->str[env->count])
	{
		to_buff_block(env);
		if (!env->str[env->i])
			break ;
		env->i++;
		parse_after_percent(e, arg);
		if (e->unicode_error == 1)
			break ;
		env1->i++;
	}
	return(rez);
}

int main(void)
{
	int i;

	i = 1;
	printf("%i\n", i);
	ft_printf("%i\n", i);
	return(0);
}

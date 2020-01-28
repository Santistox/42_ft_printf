/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/01/28 18:05:09 by mnidoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 *  test correctly functionality
 */
void	checker(t_env *env, va_list args)
{
	printf("buf               |%s|\n", env->buf);
	printf("str               |%s|\n", env->str);
	printf("count             |%i|\n", env->count);
	printf("offset            |%i|\n", env->offset);
	printf("precision         |%i|\n", env->precision);
	printf("is_precision      |%i|\n", env->is_precision);
	printf("dot               |%i|\n", env->dot);
	printf("grille            |%i|\n", env->grille);
	printf("plus              |%i|\n", env->plus);
	printf("minus             |%i|\n", env->minus);
	printf("space             |%i|\n", env->space);
	printf("zero              |%i|\n", env->zero);
	printf("is_unicode        |%i|\n", env->is_unicode);
	printf("unicode_error     |%i|\n", env->unicode_error);
	printf("first_char_pos    |%i|\n", env->first_char_pos);
	printf("percent_pos       |%i|\n", env->percent_pos);
	printf("_____________________________________\n");
}

/*
 *  find and validate modifications of flag
 */
void	check_preflag(t_env *env)
{
	char c;
	c = env->str[env->count];
	while (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+' || c == '.')
	{
		if (env->str[env->count] == '#')
			env->grille= 1;
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
		env->count++;
		c = env->str[env->count];
	}
}

/*
 *  reset variables of structure
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
 *  flag validation
 */
int		check_flag(char c)
{
	if (ft_isdigit(c) || c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
		c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == '.' || c == '%' || c == 'h' || c == 'l' ||
		c == 'i' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

/*
 *  count precision
 */
void	set_precision(int init_index, t_env *env)
{
	char	*num;
	int		max;

	if (env->str[env->count] == '+' && env->str[env->count++])
		env->plus = 1;
	if (env->str[env->count] == '.' && env->str[env->count++])
		env->is_precision = 1;
	while (ft_isdigit(env->str[env->count]))
		env->count++;
	if (env->count - init_index == 0)
		return ;
	init_index += env->str[init_index] == '.' ? 1 : 0;
	if (!(num = ft_memalloc(sizeof(char) * env->count - init_index + 1)))
	{
		ft_putstr("error: Malloc failed\n");
		exit(EXIT_FAILURE);
	}
	max = env->count;
	env->count = env->count - (env->count - init_index);
	ft_memcpy(num, &env->str[env->count], max - env->count);
	env->count = max;
	env->precision = ft_atoi(num);
	if (env->precision == 0 || env->dot == 1)
		env->is_precision = 1;
	ft_memdel((void*)&num);
}

/*
 *  count offset
 */
void	set_offset(int init_index, t_env *env)
{
	char	*num;
	int		i;
	int		max;

	i = 0;
	if (env->str[env->count] == '0' && !env->minus)
	{
		env->count++;
		return ;
	}
	while (ft_isdigit(env->str[env->count]))
		env->count++;
	if (!(num = ft_memalloc(sizeof(char) * env->count - init_index + 1)))
	{
		ft_putstr("error: Malloc failed\n");
		exit(EXIT_FAILURE);
	}
	max = env->count;
	env->count = env->count - (env->count - init_index);
	while (env->count < max)
		num[i++] = env->str[env->count++];
	num[i] = '\0';
	env->offset = ft_atoi(num);
	ft_memdel((void*)&num);
}

/*
 *  find flag e.g. %s %c
 */
void	find_flag(t_env  *env, va_list args)
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

	if(env->space == 1 && env->offset != 0)
		env->offset -= 1;
	else
		env->offset -= env->space;
	checker(env, args);
	// here code of calling flags functions
}

/*
 *  move string line to buffer
 */
void	to_buff_str(char *str, t_env *env)
{
	char *temp;

	temp = env->buf;
	env->buf = ft_strjoin(env->buf, str);
	ft_memdel((void*)&temp);
	ft_memdel((void*)&str);
}

/*
 *  move 1 char from line to buffer
 */
void	to_buff_char(char c, t_env *env)
{
	char	*ch;
	char    *temp;

	if (!(ch = ft_memalloc(sizeof(char) * 2)))
		exit(EXIT_FAILURE);
	ft_strncat(ch, &c, 1);
	ft_strncat(ch, "\0", 2);
	temp = env->buf;
	env->buf = ft_strjoin(env->buf, ch);
	ft_memdel((void*)&temp);
	ft_memdel((void*)&ch);
}

/*
 *  move line before % to buffer
 */
void	to_buff_block(t_env *env)
{
	env->first_char_pos = env->count;
	while (env->str[env->count] && env->str[env->count] != '%')
	{
		to_buff_char(env->str[env->count], env);
		env->count++;
	}
	if (env->str[env->count] == '%')
		env->percent_pos = env->count;
}

/*
 *  create struct
 */
t_env	*malloc_env(char *str)
{
	t_env	*env;

	if (!(env = ft_memalloc(sizeof(t_env))))
	{
		ft_putstr("error: Malloc failed\n");
		exit(EXIT_FAILURE);
	}
	env->buf = ft_memalloc(sizeof(char *));
	env->str = str;
	env->count = 0;
	return (env);
}

/*
 *  main function of ft_printf
 */
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
		if (!env->str[env->count])
			break ;
		env->count++;
		find_flag(env, args);
		if (env->unicode_error == 1)
			break ;
		env->count++;
	}
	return(rez);
}

int main(void)
{
	float e;

	e=2.718281828;

	// test here
	printf("20%i%20i%i%i%i%i\n", 1,2,3,4,5,6);
	ft_printf("20%02i%20i%i%i%i%i", 1,2,3,4,5,6);
	return(0);
}

//compile with:
// gcc main.c ft_printf.h libft/libft.h libft/*.c

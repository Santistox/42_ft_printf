/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:36:33 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 14:43:56 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** library to work with standatd printf
** library to work with indefinite number of arguments
** personal library
** library for using wchar_t type
*/

# include <stdio.h>
# include <stdarg.h>
# include "../libft/libft.h"
# include <wchar.h>
# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 1024

/*
** buf - buffer
** str - input line
** count - line coursor str
** count_buf - line coursor buf
** offset - number of offsets
** precision - number of precision
** if_precisison - if there is a precision
** dot - . after %
** grille - # after %
** plus - + after %
** space - ␣ after %
** zero - 0 after %
** is_unicode - check is char unicode
** unicode_error - unicode error
** first_char_pos - first char position from start/prev%
** percent_pos - position of %
** res - count of buf ???
** cont - container helps program to contain big numbers
** count_2 - backup count variable value
** fd - file descriptor
*/

typedef struct	s_env
{
	char		*buf;
	char		*str;
	int			count;
	int			count_buf;
	int			offset;
	int			precision;
	int			is_precision;
	int			dot;
	int			grille;
	int			plus;
	int			minus;
	int			space;
	int			zero;
	int			is_unicode;
	int			unicode_error;
	int			first_char_pos;
	int			percent_pos;
	int			res;
	uintmax_t	cont;
	int			count_2;
	int			fd;
}				t_env;

int				ft_printf(const char *line, ...);
t_env			*malloc_env(char *str);
void			error(int error_id);

/*
** buffer functions
*/

void			to_buff_block(t_env *env);
void			to_buff_char(char c, t_env *env);
void			to_buff_str(char *str, t_env *env);
void			to_buff_offset(t_env *env);

/*
** flags.c
*/

void			find_flag(t_env *env, va_list args);
void			find_flag_continue(t_env *env, va_list args);
void			check_preflag(t_env *env);
int				check_flag(char c);

/*
** output.c
*/

void			sputstr(t_env *env, char *str, int n);
void			sputchar(t_env *env, char c);
void			sprint_buff(t_env *env);

void			set_def(t_env *env);

void			set_precision(int init_index, t_env *env);
void			set_offset(int init_index, t_env *env);

/*
** num flags
*/

void			flag_di(t_env *env, va_list args);
void			flag_di_help(t_env *env, int num, char **res, int zero_minus);
void			flag_o(t_env *env, va_list args);
void			flag_o_second(t_env *env, char **res, unsigned int num);
void			flag_u(t_env *env, va_list args);
void			flag_x(t_env *env, va_list args);
void			flag_x_up(t_env *env, va_list args);
char			*base_ft_itoa(unsigned int n, char c, int base);
char			*ft_itoa_o(unsigned int n);
char			*ft_itoa_x(unsigned int n);
char			*ft_itoa_x_up(unsigned int n);

/*
** num flags
*/

void			flag_s(t_env *env, va_list args);
void			flag_c(t_env *env, va_list args);
void			flag_per(t_env *env);

void			error_mes();
char			*space_offset(t_env *env, char *res, int minus, int flag_char);
char			*zero_offset(t_env *env, char *res, int minus);
char			*precision(t_env *env, char *res, int minus);
void			plus_minus(t_env *env, char **res, int minus, int num);
void			space(t_env *env, char **res, int zero);

/*
** Libft files
*/

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(long long int n);
void			ft_putstr(char const *s);
char			*ft_strnew(size_t size);

#endif

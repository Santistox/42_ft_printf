/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:36:33 by rlintill          #+#    #+#             */
/*   Updated: 2020/03/06 14:16:55 by rlintill         ###   ########.fr       */
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
# include <wchar.h>
# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 1024

/*
**
** main struct of printf
**
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
	int			caps;
	int			base;
	int			nb_digit;
}				t_env;

/*
**
** help struct for flag %f
**
** exp - exponent
** bit - bit size of array
** sign - sign of number
** compos - comma position in result
*/

typedef struct	s_fenv
{	
	char				bit;
	char 				sign;
	int 				res_bit; // !!!!!
	int					compos;
	int 				exp_num;
	int 				mant_num;
	long unsigned int 	exp;
	int					*bits;
}				t_fenv;


/*
** ft_printf.c
*/

void			error(int error_id);
void			set_def(t_env *env);
t_env			*malloc_env(char *str);
int				ft_printf_fd(int fd, const char *line, ...);
int				ft_printf(const char *line, ...);

/*
** buffun.c
*/

void			to_buff_offset(t_env *env);
void			to_buff_str(char *str, t_env *env);
void			to_buff_char(char c, t_env *env);
void			to_buff_block(t_env *env);

/*
** flags.c
*/
void			set_nb_digit(t_env *env);
void			find_flag_continue(t_env *env, va_list args);
void			find_flag(t_env *env, va_list args);
int				check_flag(char c);
void			check_preflag(t_env *env);

/*
** offpre.c
*/

void			set_precision(int init_index, t_env *env);
void			set_offset(int init_index, t_env *env);

/*
** flag_size.c
*/

void			length_flags(t_env *env, va_list args);

/*
** util.c
*/

char			*space_offset(t_env *env, char *res, int minus, int flag_char);
char			*zero_offset(t_env *env, char *res, int minus);
char			*precision(t_env *env, char *res, int minus);
void			plus_minus(t_env *env, char **res, int minus, int num);
void			space(t_env *env, char **res, int zero);

/*
** stringfun.c
*/

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putstr(char const *s);
char			*ft_strnew(size_t size);

/*
** memfun.c
*/

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
int				ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** flag_color.c
*/

int				paint(t_env *env, char *color, char *color_id);
void			flag_color(t_env *env);

/*
** num flagsi
*/

void			flag_f(t_env *env, va_list args);

void			put_precision(t_env *env, int arg_size);
void			put_zero(t_env *env);
void			flag_di(t_env *env);
void			flag_di_util(t_env *env);
char			*flag_di_help(t_env *env);

void			flag_x(t_env *env);
void			flag_x_util(t_env *env);
char			*flag_x_help(t_env *env);

void			flag_o(t_env *env);
char			*flag_o_help(t_env *env);

/*
** num flags
*/

void			flag_s(t_env *env, va_list args);
void			flag_c(t_env *env);
void			flag_per(t_env *env);

/*
** Libft files
*/

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
char			*ft_itoa(long long int n);

/*
** Calculator
*/
void 			add_by_column(int *num1, int *num2, int *rez, int *bit);
void            mult_by_column(int *num1, int *num2, int *rez, int *bit);
void			print_num(int *num, int i, char a); // WARNIG!! THIS FUNCTION JUST FOR TEST
int             cut_num(int **num, int bit);

/*
** flag_f.c
*/

int 			*new_arr(long long unsigned int num, int bit);
int 			*binpow(int num, int pow, int bit);
void			to_buff_float(t_env *env, t_fenv *fenv, int *num);
void 			copy_int(int *num1, int *num2, int bit);
/*
** flag_lf.c
*/

void			flag_lf(t_env *env, va_list args);
void			float_flags(t_env *env, va_list args);

#endif

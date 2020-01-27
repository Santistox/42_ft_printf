#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>

typedef struct	s_env
{
	char		*buf;
	char		*str;
	int			count;
	int			count_before_reset;
	uintmax_t	nbr;
	int			offset;
	int			precision;
	int			is_precision_specified;
	int			nb_digit;
	int			is_unicode;
	int			unicode_error;
	int			first_char_pos;
	int			percent_pos;
	int			size;
}				t_env;

#endif
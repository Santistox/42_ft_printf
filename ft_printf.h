#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h> // library to work with standard prinft
# include <stdarg.h> // library to work with indefinite number of arguments
# include "libft/libft.h" // personal library

typedef struct	s_env
{
	char		*buf;            // buffer
	char		*str;			 // input line
	int			count;           // line cursor
	int			offset;			 // number of offsets
	int			precision;       // number of precision
	int			is_precision;    // if there is precision
	int			dot;             // dot: . after %
	int			grille;			 // grille: # after %
	int			plus;            // plus: + after %
	int			minus;           // minus: - after %
	int			space;           // space: ␣ after %
	int			zero;            // zero: 0 after %
	int			is_unicode;      // check is char unicode
	int			unicode_error;   // unicode error
	int			first_char_pos;  // first char position from start/prev%
	int			percent_pos;     // position of %
	int			res;
}				t_env;

int		ft_printf(const char *line, ...);
t_env	*malloc_env(char *str);
void	to_buff_block(t_env *env);
void	to_buff_char(char c, t_env *env);
void	to_buff_str(char *str, t_env *env);
void	find_flag(t_env  *env, va_list args);
int		check_flag(char c);
void	set_def(t_env *env);
void	check_preflag(t_env *env);
void	set_precision(int init_index, t_env *env);
void	set_offset(int init_index, t_env *env);

void	flag_di(t_env *env, va_list args);
void	flag_o(t_env *env, va_list args);
char	*ft_itoa_o(int n);
void	print(t_env *env);

char	*space_offset(t_env *env, char *res, int minus);
char	*zero_offset(t_env *env, char *res, int minus);
char	*precision(t_env *env, char *res, int minus);
void	plus_minus(t_env *env, char **res, int minus, int num);
void	space(t_env *env, char **res, int num);
#endif

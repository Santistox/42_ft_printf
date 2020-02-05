#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h> // library to work with standard prinft
# include <stdarg.h> // library to work with indefinite number of arguments
# include "../libft/libft.h" // personal library
# include <wchar.h> // library for using wchar_t type
# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 1024

typedef struct	s_env
{
	char		*buf;            // buffer
	char		*str;			 // input line
	int			count;           // line cursor str
	int			count_buf;       // line cursor buf
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
	uintmax_t	cont;            // container help program contain big numbers
	int 		count_2;         // backup count variable value
	int 		fd;				 // file descriptor
}				t_env;

int		ft_printf(const char *line, ...);
t_env	*malloc_env(char *str);
void	error(int error_id);

/*
** buffer functions
*/
void	to_buff_block(t_env *env);
void	to_buff_char(char c, t_env *env);
void	to_buff_str(char *str, t_env *env);
void	to_buff_offset(t_env *env);

/*
** flags.c
*/
void	find_flag(t_env  *env, va_list args);
void	check_preflag(t_env *env);
int		check_flag(char c);


/*
** output.c
*/
void	sputstr(t_env *env, char *str, int n);
void	sputchar(t_env *env, char c);
void	sprint_buff(t_env *env);

void	set_def(t_env *env);

void	set_precision(int init_index, t_env *env);
void	set_offset(int init_index, t_env *env);

/*
** num flags
*/
void	flag_di(t_env *env, va_list args);
void	flag_o(t_env *env, va_list args);
void	flag_u(t_env *env, va_list args);
void	flag_x(t_env *env, va_list args);
void	flag_x_up(t_env *env, va_list args);
char	*ft_itoa_o(unsigned int n);
char	*ft_itoa_x(unsigned int n);
char	*ft_itoa_x_up(unsigned int n);
void	print(t_env *env);

/*
** num flags
*/
void	flag_s(t_env *env, va_list args);
// void	flag_c(t_env *env, int offset);
void	flag_c(t_env *env, va_list args);

char	*space_offset(t_env *env, char *res, int minus);
char	*zero_offset(t_env *env, char *res, int minus);
char	*precision(t_env *env, char *res, int minus);
void	plus_minus(t_env *env, char **res, int minus, int num);
void	space(t_env *env, char **res, int num);

/*
 *	Libft files
 */

void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strncat(char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(long long int n);
void	ft_putstr(char const *s);
char	*ft_strnew(size_t size);

#endif

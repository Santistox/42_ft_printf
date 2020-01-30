
#include "ft_printf.h"


// GOVNOCODE!

void	flag_sS(t_env *e, va_list arg)
{
	char	*next_arg;
	int		arg_size;
	char	*precise_str;

	next_arg = va_arg(arg, char *);
	if (!next_arg)
		next_arg = "(null)";
	arg_size = ft_strlen(next_arg);
	if (env->precision < arg_size && env->is_precision == 1)
	{
		env->offset -= env->precision;
		if (!(precise_str = ft_memalloc(sizeof(char) * env->precision + 1)))
			malloc_error();
		ft_memcpy(precise_str, next_arg, env->precision);
	}
	else
	{
		env->offset -= arg_size;
		precise_str = ft_strdup(next_arg);
	}
	if (!env->minus)
		put_offset_to_buf(e);
	put_str_to_buf(precise_str, e);
	if (env->minus)
		put_offset_to_buf(e);
}
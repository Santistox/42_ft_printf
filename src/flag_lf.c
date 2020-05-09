#include "ft_printf.h"

/*
** function algorithm selection
*/

void	float_flags(t_env *env, va_list args)
{
	if (env->str[env->count] == 'L')
	{
		env->count++;
		if (env->str[env->count] == 'f')
			flag_lf(env, args);
	}
	else if (env->str[env->count] == 'f')
		flag_f(env, args);
}

/*
** function of long float
*/

void	flag_lf(t_env *env, va_list args)
{
	long double	cont;

	cont = (long double)va_arg(args, long double);
	printf("%Lf DEBUG of %c\n", cont, env->str[env->count]);
}

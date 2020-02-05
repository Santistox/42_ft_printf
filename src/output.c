
#include "ft_printf.h"

void	sputstr(t_env *env, char *str, int n)
{
	while (n > 0)
	{
		sputchar(env, *str);
		n--;
		str++;
	}
}

void	sputchar(t_env *env, char c)
{
	if (env->count_buf == BUFF_SIZE)
		sprint_buff(env);
	env->buf[env->count_buf++] = c;
}

void	sprint_buff(t_env *env)
{
	if (env->count_buf > 0)
	{
		write(env->fd, env->buf, env->count_buf);
		env->res += env->count_buf;
	}
	env->count_buf= 0;
}
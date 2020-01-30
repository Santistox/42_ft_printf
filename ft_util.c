/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:19:37 by rlintill          #+#    #+#             */
/*   Updated: 2020/01/30 12:04:26 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*space_offset(t_env *env, char *res, int minus)
{
	char	*offset;
	int		leng;

	offset = NULL;
	leng = ft_strlen(res);
	if (minus)
		leng++;
	if (env->offset - leng > 0)
	{
		offset = ft_memalloc((size_t)(env->offset - leng));
		offset = ft_memset(offset, ' ', env->offset - leng);
		if (!env->minus)
			res = ft_strjoin(offset, res);
		else
			res = ft_strjoin(res, offset);
		env->res += (env->offset - leng);
	}
	if (offset != NULL)
		ft_memdel((void*)&offset);
	return (res);
}

char	*zero_offset(t_env *env, char *res, int minus)
{
	char	*offset;
	int		leng;

	offset = NULL;
	leng = ft_strlen(res);
	if (minus)
		leng += 1;
	if (env->offset - leng > 0)
	{
		offset = ft_memalloc((size_t)(env->offset - leng));
		offset = ft_memset(offset, '0', env->offset - leng);
		if (!env->minus)
			res = ft_strjoin(offset, res);
		env->res += (env->offset - leng);
	}
	if (minus)
	{
		res = ft_strjoin("-", res);
		env->res++;
	}
	if (offset != NULL)
		ft_memdel((void*)&offset);
	return (res);
}

char	*precision(t_env *env, char *res, int minus)
{
	char	*offset;
	int		leng;

	offset = NULL;
	leng = ft_strlen(res);
	if (env->offset - leng > 0)
	{
		offset = ft_memalloc((size_t)(env->offset - leng));
		offset = ft_memset(offset, '0', env->offset - leng);
		if (!env->minus)
			res = ft_strjoin(offset, res);
		env->res += (env->offset - leng);
	}
	if (minus)
	{
		res = ft_strjoin("-", res);
		env->res++;
	}
	if (offset != NULL)
		ft_memdel((void*)&offset);
	return (res);	
}

void	plus_minus(t_env *env, char **res, int minus, int num)
{
	if (!minus && env->plus && num >= 0)
	{
		*res = ft_strjoin("+", *res);
		env->res++;
	}
}

void	space(t_env *env, char **res, int num)
{
	if (env->space && num >= 0)
	{
		*res = ft_strjoin(" ", *res);
		env->res++;
	}
}

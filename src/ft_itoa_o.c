/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:56:56 by rlintill          #+#    #+#             */
/*   Updated: 2020/02/13 13:45:28 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_swap(char *i, char *j)
{
	char	temp;

	temp = *i;
	*i = *j;
	*j = temp;
}

void	ft_reverse(char **num)
{
	int		i;
	int		end;
	char	*temp;

	i = 0;
	temp = ft_strdup(*num);
	end = ft_strlen(*num) - 1;
	while (i < end)
	{
		ft_swap(&temp[i], &temp[end]);
		i++;
		end--;
	}
	if (*num != NULL)
		free(*num);
	*num = ft_strdup(temp);
	if (temp != NULL)
		ft_memdel((void*)&temp);
}

void	itoa_x_symb(char **temp, unsigned int n, char c, int base)
{
	int rem;
	int	i;

	rem = 0;
	i = 0;
	while (n > 0)
	{
		rem = n % base;
		(*temp)[i] = (rem > 9) ? ((rem - 10) + c) : (rem + '0');
		n = n / base;
		i++;
	}
	(*temp)[i] = '\0';
}

char	*base_ft_itoa(unsigned int n, char c, int base)
{
	char	*temp;
	char	*res;
	int		rem;
	int		i;

	i = 0;
	rem = 0;
	res = NULL;
	temp = NULL;
	if (n == 0)
	{
		res = ft_strjoin(res, "0");
		return (res);
	}
	temp = ft_memalloc(sizeof(char) * 25);
	itoa_x_symb(&temp, n, c, base);
	ft_reverse(&temp);
	res = ft_strdup(temp);
	if (temp != NULL)
		free(temp);
	return (res);
}

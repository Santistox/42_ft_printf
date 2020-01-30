/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:56:56 by rlintill          #+#    #+#             */
/*   Updated: 2020/01/30 16:53:30 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	power(long long int n)
{
	int	res;
	long long int	i;

	i = 1;
	res = 0;
	while (i < 1037741825 && i < n)
	{
		res++;
		i *= 8;
	}
	return (res - 1);
}

char	*ft_itoa_o(long long int n)
{
	int	i;
	int res;
	int j;
	int lim;
	int	dec;
//	int	min;

	res = 0;
//	min = ((n < 0) ? 1 : 0);
//	if (min)
//		n *= -1;
	lim = power(n);
	i = 1;
	j = 0;
	dec = 1;
	while (j < lim)
	{
		i *= 8;
		j++;
	}
	while (n > 0)
	{
		j = 0;
		dec = 1;
		while (j < lim)
		{
			dec *= 10;
			j++;
		}
		res += dec * (n / i);
		n -= i * (n / i);
		i /= 8;
		lim--;
	}
//	if (min)
//		res = 37777777778;
	return (ft_itoa(res));
}

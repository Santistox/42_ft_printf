/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlintill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:56:56 by rlintill          #+#    #+#             */
/*   Updated: 2020/01/31 16:15:57 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


/*
int	power(long long int n)
{
	int	res;
	long long int	i;

	i = 1;
	res = 0;
	while (i < n)
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

	res = 0;
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
	return (ft_itoa(res));
} 
*/

void	ft_swap(char *i, char *j)
{
	char	temp;

	temp = *i;
	*i = *j;
	*j = temp;
}

void	ft_reverse(char **num)
{
	int i;
	int	end;
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
	if (temp != NULL)
		ft_memdel((void*)num);
	*num = ft_strdup(temp);
	if (temp != NULL)
		ft_memdel((void*)&temp);
}

char	*ft_itoa_o(unsigned int n)
{
	char	*res;
	int		rem;
	int		i;

	i = 0;
	rem = 0;
	res = NULL;
	if (n == 0)
	{
		res = ft_strjoin(res, "0");
		return (res);
	}
	/*
	 *
	 *	I'm not sure about the malloc, help pls
	 *								- rlintill	
	 *
	 * */
	res = ft_memalloc(sizeof(char) * 30);
	while (n > 0)
	{
		rem = n % 8;
		res[i] = (rem > 9) ? ((rem - 10) + 'a') : (rem + '0');
		n = n/8;
		i++;
	}
	res[i] = '\0';
	ft_reverse(&res);
	return (res);
}

char	*ft_itoa_x(unsigned int n)
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
	/*
	 *
	 *	I'm not sure about the malloc, help pls
	 *								- rlintill	
	 *
	 * */
	temp = ft_memalloc(sizeof(char) * 30);
	while (n > 0)
	{
		rem = n % 16;
		temp[i] = (rem > 9) ? ((rem - 10) + 'a') : (rem + '0');
		n = n / 16;
		i++;
	}
	temp[i] = '\0';
	ft_reverse(&temp);
	res = ft_strdup(temp);
	if (temp != NULL)
		ft_memdel((void*)&temp);
	return (res);
}

char	*ft_itoa_x_up(unsigned int n)
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
	/*
	 *
	 *	I'm not sure about the malloc, help pls
	 *								- rlintill	
	 *
	 * */
	temp = ft_memalloc(sizeof(char) * 30);
	while (n > 0)
	{
		rem = n % 16;
		temp[i] = (rem > 9) ? ((rem - 10) + 'A') : (rem + '0');
		n = n / 16;
		i++;
	}
	temp[i] = '\0';
	ft_reverse(&temp);
	res = ft_strdup(temp);
	if (temp != NULL)
		ft_memdel((void*)&temp);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/13 14:51:54 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *temp;

	temp = (unsigned char *)b;
	while (len--)
		*temp++ = (unsigned char)c;
	return (b);
}

void	ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_1;
	unsigned char	*temp_2;
	unsigned		i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	temp_1 = (unsigned char*)dst;
	temp_2 = (unsigned char*)src;
	while (i < n)
	{
		temp_1[i] = temp_2[i];
		i++;
	}
	return (temp_1);
}

void	*ft_memalloc(size_t size)
{
	void	*temp;
	int		i;
	int		n;

	i = 0;
	n = size;
	if (!(temp = (void *)malloc(size)))
		return (NULL);
	while (n > 0)
	{
		((unsigned char *)temp)[i] = 0;
		n--;
		i++;
	}
	return (temp);
}

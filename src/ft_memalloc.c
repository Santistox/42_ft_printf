/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <mnidoque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:03:59 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/04 12:08:39 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		*ft_memalloc(size_t size)
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

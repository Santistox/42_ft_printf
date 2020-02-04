/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:28:42 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/04 12:10:53 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;
	int		length;

	i = 0;
	length = ft_strlen(s1);
	dest = (char*)malloc(sizeof(*dest) * (length + 1));
	if (dest == 0)
		return (0);
	while (i < length)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

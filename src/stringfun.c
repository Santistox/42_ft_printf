/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringfun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 15:47:37 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/04 12:10:17 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*start;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	len = ((s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0));
	result = ft_strnew(len);
	if ((start = result))
	{
		if (s1)
			while (*s1)
				*result++ = *s1++;
		if (s2)
			while (*s2)
				*result++ = *s2++;
		*result = '\0';
	}
	return (start);
}

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0' && j < n)
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	i = size;
	if (size >= (size_t)(-1) || (size + 1) >= (size_t)(-1))
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	str[i] = '\0';
	while (i-- > 0)
		str[i] = '\0';
	return (str);
}

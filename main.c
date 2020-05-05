/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/13 15:36:07 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int main(void)
{
	//int i;

	//i = 0;
	//printf("{%.9f}\n", -875.000001);
	//ft_printf("{red}TEST{green}COLOR{brown}SYSTEM\n");
	//ft_printf("{yellow}YES{blue}IT{purple}WORK{cyan}FINE{eoc}!\n");
	ft_printf("%+05.0f!!\n", 1.1);
	printf("%+05.0f!!!\n", 1.1);
	//scanf("%i", &i);
	return(0);
}

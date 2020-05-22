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
#include <math.h>

int main(void)
{
	//int i;

	//i = 0;
	//ft_printf("%05");
	//printf("{%.9f}\n", -875.000001);
	//ft_printf("{red}TEST{green}COLOR{brown}SYSTEM\n");
	//ft_printf("{yellow}YES{blue}IT{purple}WORK{cyan}FINE{eoc}!\n");
	ft_printf("%.1f\n", -0.00032);
	printf("%.1f\n", -0.00032);
	//ft_printf("%Lf\n", (1.0/0.0));
//	ft_printf("%f\n", (1.0/0.0));
//	printf("%f\n", (1.0/0.0));
//	ft_printf("%f\n", sqrt(-1));
//	printf("%f\n", sqrt(-1));
	//scanf("%i", &i);
	return(0);
}

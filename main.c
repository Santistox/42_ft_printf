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
	//printf("{%.9f}\n", -875.000001);
	//ft_printf("{red}TEST{green}COLOR{brown}SYSTEM\n");
	//ft_printf("{yellow}YES{blue}IT{purple}WORK{cyan}FINE{eoc}!\n");
	ft_printf("%.6f\n", 45.23);
	return(0);
}

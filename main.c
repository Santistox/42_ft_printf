/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnidoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:03:20 by mnidoque          #+#    #+#             */
/*   Updated: 2020/02/04 15:42:53 by rlintill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int main(void)
{
	// tests here
	
	int i = 0; // for leak test

//	printf("%08.3d\n", 1234);
//	ft_printf("%08.3d\n", 1234);

//	printf("%3.3s%3.3s\n", "hello", "world");
//	ft_printf("%3.3s%3.3s\n", "hello", "world");

 //	printf("20%02i%20i%i%i%i%i\n", 1,2,3,4,5,6);
	ft_printf("20%02i%20i%i%i%i%i", 1,2,3,4,5,6);
	
//	printf("ASCII value = %-5c, Character = %c\n", 'a', 76);
//	ft_printf("ASCII value = %-5c, Character = %c\n", 'a', 76);

//	printf("%c\n", 'k');
//	ft_printf("%c\n", 'k');
	scanf("%i", &i); // for leak test
	return(0);
}

// simple compile with:
// gcc *.c libft/*.c ft_printf.h libft/libft.h

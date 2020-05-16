#include "ft_printf.h"

/*
** This main for error tests
*/

int main(void)
{
	// I don't know what these tests should output
	// Other projects output \n
	// Our output is bullshit 💩
	ft_printf("%5");
	ft_printf("%05");
	ft_printf("%-05");
	ft_printf("%-5");
	return(0);
}

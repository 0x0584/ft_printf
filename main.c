/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 main.c												:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/24 20:00:58 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/27 09:12:17 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <stdio.h>

#include "buffer.h"
#include "ft_printf.h"
#include "libft.h"

#include "bigint.h"

int main(void)
{
	t_bigint *foo = bigint_pow(2, 1024);

	ft_putbigint(foo);

	ft_putendl("\n ----------- \n");
	/* printf("%.45lf\n", 9.2101978415421212445); */

	t_uint64 bits = 0x7ff0000000000000;
	char *bar = ft_dtoa(*(double *)&bits, 8);
	ft_putendl(bar);
	ft_strdel(&bar);

	bar = ft_dtoa(-0.652240, 8);
	ft_putendl(bar);
	ft_strdel(&bar);

	bar = ft_dtoa(-2145.14512021, 8);
	ft_putendl(bar);
	ft_strdel(&bar);
	
	bar = ft_dtoa(0.0, 8);
	ft_putendl(bar);
	ft_strdel(&bar);

	return 0;
}

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
	/* t_uint64 bits = 0x7ff0000000000000; */
	/* char *bar = ft_dtoa(*(double *)&bits, 8); */
	/* ft_putendl(bar); */
	/* ft_strdel(&bar); */

	/* bar = ft_dtoa(-0.652240, 9); */
	/* ft_putendl(bar); */
	/* ft_strdel(&bar); */

	/* bar = ft_dtoa(-2145.14512021, 9); */
	/* ft_putendl(bar); */
	/* ft_strdel(&bar); */

	/* bar = ft_dtoa(0.0, 9); */
	/* ft_putendl(bar); */
	/* ft_strdel(&bar); */

	/* printf("%.0f\n", 1.987); */
	/* printf("%.1f\n", 1.987); */
	/* printf("%.2f\n", 1.987); */
	/* printf("%.3f\n", 1.987); */
	/* printf("%.4f\n", 1.987); */

	/* printf("%.0f\n", 23.5); */
	/* printf("%.0f\n", 24.5); */
	/* printf("%.0f\n", 25.5); */

	/* char *foo; */
	/* foo = ft_strdup("ar"); */
	/* ft_strreplace(&foo, "art", ""); */
	/* ft_putendl(foo); */

	/* ft_strdel(&foo); */

	/* /\* printf("%.2Le", 5990909.688898973487L); *\/ */

	/* foo = ft_dtoa(0.0067); */
	/* ft_putendl(foo); */
	/* ft_strdel(&foo); */

	/* foo = ft_uitoa_base(255, "0123456789abcdef"); */
	/* ft_putendl(foo); */
	/* ft_strdel(&foo); */


	/* t_bigint *big = bigint_add(1150, 60); */
	/* ft_putstr(big->base); */
	/* getchar(); */


	/* char *foo; */

	/* char *bar = ft_strdup("this"); */
	/* ft_strpad(&bar, '0', 3, false); */
	/* ft_putendl(bar); */
	/* ft_strdel(&bar); */
	/* foo = ft_dtoa(0.01); */
	/* ft_putendl(foo); */
	/* ft_strdel(&foo); */


	/* getchar(); */
	ft_dprintf(1, "mine: %f", 0.0012);
	ft_putendl("\n---------------");
	printf("theirs: %f\n", -0.0);
	return 0;
}

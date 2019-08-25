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
#include "ieeefp.h"
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


	/* char *foo = ft_dtoa(-3.1415); */
	/* ft_putendl(foo); */
	/* ft_strdel(&foo); */
	/* getchar(); */
	/* ft_dprintf(1, "mine: %a", -3.1415); */
	/* ft_putendl("\n---------------"); */
	/* printf("theirs: %a\n", -3.1415); */

	/* t_bigint foo = bigint_init(3); */
	/* bar = bigint_init(4); */

	/* (void)printf("foo > %d\n", foo.block[0]); */
	/* (void)printf("bar > %d\n", bar.block[0]); */

	/* bigint_inadd(&foo, bar); */
	/* bigint_inadd(&foo, bar); */

	/* bigint_inmul(&foo, foo); */
	/* bigint_inmul(&foo, foo); */
	/* bigint_asbin(foo); */
	/* (void)printf("size > %u\n", foo.size); */
	/* bigint_inbls(&foo, 31); */
	/* bigint_asbin(foo); */
	/* bigint_inbls(&foo, 1); */
	/* bigint_inbls(&foo, 1); */
	/* bigint_inbls(&foo, 1); */
	/* (void)printf("\nfoo > %u\n", foo.block[0]); */
	/* (void)printf("bar > %d\n", bar.block[0]); */

	/* t_bigint ten = bigint_pow(bar, 2); */
	/* (void)printf("ten: %d", ten.block[0]); */

	/* foo = bigint_add(foo, foo); */
	/* printf("size: %ld\n", foo.size); */
	/* bigint_inbls(&foo, 3); */
	/* printf("size: %ld\n", foo.size); */

	double d = 189.00345;
	char *bar = ft_dtoa(d);
	printf(" that %lf [%s]", d, bar);
	free(bar);

	/* printf("%d", bigint_cmp(bigint_init(100), bigint_init(320))); */
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:00:58 by archid-           #+#    #+#             */
/*   Updated: 2019/07/27 09:12:17 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "ieeefp.h"

int main(void)
{
	/* ft_printf("[left %-6d right %6d zero % 06d]\n", 10, 50, -13); */
	/* ft_putendl("------------------------"); */
	/* printf("[left %-6d right %6d zero % 06d]\n", 10, 50, -13); */

	/*
	   NOTE: negative and octal are not working good? probably an
	   unsigned problem
	*/
	/* char *foo = ft_strdup("000this is000"); */
	/* ft_strctrim(&foo, '0', TOWARD_HEAD); */
	/* ft_putendl(foo); */
	/* getchar(); */
	/* ft_strctrim(&foo, '0', TOWARD_TAIL); */
	/* ft_putendl(foo); */
	/* ft_strdel(&foo); */


	char *fmt = "@ (%.4e) @ (%.3e) @ (%.0E) @ (%+10.1f) @ (%.2f) @ (%#08x) @\n";
	ft_printf(fmt, 89.999, 89.999, 1.0001343453, 89.999, 89.999, 999);
	ft_putendl("------------------------");
	printf(fmt, 89.999, 89.999, 1.0001343453, 89.999, 89.999, 999);

	/* char *bar = ieee_dtoa(0.00899L, 4); */

	/* printf("(%s)", bar); */
	/* free(bar); */
	return 0;
}

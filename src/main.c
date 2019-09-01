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


	char *fmt = "[left (%e) (%.3e) (%e) (%+10.8f) right (%#06x) zero (%#08o)]\n";
	ft_printf(fmt, 89.999, 89.999, 0.01333453, 89.999, 1412, 1993);
	ft_putendl("------------------------");
	printf(fmt, 89.999, 89.999, 0.01333453, 89.999, 1412, 1993);

	char *bar = ft_itoa_base(-13, BASE_DEC);
	/* printf("%s", bar); */
	free(bar);
	return 0;
}

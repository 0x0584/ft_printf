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

	char *fmt = "[left (%+8.2f) right (%.4f) zero (%.7f)]\n";
	ft_printf(fmt, 10.00899, 50.5555, 1993.43);
	ft_putendl("------------------------");
	printf(fmt, 10.00899, 50.5555, 1993.43);

	char *bar = ft_dtoa(0.00899L, 4);

	printf("(%s)", bar);
	free(bar);
	return 0;
}

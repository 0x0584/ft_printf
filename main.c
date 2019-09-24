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
#include "utf8.h"
#include "bigint.h"
#include <stdint.h>

int main(void)
{
	/* BUG: it seems like %O and %D should not be  */
	/* ft_printf("\n%024hho et%#1.2o %0012.O\n", (unsigned char)12, 0, 123654789); */
	/* printf("\n%024hho et%#1.2o %0012.O\n", (unsigned char)12, 0, 123654789); */

	/* ft_printf("toto %###.0o%#.O et %#.1o !\n", 0, 0, 0); */
	/* printf("toto %###.0o%#.O et %#.1o !\n", 0, 0, 0); */

	/* char *foo = "this"; */
	/* char *fmt = "[%5d]\n"; */

	/* ft_printf("cc%#.4X et %#0012x %#04hX !!\n", 0xaef, 0xe, (unsigned short)0); */
	/* printf("cc%#.4X et %#0012x %#04hX !!\n", 0xaef, 0xe, (unsigned short)0); */

	/* int ret = ft_printf("hello ca%----4c %1c va %10c%-c ??\n", '\0', '\n', (char)564, 0); */
	/* int ret2 = printf("hello ca%----4c %1c va %10c%-c ??\n", '\0', '\n', (char)564, 0); */

	/* ft_printf("%d %d\n", ret, ret2); */

	/* ft_printf("[Coucou %.0s\n%s%---12s]", "hi", "coco", NULL); */
	/* printf("[Coucou %.0s\n%s%---12s\n]", "hi", "coco", NULL); */

	/* char buffer[200]; */
	/* ft_bzero(buffer, 200); */
	/* printf("\n %s %d %d", buffer, ret, ret2); */

	ft_printf("%p %s", NULL, NULL);
	printf("%p %s", NULL, NULL);
	return 0;
}

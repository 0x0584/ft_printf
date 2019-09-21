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

int main(void)
{
	/* BUG: it seems like %O and %D should not be  */
	/* ft_printf("\n%024hho et%#1.2o %0012.O\n", (unsigned char)12, 0, 123654789); */
	/* printf("\n%024hho et%#1.2o %0012.O\n", (unsigned char)12, 0, 123654789); */

	/* ft_printf("toto %###.0o%#.O et %#.1o !\n", 0, 0, 0); */
	/* printf("toto %###.0o%#.O et %#.1o !\n", 0, 0, 0); */

	char *foo = "this";
	char *fmt = "[%5d]\n";

	ft_printf("toto%.0d et %+.i et  %   .0d !!!\n", 0, 0, 0);
	printf("toto%.0d et %+.i et  %   .0d !!!\n", 0, 0, 0);
	return 0;
}

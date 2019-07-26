/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:00:58 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 20:47:39 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "buffer.h"
#include "ft_printf.h"
#include "libft.h"

#include "bigint.h"

int main(int argc, char *argv[])
{


	/* printf("%.45lf\n", 9.2101978415421212445); */
	char *bar = ft_dtoa(9.2101978415421212445, 8);

	/* printf("%.20lf\n", 9.2101); */

	ft_putendl(bar);

	/* printf("%zu", sizeof(void *)); */
	ft_strdel(&bar);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:00:58 by archid-           #+#    #+#             */
/*   Updated: 2019/07/26 17:07:43 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "buffer.h"
#include "ft_printf.h"
#include "libft.h"

#include "bigint.h"

int main(int argc, char *argv[])
{

	t_bigint *foo = bigint_mul(150, 8);
	ft_putbigint(foo);

	ft_putendl("\n-------------");
	ft_dtoa(9.2101, 8);

	/* printf("%.20lf\n", 9.2101); */

	/* printf("%zu", sizeof(void *)); */
	/* bigint_free(&foo); */

	return 0;
}

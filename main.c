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
	ft_printf("[%.i]\n\n", 0);

	/*
	  XXX: precision issues
	  NOTE: it was about FL_PLUS and precision
	*/

	ft_printf("[toto%.0d et %+.i et  %   .0D !!!]\n", 0, 0, 0);
	printf("[toto%.0d et %+.i et  %   .0D !!!]\n", 0, 0, 0);

	ft_printf("hello % .d this is a test\n", 0);
	printf("hello % .d this is a test\n", 0);

	return 0;
}

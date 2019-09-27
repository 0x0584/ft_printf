/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:00:58 by archid-           #+#    #+#             */
/*   Updated: 2019/09/27 14:47:00 by archid-          ###   ########.fr       */
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

	ft_printf("%-+-12.7Dt%0 4i %04.2% et %lc titi\n", 125, 124, 256);
	printf("%-+-12.7Dt%0 4i %04.2% et %lc titi\n", 125, 124, 256);

	return 0;
}

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
	ft_printf("[left %-6d right %6d zero %+06d]\n", 10, 50, -13);
	ft_putendl("------------------------");
	printf("[left %-6d right %6d zero %+06d]\n", 10, 50, -13);

	char *bar = ft_itoa_base(-13, BASE_DEC);
	printf("%s", bar);
	free(bar);
	return 0;
}

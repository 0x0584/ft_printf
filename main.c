/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:00:58 by archid-           #+#    #+#             */
/*   Updated: 2019/09/26 19:18:11 by archid-          ###   ########.fr       */
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

	int ret = ft_printf("hello [ca%----4c] [%1c] va [%10c%-c] ??\n", '\0', '\n',
						(char)564, 0);
	int myret = printf("hello [ca%----4c] [%1c] va [%10c%-c] ??\n", '\0', '\n',
					   (char)564, 0);

	printf("%d %d\n", ret, myret);

	/* ft_printf("mine: [%.0s]\n[%s][%---12s]\n", "hi", "coco", NULL); */
	/* printf("theirs: [%.0s]\n[%s][%---12s]\n", "hi", "coco", NULL); */

	return 0;
}

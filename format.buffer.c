/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:17:54 by archid-           #+#    #+#             */
/*   Updated: 2019/06/27 00:34:16 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#include <stdio.h>

void	format_dbg(t_frmt *frmt)
{
	printf("conv: %d lenght: %d\n", frmt->conv, frmt->length);
	printf("arg: %d fmt:%d\n", frmt->argindex, frmt->fmtindex);
	printf("precision: %d width: %d\n", frmt->precision, frmt->width);
	printf("0 flag: %d | + flag: %d | ", frmt->prefix_zeros, frmt->prefix_signe);
	printf("' ' flag: %d | - flag: %d | ", frmt->prefix_zeros, frmt->padding_on_left);
	printf("# flag %d\n-------------------\n", frmt->is_alter);
}

void	buff_add_width(t_buff *buff, int width)
{

}

/* TODO: somehow turn all that shit into string! */
void	format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_list *e;
	t_frmt *frmt;

	(void)printf("#### here #####\n");
	e = lstfrmt;
	while (e)
	{
		frmt = (t_frmt *)e->content;

		/* /\* handle prefix_zeros  *\/ */
		/* if (frmt->precision != -1 && */
		/* 		frmt->prefix_zeros && */
		/* 		(frmt->conv == SIGNED_DECI || */
		/* 			frmt->conv == UNSIGNED_OCTA || */
		/* 			frmt->conv == UNSIGNED_HEXA || */
		/* 			frmt->conv == UNSIGNED_HEXA2)) */
		/* 	frmt->prefix_zeros = false; */

		(void)printf(">");
		format_dbg(frmt);
		e = e->next;
	}
	(void)printf(" ------ ^^^ ---- \n");
}

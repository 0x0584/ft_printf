/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.buffer.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/23 15:17:54 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/08/06 15:51:46 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "format.h"

#include <stdio.h>

void			format_dbg(t_frmt *frmt)
{
	char *format = NULL;

	if (frmt->conv == CONV_INT || frmt->conv == CONV_CHAR)
		format = "INTEGER";
	else if (frmt->conv == CONV_UOCT || frmt->conv == CONV_UDEC
				|| frmt->conv == CONV_UHEX || frmt->conv == CONV_PTR)
		format = "UNSIGNED";
	else if (frmt->conv == CONV_DBL || frmt->conv == CONV_LDBL
				|| frmt->conv == CONV_GDBL || frmt->conv == CONV_EDBL)
		format = "DOUBLE";
	else if (frmt->conv == CONV_STR || frmt->conv == CONV_FRMT)
		format = "STRING";

	printf("conv: %s lenght: %d\n", format, frmt->length);
	printf("arg: %d fmt:%d\n", frmt->iarg, frmt->ifrmt);
	printf("precision: %d width: %d\n", frmt->prec, frmt->width);
	printf("0 flag: %d | + flag: %d | ", HAS_FLAG(frmt, FL_ZERO),
											HAS_FLAG(frmt, FL_PLUS));
	printf("' ' flag: %d | - flag: %d | ", HAS_FLAG(frmt, FL_SPACE),
		   HAS_FLAG(frmt, FL_MINUS));
	printf("# flag %d\n-------------------\n", HAS_FLAG(frmt, FL_HASH));
}

void			format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_list	*e;
	t_frmt	*frmt;
	char	*s_frmt;
	size_t	padding_size;
	size_t slen;

	e = lstfrmt;
	while (e)
	{
		frmt = (t_frmt *)e->content;
		padding_size = 0;
		slen = 0;
		if ((s_frmt = format_handle_conversion(frmt)) == NULL)
			break ;
		if (frmt->width > (slen = ft_strlen(s_frmt)) && frmt->width)
			padding_size = frmt->width - slen;
		adjust_prefix(frmt, &s_frmt, &padding_size);
		adjust_precision(frmt, &s_frmt, &padding_size);
		adjust_padding(frmt, &s_frmt, &padding_size);
		buff_append(buff, s_frmt, ft_strlen(s_frmt));
		LST_NEXT(e);
		ft_strdel(&s_frmt);
	}
}

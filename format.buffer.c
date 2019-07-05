/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.buffer.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/23 15:17:54 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/06/27 00:34:16 by archid-		  ###	########.fr		  */
/*																			  */
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
	t_list	*e;
	t_frmt	*frmt;
	char	*tmp;

	e = lstfrmt;
	tmp = NULL;
	while (e)
	{
		frmt = (t_frmt *)e->content;
		/* format_dbg(frmt); */

		if (frmt->conv == SIGNED_DECI)
			tmp = ft_itoa(frmt->u_data.i);
		else if (frmt->conv == STRING || frmt->conv == STRING_FRMT)
		{
			/* ft_putendl("found first string"); */
			tmp = frmt->u_data.str;
		}
		if (tmp)
		{
			buff_append(buff, tmp, ft_strlen(tmp));
			/* ft_strdel(&tmp); */
		}

		/* buff_write(1, buff); */
		/* getchar(); */

		e = e->next;
	}
}

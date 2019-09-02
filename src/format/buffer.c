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

/*
  TODO: YOU HAVE TO create a function to everything

  those ifs must all be some foo functions, put them in an
  array or something..
*/

/*
   FIXME: this should return a bool
*/

# define HASH_FLAG_SIZE(f)		(HAS_FLAG(f, FL_HASH) + (f->conv == CONV_UHEX))

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

		/* format_dbg(frmt); */
		/* getchar(); */

		s_frmt = format_handle_conversion(frmt);

		printf("current format as string: [%s]\n", s_frmt);

		/*
		   NOTE:
		   create a fomrmat string and reedit it! stop concerning about
		   performance for now
		 */

		/* TODO: create format_set_precision(CONV_CHAR **, t_frmt *) */

		if (frmt->width > (slen = ft_strlen(s_frmt)) && frmt->width)
			padding_size = frmt->width - slen;

		/* alternate form and Sign or Space */
		flag_getprefix_or_sign(frmt, &s_frmt, &padding_size);

		flag_adjust_padding(frmt, &s_frmt, &padding_size);

		ft_putstr("must not be NULL: >>> ");
		ft_putstr(s_frmt);
		getchar();

		if (!buff_append(buff, s_frmt, ft_strlen(s_frmt)))
		{
			ft_putendl_fd("buff doesn't have a room left'", 2);
			break;
		}

		if (s_frmt == NULL)
			ft_putendl_fd("s_frmt was empty", 2);

		ft_putstr("{");
		buff_write(1, buff);
		ft_putendl("}");

		e = e->next;
		ft_strdel(&s_frmt);
	}

	if (s_frmt == NULL)
		ft_putendl_fd("s_frmt was empty", 2);
}

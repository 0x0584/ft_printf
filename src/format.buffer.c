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
	printf("0 flag: %d | + flag: %d | ", IS_FLAG(frmt->flags, FL_ZERO),
											IS_FLAG(frmt->flags, FL_PLUS));
	printf("' ' flag: %d | - flag: %d | ", IS_FLAG(frmt->flags, FL_SPACE),
		   IS_FLAG(frmt->flags, FL_MINUS));
	printf("# flag %d\n-------------------\n", IS_FLAG(frmt->flags, FL_HASH));
}

/*
  TODO: YOU HAVE TO create a function to everything

  those ifs must all be some foo functions, put them in an
  array or something..
*/

/*
   FIXME: this should return a bool
*/

void			format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_list	*e;
	t_frmt	*frmt;
	char	*s_frmt;

	e = lstfrmt;
	s_frmt = NULL;
	while (e)
	{
		frmt = (t_frmt *)e->content;
		/* format_dbg(frmt); */
		/* getchar(); */

		if (frmt->conv == CONV_INT)
			s_frmt =  handle_signed_deci(frmt);
		else if (frmt->conv == CONV_UOCT)
			s_frmt = handle_unsigned_deci(frmt, BASE_OCT);
		else if (frmt->conv == CONV_UDEC)
			s_frmt = handle_unsigned_deci(frmt, BASE_DEC);
		else if (frmt->conv == CONV_UHEX)
			s_frmt = handle_unsigned_deci(frmt, BASE_UHEX);
		else if (format_isfloat(frmt))
			s_frmt = handle_floating_point(frmt);
		else if (frmt->conv == CONV_CHAR)
			s_frmt = handle_char(frmt);
		else if (frmt->conv == CONV_STR || frmt->conv == CONV_FRMT)
			s_frmt = handle_string(frmt);

		printf("current format as string: %s", s_frmt);
		getchar();
		/* TODO: create format_set_precision(CONV_CHAR **, t_frmt *) */
		/**
		 * TODO: create format_alterform(t_frmt *)
		 *
		 * IDEA:
		 * =====
		 *
		 * if value == 0 then ret
		 * if format_isnumeric(frmt)
		 *		call buffutils_pad(dest, "0", 1) for %o
		 *		call buffutils_pad(dest, "0x", 2) for %x
		 *		call buffutils_pad(dest, "0X", 1) for %X
		 * else if format_isfloat(frmt)
		 *		dest = ft_format_ieee_float(frmt, trailing_is_on) // default off
		 */

		/*
		  XXX: free all buffutils()
		  no need for them! teh was a poor programming style!
		  I have to get back to my shape!
		*/

		/* Field width */
		if (IS_FLAG(frmt->flags, FL_MINUS) && frmt->width)
			ft_strpad(&s_frmt, ' ', frmt->width - ft_strlen(s_frmt),
						TOWARD_TAIL);

		/* Zero padding */
		if (!IS_FLAG(frmt->flags, FL_MINUS) && frmt->width
			&& !(format_isnumeric(frmt) && frmt->prec))
			ft_strpad(&s_frmt, IS_FLAG(frmt->flags, FL_ZERO) ? '0' : ' ',
					  frmt->width - ft_strlen(s_frmt)
					  - (format_getsign(frmt) == '-'), TOWARD_HEAD);

		/* Sign or Space */
		if (format_isnumeric(frmt)
			&& (IS_FLAG(frmt->flags, FL_PLUS)
				|| IS_FLAG(frmt->flags, FL_SPACE)))
			ft_strpad(&s_frmt, IS_FLAG(frmt->flags, FL_PLUS)
						? format_getsign(frmt) : ' ', 1, TOWARD_HEAD);

		/* format_alterform(&s_frmt, frmt); */
		/* format_set_precision(&s_frmt, frmt); */

		if (!buff_append(buff, s_frmt, ft_strlen(s_frmt)))
		{
			ft_putendl("buff doesn't have a room left'");
			break;
		}

		ft_putstr("[");
		buff_write(1, buff);
		ft_putendl("]");

		e = e->next;
		ft_strdel(&s_frmt);
	}

	if (s_frmt == NULL)
		ft_putendl("s_frmt was empty");
}

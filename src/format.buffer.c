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
	char	tmp_sign;
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
		   create a fomrmat string and re edit it! stop concerning about
		   performance for now
		 */

		/* TODO: create format_set_precision(CONV_CHAR **, t_frmt *) */

		if (frmt->width > (slen = ft_strlen(s_frmt)) && frmt->width)
			padding_size = frmt->width - slen;

		/* format_check_alterform(&s_frmt, frmt); */

		/* Sign or Space */
		/* XXX: plus overrides the space */
		if (frmt->conv == CONV_INT && format_getsign(frmt) != '-'
			&& (HAS_FLAG(frmt, FL_PLUS) || HAS_FLAG(frmt, FL_SPACE)))
		{

			ft_strpad(&s_frmt, HAS_FLAG(frmt, FL_PLUS) ? '+' : ' ', 1,
						TOWARD_HEAD);
			/* XXX: remove padding_size from  */
			if (padding_size)
				padding_size--;
		}

		/* Field width */
		/* TODO: Check this when flag + and space */
		if (frmt->width && padding_size && !HAS_FLAG(frmt, FL_ZERO))
			ft_strpad(&s_frmt, ' ', padding_size,
					  HAS_FLAG(frmt, FL_MINUS) ? TOWARD_TAIL : TOWARD_HEAD);

		/* Zero padding */
		/* FIXME: ignore zero padding when precision */
		if (HAS_FLAG(frmt, FL_ZERO) && !HAS_FLAG(frmt, FL_MINUS)
				&& frmt->width && padding_size
				&& !(format_isnumeric(frmt) && frmt->prec))
		{
			tmp_sign = *s_frmt;
			ft_putstr(" ?? "); ft_putendl(s_frmt);

			ft_strpad(&s_frmt, '0', padding_size, TOWARD_HEAD);

			ft_putstr(" >");
			getchar();

			if (tmp_sign == '+' && !HAS_FLAG(frmt, FL_PLUS)
					&& HAS_FLAG(frmt, FL_SPACE))
				tmp_sign = ' ';
			if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
				ft_strreplace(&s_frmt, (char []){tmp_sign, '\0'}, "");
			if (tmp_sign == '+' || tmp_sign == '-' || tmp_sign == ' ')
				ft_strinsert_at(&s_frmt, (char []){tmp_sign, '\0'}, 0);

			/* if (tmp_sign == '+' || tmp_sign == '-') */
			/* { */
			/* 	ft_strreplace(&s_frmt, (char []){tmp_sign, '\0'}, "0"); */
			/* 	ft_strreplace(&s_frmt, "0", (char []){tmp_sign, '\0'}); */
			/* } */
			ft_putendl(s_frmt);
			getchar();

			/* ft_strpad(&s_frmt, HAS_FLAG(frmt, FL_ZERO) ? '0' : ' ', */
			/* 			padding_size - (format_getsign(frmt) == '-' */
			/* 						&& HAS_FLAG(frmt, FL_ZERO)), */
			/* 			TOWARD_HEAD); */
			/* if (format_getsign(frmt) == '-' && HAS_FLAG(frmt, FL_ZERO)) */
			/* { */
			/* 	ft_strreplace(&s_frmt, "-", "0"); */
			/* 	ft_strinsert_at(&s_frmt, "-", 0); */
			/* } */
			/* if (HAS_FLAG(frmt, FL_PLUS) || HAS_FLAG(frmt, FL_SPACE)) */
			/* 	ft_strreplace(&s_frmt, "0", ""); */
		}

		/* if (frmt->width && padding_size */
		/* 		&& !(HAS_FLAG(frmt, FL_MINUS) || HAS_FLAG(frmt, FL_ZERO))) */
		/* 	ft_strpad(&s_frmt, ' ', padding_size, TOWARD_TAIL); */

		/* format_set_precision(&s_frmt, frmt); */

		if (!buff_append(buff, s_frmt, ft_strlen(s_frmt)))
		{
			ft_putendl("buff doesn't have a room left'");
			break;
		}

		ft_putstr("{");
		buff_write(1, buff);
		ft_putendl("}");

		e = e->next;
		ft_strdel(&s_frmt);
	}

	if (s_frmt == NULL)
		ft_putendl("s_frmt was empty");
}

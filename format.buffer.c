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

	if (frmt->conv == SIGNED_DECI || frmt->conv == CHAR)
	{
		format = "SIGNED_DECI || CHAR";
	}
	else if (frmt->conv == U_OCTA ||
			 frmt->conv == U_DECI ||
			 frmt->conv == U_HEXA ||
			 frmt->conv == U_HEXA2 ||
			 frmt->conv == POINTER)
	{
		format = "UNSIGNED";
	}
	else if (frmt->conv == DBL_EXP ||
			 frmt->conv == DBL_EXP2 ||
			 frmt->conv == DBL_NRML ||
			 frmt->conv == DBL_NRML2) {
		format = "DOUBLE";
	}
	else if (frmt->conv == STRING)
		format = "STRING";
	printf("conv: %s lenght: %d\n", format, frmt->length);
	printf("arg: %d fmt:%d\n", frmt->argindex, frmt->fmtindex);
	printf("precision: %d width: %d\n", frmt->precision, frmt->width);
	printf("0 flag: %d | + flag: %d | ", frmt->prefix_zeros, frmt->prefix_signe);
	printf("' ' flag: %d | - flag: %d | ", frmt->prefix_zeros,
		   frmt->padding_on_left);
	printf("# flag %d\n-------------------\n", frmt->is_alter);
}


/*
 * TODO: YOU HAVE TO create a function to everything
 *
 * those ifs must all be some foo functions, put them in an
 * array or something..
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
		format_dbg(frmt);

		if (frmt->conv == SIGNED_DECI)
			s_frmt =  handle_signed_deci(frmt);
		else if (frmt->conv == U_OCTA)
			s_frmt = handle_unsigned_deci(frmt, 8);
		else if (frmt->conv == U_DECI)
			s_frmt = handle_unsigned_deci(frmt, 10);
		else if (frmt->conv == U_HEXA || frmt->conv == U_HEXA2)
			s_frmt = handle_unsigned_deci(frmt, 16);
		else if (frmt->conv == DBL_EXP || frmt->conv == DBL_EXP2)
			s_frmt = handle_double(frmt, true);
		else if (frmt->conv == DBL_NRML || frmt->conv == DBL_NRML2)
			s_frmt = handle_double(frmt, false);
		else if (frmt->conv == CHAR)
			s_frmt = handle_char(frmt);
		else if (frmt->conv == STRING || frmt->conv == STRING_FRMT)
			s_frmt = handle_string(frmt);

		/* TODO: create format_set_precision(char **, t_frmt *) */
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

		/* padding with zero */

		/* FIXME: free all buffutils() */
		if (frmt->padding_on_left && frmt->width)
		{
			char *foo;
			foo = ft_strjoin(s_frmt,
							 buffutils_pad(' ',
										   frmt->width - ft_strlen(s_frmt)));
			ft_strdel(&s_frmt);
			s_frmt = foo;
			frmt->prefix_zeros = false;
		}

		if (frmt->width && !frmt->padding_on_left &&
			!(format_isnumeric(frmt) && frmt->precision))
			ft_strprepend(&s_frmt,
						  buffutils_pad(frmt->prefix_zeros ? '0' : ' ',
										frmt->width - ft_strlen(s_frmt) - frmt->prefix_signe));
		/* sign or space */
		if ((frmt->prefix_signe || frmt->prefix_plus_blank) &&
			format_isnumeric(frmt))
			ft_strprepend(&s_frmt,
						  buffutils_pad(frmt->prefix_signe
										? format_getsign(frmt) : ' ' , 1));
		/* format_alterform(&s_frmt, frmt); */
		/* format_set_precision(&s_frmt, frmt); */


		if (!s_frmt || !buff_append(buff, s_frmt, ft_strlen(s_frmt)))
		{
			ft_putendl("s_frmt was empty");
			getchar();
		}
		buff_write(1, buff);
		ft_putendl("");
		e = e->next;
		ft_strdel(&s_frmt);
	}
}

/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.buffer.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/23 15:17:54 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/08/06 01:46:48 by archid-          ###   ########.fr       */
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
	else if (frmt->conv == UNSIGNED_OCTA ||
			 frmt->conv == UNSIGNED_DECI ||
			 frmt->conv == UNSIGNED_HEXA ||
			 frmt->conv == UNSIGNED_HEXA2 ||
			 frmt->conv == POINTER)
	{
		format = "UNSIGNED";
	}
	else if (frmt->conv == DOUBLE_EXP ||
			 frmt->conv == DOUBLE_EXP2 ||
			 frmt->conv == DOUBLE_NORMAL ||
			 frmt->conv == DOUBLE_NORMAL2) {
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

static char		*char_to_str(char c)
{
	char *s;

	s = ft_strnew(1);
	*s = c;
	return s;
}

/*
 * TODO: YOU HAVE TO create a function to everything
 *
 * those ifs must all be some foo functions, put them in an
 * array or something..
 */

char *handle_unsigned_deci(t_frmt *frmt, int base)
{
	if (frmt->length == MODIF_LL)
		return ft_itoa_base((long long)frmt->u_data.ll, base);
	else if (frmt->length == MODIF_L)
		return ft_itoa_base((long long)frmt->u_data.l, base);
	else if (frmt->length == MODIF_H)
		return ft_itoa_base((long long)frmt->u_data.s, base);
	else
		return ft_itoa_base((long long)frmt->u_data.i, base);
}

char			*handle_signed_deci(t_frmt *frmt)
{
	if (frmt->length == MODIF_LL)
		return ft_lltoa((long long)frmt->u_data.ll);
	else if (frmt->length == MODIF_L)
		return ft_lltoa((long long)frmt->u_data.l);
	else if (frmt->length == MODIF_H)
		return ft_lltoa((long long)frmt->u_data.s);
	else
		return ft_lltoa((long long)frmt->u_data.i);
}

char			*handle_double_exp(t_frmt *frmt)
{

}

void			format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_list	*e;
	t_frmt	*frmt;
	char	*tmp;

	/*
	 * FIXME: try to allocated memory fpr exatly dest size chars
	 *
	 * IDEA:
	 * =====
	 *
	 * move over the string to count the length
	 * allocated memory for exactly that length + 1
	 * code the process of decoding
	 */
	t_int8 dest[0xff];

	ft_bzero(dest, 0xff);
	e = lstfrmt;
	tmp = NULL;
	while (e)
	{
		frmt = (t_frmt *)e->content;
		format_dbg(frmt);

		if (frmt->conv == SIGNED_DECI)
			tmp =  handle_signed_deci(frmt);
		else if (frmt->conv == UNSIGNED_OCTA)
			tmp = handle_unsigned_deci(frmt, 8);
		else if (frmt->conv == UNSIGNED_DECI)
			tmp = handle_unsigned_deci(frmt, 10);
		else if (frmt->conv == UNSIGNED_HEXA)
			tmp = handle_unsigned_deci(frmt, 16);
		else if (frmt->conv == UNSIGNED_HEXA2)
		{
			tmp = handle_unsigned_deci(frmt, 16);
			ft_strtoupper(&tmp);
		}
		else if (frmt->conv == CHAR)
		{
			if (frmt->length != MODIF_L)
				tmp = char_to_str(frmt->u_data.i);
			else
			{
				ft_bzero(dest, 5);
				ft_utf8tostr_ch(dest, frmt->u_data.i);
				tmp = ft_strdup(dest);
			}
		}
		else if (frmt->conv == STRING || frmt->conv == STRING_FRMT)
		{
			if (frmt->length != MODIF_L)
				tmp = ft_strdup(frmt->u_data.str);
			{
				int ret = ft_utf8tostr(dest, 0xff, frmt->u_data.wstr, 0xff);
				tmp = ft_strrdup(dest, dest + ret);
			}
		}
		else if (frmt->conv == DOUBLE_EXP)
			tmp = handle_double_exp(frmt);


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
			char *foo = ft_strjoin(tmp, buffutils_pad(' ', frmt->width - ft_strlen(tmp)));
			ft_strdel(&tmp);
			tmp = foo;
			frmt->prefix_zeros = false;
		}

		if (frmt->width && !frmt->padding_on_left &&
			!(format_isnumeric(frmt) && frmt->precision))
			ft_strprepend(&tmp,
						  buffutils_pad(frmt->prefix_zeros ? '0' : ' ',
										frmt->width - ft_strlen(tmp) - frmt->prefix_signe));
		/* sign or space */
		if ((frmt->prefix_signe || frmt->prefix_plus_blank) &&
			format_isnumeric(frmt))
			ft_strprepend(&tmp,
						  buffutils_pad(frmt->prefix_signe
										? format_getsign(frmt) : ' ' , 1));
		/* format_alterform(&tmp, frmt); */
		/* format_set_precision(&tmp, frmt); */


		if (!tmp || !buff_append(buff, tmp, ft_strlen(tmp)))
		{
			ft_putendl("tmp was empty");
			getchar();
		}
		buff_write(1, buff);
		ft_putendl("");
		e = e->next;
		ft_strdel(&tmp);
	}
}

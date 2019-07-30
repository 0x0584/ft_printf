/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.buffer.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/23 15:17:54 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/27 10:09:39 by archid-		  ###	########.fr		  */
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

/* TODO: somehow turn all that shit into string! */
void			format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_list	*e;
	t_frmt	*frmt;
	char	*tmp;

	/* FIXME: try to allocated memory fpr exatly dest size chars
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
		{
			tmp = ft_itoa(frmt->u_data.i);
			ft_putnumber(frmt->u_data.i);
			(void)getchar();
		}
		else if (frmt->conv == CHAR)
		{
			if (frmt->length == MODIF_L)
			{
				ft_bzero(dest, 5);
				ft_utf8tostr_ch(dest, frmt->u_data.i);
				tmp = ft_strdup(dest);
			}
			else
				tmp = char_to_str(frmt->u_data.i);
		}
		else if (frmt->conv == STRING || frmt->conv == STRING_FRMT)
		{
			if (frmt->length == MODIF_L)
			{
				int ret = ft_utf8tostr(dest, 0xff, frmt->u_data.wstr, 0xff);
				tmp = ft_strrdup(dest, dest + ret);
			}
			else
				tmp = ft_strdup(frmt->u_data.str);

		}
		else if (format_isfloat(frmt))
		{
			/* FIXME: check if this is correct */
			tmp = (char *)format_ieee_float(frmt);
		}
		else
			tmp = NULL;

		/* FIXME: check if those ifs should be if-elses */

		/* XXX: create bufferutil_pad(char, size_t) */
		/* XXX: create format_isnumeric(t_frmt *) */
		/* XXX: create format_isfloat(t_frmt *) */


		/* TODO: create format_ieee_float(t_frmt *, bool) */
		/* TODO: create format_set_precision(char **, t_frmt *) */
		/* TODO: create format_alterform(t_frmt *)
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
		/* TODO: create format_getsigne(t_frmt *) */

		ft_putstr(" tmp >> "); ft_putendl(tmp);
		/* padding with zero */
		if ((frmt->width && !frmt->padding_on_left) &&
				!(format_isnumeric(frmt) && frmt->precision))
			ft_strprepend(&tmp,
						  buffutils_pad(frmt->prefix_zeros ? '0' : ' ',
										frmt->width - ft_strlen(tmp)));
		/* sign or space */
		if ((frmt->prefix_signe || frmt->prefix_plus_blank) &&
				format_isnumeric(frmt))
			ft_strprepend(&tmp,
						  buffutils_pad(frmt->prefix_signe
										? format_getsign(frmt) : ' ' , 1));

		/* format_alterform(&tmp, frmt); */
		/* format_set_precision(&tmp, frmt); */

		if (!tmp || !buff_append(buff, tmp, ft_strlen(tmp)))
			ft_putendl("tmp was empty");
		buff_write(1, buff);
		ft_putendl("");
		/* getchar(); */
		e = e->next;
		/* FIXME: tmp could contain leaks
		 *
		 * might fix this by setting a flag when a new string is allocated
		 */
		ft_strdel(&tmp);
	}
}

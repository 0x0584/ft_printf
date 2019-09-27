/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:17:54 by archid-           #+#    #+#             */
/*   Updated: 2019/09/27 14:22:37 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#include "buffer.h"
#include "utf8.h"

t_buff		*buff_alloc(size_t size)
{
	t_buff *foo;

	if (!(foo = ALLOC(t_buff *, 1, sizeof(t_buff)))
			|| !(foo->base = ALLOC(char *, size + 1, sizeof(char))))
		return (NULL);
	foo->len = 0;
	foo->size = size;
	return (foo);
}

void		buff_free(t_buff **buff)
{
	if (!buff)
		return ;

	free((*buff)->base);
	free(*buff);
	*buff = NULL;
}

size_t		buff_append(t_buff *buff, const char *str, size_t size)
{
	char	*foo;

	if (!buff || !str)
		return (0);
	if (size + buff->len > buff->size + 1)
	{
		foo = buff->base;
		buff->size = size + buff->size * 2;
		buff->base = ALLOC(char *, size + buff->size * 2, sizeof(char));
		(void)ft_memcpy(buff->base, foo, buff->len);
		free(foo);
	}
	ft_memcpy(buff->base + buff->len, str, size);
	return (buff->len += size);
}

ssize_t		buff_write(const int fd, t_buff *buff)
{
	if (fd < 0)
		return (fd);
	return (write(fd, buff->base, buff->len));
}

void		dbg_str(char *s, bool log)
{
	/* if (!log) */
	/* 	return ; */
	/* ft_putstr("{"); */
	/* ft_putstr(s); */
	/* ft_putendl("}"); */
	/* getchar(); */
}

int			format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_frmt		*frmt;
	char		*s_frmt;
	int			n_char_convs;
	size_t		padding_size;
	size_t		slen;

	bool do_print;

	n_char_convs = 0;
	while (lstfrmt)
	{
		slen = 0;
		padding_size = 0;
		frmt = (t_frmt *)lstfrmt->content;
		do_print = frmt->conv != CONV_FRMT;
		/* BUG: '\0' this should be printed properly */
		/* n_char_convs += (frmt->conv == CONV_CHAR && ((frmt->length == MOD_L */
		/* 				  && frmt->data.wc == L'\0') || (frmt->data.c == '\0'))); */
		if (!(s_frmt = format_handle_conversion(frmt)))
			return (-1);
		if (frmt->conv == CONV_CHAR)
			slen = 1;
		else if (frmt->conv == CONV_STR && frmt->length == MOD_L)
			slen = utf8_wstrlen(frmt->data.wstr);
		else
			slen = ft_strlen(s_frmt);
		if (frmt->width >= slen && frmt->width)
			padding_size = frmt->width - slen;
		dbg_str("before prefix", do_print);
		dbg_str(s_frmt, do_print);
		adjust_prefix(frmt, &s_frmt, &padding_size);
		dbg_str("before precision", do_print);
		dbg_str(s_frmt, do_print);
		adjust_precision(frmt, &s_frmt, &padding_size);
		dbg_str("before padding", do_print);
		dbg_str(s_frmt, do_print);
		adjust_padding(frmt, &s_frmt, &padding_size);
		dbg_str("appending..", do_print);
		dbg_str(s_frmt, do_print);
		/* ft_putendl("--------------"); */
		slen = ft_strlen(s_frmt);
		/* YEAH! */
		if (frmt->is_nulchr)
		{
			slen += 1;
			if (*(s_frmt + 1))
				slen += ft_strlen(s_frmt + 1);
		}
		buff_append(buff, s_frmt, slen);
		/* getchar(); */
		ft_strdel(&s_frmt);
		LST_NEXT(lstfrmt);
	}
	return (n_char_convs);
}

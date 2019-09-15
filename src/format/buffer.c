/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.buffer.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/23 15:17:54 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/09/15 16:40:14 by archid-          ###   ########.fr       */
/*																			  */
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
	return write(fd, buff->base, buff->len);
}

int			format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_frmt		*frmt;
	char		*s_frmt;
	int			n_char_convs;
	size_t		padding_size;
	size_t		slen;

	n_char_convs = 0;
	while (lstfrmt)
	{
		slen = 0;
		padding_size = 0;
		frmt = (t_frmt *)lstfrmt->content;
		n_char_convs += (frmt->conv == CONV_CHAR && frmt->data.c == '\0');
		if (!(s_frmt = format_handle_conversion(frmt)))
			return (-1);
		if (frmt->conv == CONV_STR && frmt->length == MOD_L)
			slen = utf8_wstrlen(frmt->data.wstr);
		else if (frmt->conv == CONV_CHAR && frmt->length == MOD_L)
			slen = 1;
		else
			slen = ft_strlen(s_frmt);
		if (frmt->width > slen && frmt->width)
			padding_size = frmt->width - slen;
		adjust_prefix(frmt, &s_frmt, &padding_size);
		adjust_precision(frmt, &s_frmt, &padding_size);
		adjust_padding(frmt, &s_frmt, &padding_size);
		buff_append(buff, s_frmt, ft_strlen(s_frmt));
		ft_strdel(&s_frmt);
		LST_NEXT(lstfrmt);
	}
	return (n_char_convs);
}

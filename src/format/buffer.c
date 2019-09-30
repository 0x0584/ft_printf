/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:17:54 by archid-           #+#    #+#             */
/*   Updated: 2019/09/29 19:58:23 by archid-          ###   ########.fr       */
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

int			format_to_buff(t_list *lstfrmt, t_buff *buff)
{
	t_frmt		*frmt;
	char		*s_frmt;
	size_t		padding_size;
	size_t		slen;

	while (lstfrmt)
	{
		slen = 0;
		frmt = (t_frmt *)lstfrmt->content;
		if (!(s_frmt = format_handle_conversion(frmt)))
			return (-1);
		padding_size = format_init_padding(frmt, s_frmt);
		adjustments(frmt, &s_frmt, &padding_size);
		slen = ft_strlen(s_frmt) + frmt->is_nulchr;
		if (frmt->is_nulchr && !*s_frmt && *(s_frmt + 1))
			slen += ft_strlen(s_frmt + 1);
		buff_append(buff, s_frmt, slen);
		ft_strdel(&s_frmt);
		LST_NEXT(lstfrmt);
	}
	return (0);
}

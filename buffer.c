/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:31:59 by archid-           #+#    #+#             */
/*   Updated: 2019/06/18 12:59:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

t_buff		*buff_alloc(size_t size)
{
	t_buff *foo;

	UNLESS_RET(foo = ALLOC(t_buff *, 1, sizeof(t_buff)), NULL);
	UNLESS_RET(foo->base = ALLOC(char *, size + 1, sizeof(char)), NULL);
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

void		buff_append(t_buff *buff, const char *str, size_t size)
{
	char 	*foo;

	if (!buff || !str)
		return ;
	if (size + buff->len > buff->size + 1)
	{
		foo = buff->base;
		buff->size = size + buff->size * 2;
		buff->base = ALLOC(char *, size + buff->size * 2, sizeof(char));
		(void)ft_memcpy(buff->base, foo, buff->len);
		free(foo);
	}
	ft_memcpy(buff->base + buff->len, str, size);
	buff->len += size;
}

ssize_t		buff_write(const int fd, t_buff *buff)
{
	if (fd < 0)
		return (fd);
	return write(fd, buff->base, buff->len);
}

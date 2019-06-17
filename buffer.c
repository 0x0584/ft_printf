/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:31:59 by archid-           #+#    #+#             */
/*   Updated: 2019/06/17 19:49:20 by archid-          ###   ########.fr       */
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

void		buff_append(t_buff **buff, char *str)
{
	size_t	size;
	char 	*foo;
	t_buff	*bar;

	size = ft_strlen(str);
	if (!buff || !str)
		return ;
	if (!*buff)
	{
		if (!(bar = buff_alloc(size + 0x20)))
			return ;
		bar->len = size;
		bar->size = size + 0x20;
		(void)ft_memcpy(bar->base, str, size);
		*buff = bar;
		return ;
	}
	bar = *buff;
	if (size > (*buff)->size - (*buff)->len)
	{
		foo = bar->base;
		bar->size = size + bar->size * 2;
		bar->base = ALLOC(char *, size + bar->size * 2, sizeof(char));
		(void)ft_memcpy(bar->base, foo, bar->len);
		free(foo);
	}
	ft_memcpy(bar->base + bar->len, str, size);
	bar->len += size;
}

ssize_t		buff_write(const int fd, t_buff *buff)
{
	if (fd < 0)
		return (fd);
	return write(fd, buff->base, buff->len);
}

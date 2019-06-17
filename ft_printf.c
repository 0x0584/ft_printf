/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 02:58:13 by archid-           #+#    #+#             */
/*   Updated: 2019/06/17 19:09:17 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "buffer.h"

/* TODO: create a string functionalities */
int				ft_printfd(const int fd, const char *fmt, ...)
{
	t_buff *buff;
	int count;

	buff = buff_alloc(0x20);
	count = 0;
	while (*fmt)
	{
		fmt++;
		count++;
	}
	buff_write(fd, buff);
	buff_free(&buff);
	return (count);
}

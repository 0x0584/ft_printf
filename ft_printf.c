/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 02:58:13 by archid-           #+#    #+#             */
/*   Updated: 2019/06/18 13:20:13 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "format.h"

int		ft_printfd(const int fd, const char *fmt, ...)
{
	t_buff	*buff;
	char	*tmp;
	va_list	args;
	int		count;

	buff = buff_alloc(0x20);
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
			handle_format((char **)&fmt, &args, buff);
		else if ((tmp = ft_strchr(fmt, '%')))
		{
			buff_append(buff, fmt, tmp - fmt);
			fmt = tmp;
		}
		else
		{
			buff_append(buff, fmt, ft_strlen(fmt));
			break ;
		}
	}
	va_end(args);
	count = buff_write(fd, buff);
	buff_free(&buff);
	return (count);
}

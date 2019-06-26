/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 02:58:13 by archid-           #+#    #+#             */
/*   Updated: 2019/06/26 20:43:44 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "format.h"

void format_free(void *dat, size_t size)
{
	if (size)
		free(dat);
}

int		ft_dprintf(const int fd, const char *fmt, ...)
{
	t_buff	*buff;
	char	*tmp;
	t_list	*lstfrmt;
	int		count;
	va_list args;

	lstfrmt = NULL;
	buff = buff_alloc(0x20);
	va_start(args, fmt);
	while (*fmt)
	{
		/* ft_putendl("before handling %"); */
		if (*fmt == '%')
			handle_format((char **)&fmt, &lstfrmt);
		/* add this as a string to frmt list */
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

	ft_putendl("-------------");
	handle_relative_args(&args, lstfrmt);
	format_to_buff(lstfrmt, buff);

	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	count = buff_write(fd, buff);
	buff_free(&buff);
	return (count);
}

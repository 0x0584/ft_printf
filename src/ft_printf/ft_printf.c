/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_dprintf.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/12 02:58:13 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/06/26 20:43:44 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ft_printf.h"

/* FIXME: add negative error return  */
int		ft_printf(const char *fmt, ...)
{
	va_list args;
	t_buff	*buff;
	t_list	*lstfrmt;
	int		n_chars;

	lstfrmt = NULL;
	n_chars = 0;
	if  (!(buff = buff_alloc(0x20)))
		return (-1);
	va_start(args, fmt);
	format_parse(fmt, &lstfrmt);
	format_populate(&lstfrmt, &args);
	n_chars = format_to_buff(lstfrmt, buff);
	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	if (n_chars >= 0)
		n_chars += buff_write(1, buff);
	buff_free(&buff);
	return (n_chars);
}

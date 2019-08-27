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
#include "format.h"

#define str_len_diff(s1, s2) (s2 ? (size_t)(s2 - s1 - 1) : ft_strlen(s1))

/* int		ft_dprintf(const int fd, const char *fmt, ...) */
int		ft_printf(const char *fmt, ...)
{
	t_buff	*buff;
	char	*tmp;
	t_list	*lstfrmt;
	int		count;
	int index = 0;
	va_list args;

	lstfrmt = NULL;
	buff = buff_alloc(0x20);
	va_start(args, fmt);
	while (fmt && ++index)
	{
		if (*fmt == '%')
		{
			handle_format((char **)&fmt, &lstfrmt, &index);
			continue;
		}
		tmp = ft_strchr(fmt, '%');
		ft_lstpush(&lstfrmt, ft_lstnew(format_const_string(index,
			ft_strrdup(fmt, fmt + str_len_diff(fmt, tmp))), sizeof(t_frmt)));
		fmt = tmp;
	}
	handle_relative_args(&args, &lstfrmt);
	ft_putendl("------ handled relative args -----");
	format_to_buff(lstfrmt, buff);
	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	count = buff_write(1, buff);
	buff_free(&buff);
	return (count);
}

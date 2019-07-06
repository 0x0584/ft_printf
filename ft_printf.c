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

void	format_free(void *dat, size_t size)
{
	if (size)
		free(dat);
}

t_frmt	format_new_string(void)
{
	t_frmt frmt;

	ft_bzero(&frmt, sizeof(t_frmt));
	frmt.conv = STRING_FRMT;
	return (frmt);
}

int		ft_dprintf(const int fd, const char *fmt, ...)
{
	t_buff	*buff;
	char	*tmp;
	t_list	*lstfrmt;
	int		count;
	int index = 0;
	va_list args;
	t_frmt frmt;

	lstfrmt = NULL;
	buff = buff_alloc(0x20);
	va_start(args, fmt);
	count = 0;
	frmt = format_new_string();
	while (++index)
		if (*fmt == '%')
			handle_format((char **)&fmt, &lstfrmt, &index);
		else
		{
			tmp = ft_strchr(fmt, '%');
			frmt.u_data.str = ft_strrdup(fmt, fmt + (tmp ?
													 (size_t)(tmp - fmt - 1)
													 : ft_strlen(fmt)));
			frmt.fmtindex = index;
			ft_lstpush(&lstfrmt, ft_lstnew(&frmt, sizeof(t_frmt)));
			ft_putendl("----- dup str -----");
			ft_putendl(frmt.u_data.str);
			ft_putendl("-----  -----");
			/* getchar(); */
			/* free(frmt.u_data.str); */
			if (tmp == NULL)
				break;
			fmt = tmp;
		}

	handle_relative_args(&args, lstfrmt);
	ft_putendl("-------------");
	format_to_buff(lstfrmt, buff);
	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	count = buff_write(fd, buff);
	buff_free(&buff);
	return (count);
}

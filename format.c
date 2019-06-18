/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:20:34 by archid-           #+#    #+#             */
/*   Updated: 2019/06/18 16:23:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"

void	handle_format(char **fmt, va_list *arglst, t_buff *buff)
{
	t_frmt	conv;
	char	*base;

	base = NULL;
	conv = parse_conversion(fmt); /* TODO: parse the conversion */
	/* TODO: find the the type and va_arg(arglst, type) */
	if (IS_INT(conv) || IS_CHAR(conv))
		base = ft_itoa(va_arg(*arglst, int));
	else if (IS_STRING(conv))
		base = ft_strdup(va_arg(*arglst, char *));
	else if (IS_DOUBLE(conv))
		base = ft_ftoa(va_arg(*arglst, double));
	else if (IS_POINTER(conv))
		base = ft_ltoa_hex(va_arg(*arglst, long));
	if (base)
	{
		buff_append(buff, base, ft_strlen(base));
		free(base);
	}
}

t_frmt	parse_conversion(char **fmt)
{

}

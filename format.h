/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:16:27 by archid-           #+#    #+#             */
/*   Updated: 2019/06/18 16:11:24 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_H
# define FORMAT_H

# include "libft/libft.h"
# include "buffer.h"

# define IS_LITERAL(fmt)		(fmt.type == '%')
# define IS_INT(fmt)			(fmt.type == 'd' || fmt.type == 'i')
# define IS_UINT(fmt)			(fmt.type == 'u')
# define IS_CHAR(fmt)			(fmt.type == 'c')
# define IS_STRING(fmt)			(fmt.type == 's')
# define IS_DOUBLE(fmt)			(fmt.type == 'f' || fmt.type == 'F')
# define IS_DOUBLE_E(fmt)		(fmt.type == 'e' || fmt.type == 'E')
# define IS_DOUBLE_G(fmt)		(fmt.type == 'g' || fmt.type == 'G')
# define IS_DOUBLE_A(fmt)		(fmt.type == 'a' || fmt.type == 'A')
# define IS_HEXA(fmt)			(fmt.type == 'x' || fmt.type == 'X')
# define IS_OCTAL(fmt)			(fmt.type == 'o')
# define IS_POINTER(fmt)		(fmt.type == 'p')

typedef struct	s_format
{
	char	type;
	t_bool	isparam:1;

}				t_frmt;

void	handle_format(char **fmt, va_list *arglst, t_buff *buff);
t_frmt	parse_conversion(char **fmt);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:19:18 by archid-           #+#    #+#             */
/*   Updated: 2019/06/27 16:17:54 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTF8_H
# define UTF8_H

/*
** Universal Coded Character Set -- Transformation Format 8
*/

# include "libft.h"

# define IS_UTF8(c)		((c)&0xC0 != 0x80)


size_t	utf8_strlen(char *s);
char	*utf8_strchr(char *s, t_uint32 c);
char	*utf8_memchr(char *s, t_uint32 c, size_t size, int *index);


#endif /* UTF8_H */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:31:39 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 04:16:37 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include "libft.h"

typedef struct	s_buffer
{
	char	*base;
	size_t	len;
	size_t	size;
}				t_buff;

t_buff			*buff_alloc(size_t size);
void			buff_free(t_buff **buff);
size_t			buff_append(t_buff *buff, const char *str, size_t size);
ssize_t			buff_write(const int fd, t_buff *buff);

#endif

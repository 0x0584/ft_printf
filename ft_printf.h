/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:29:45 by archid-           #+#    #+#             */
/*   Updated: 2019/06/19 16:05:15 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include "libft/libft.h"

/* TODO: try to implement the flag $n
 *
 * in order to create the optional flag n$ we need to store the va_list
 * in an array, and index them starting at 1 */

struct va_array;

int				ft_printf(const char *fmt, ...);
int				ft_printfd(const int fd, const char *fmt, ...);

#endif

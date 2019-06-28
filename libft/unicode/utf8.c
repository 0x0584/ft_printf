/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 21:37:59 by archid-           #+#    #+#             */
/*   Updated: 2019/06/28 16:34:31 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utf8.h"

ssize_t utf8_to_utf32(t_uint32 *dest, size_t destsz, char *src, size_t srcsz);
ssize_t utf8_to_utf8(char *dest, size_t destsz, t_uint32 *src, size_t srcsz);
ssize_t utf8_to_utf8ch(char *dest, size_t destsz, t_uint32 ch);

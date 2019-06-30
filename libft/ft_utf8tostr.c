/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8tostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 23:08:36 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 01:02:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strtoutf8(t_int8 *dest, size_t destsz,
						 const t_int32 *src, size_t srcsz)
{
	size_t i;
	size_t n_bytes;

	i = 0;
	n_bytes = 0;
	while (srcsz - i && destsz - n_bytes && src[i])
		n_bytes += ft_utf8tostr_ch(dest + n_bytes, src[i++]);
	dest[n_bytes] = '\0';
	return (n_bytes);
}

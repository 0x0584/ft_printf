/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_asbin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:28:21 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

void		bigint_asbin(t_bigint u)
{
	char	*tmp;
	t_u16	i;
	t_u16	rem_bits;
	char	buff[sizeof(t_u32) * 8 + 1];

	i = u.size;
	while (i--)
	{
		tmp = ft_utoa_base(u.block[i], BASE_BIN);
		rem_bits = sizeof(t_u32) * 8 - ft_strlen(tmp);
		buff[rem_bits] = '\0';
		while (rem_bits--)
			buff[rem_bits] = '0';
		ft_putstr(buff);
		ft_putstr(tmp);
		ft_strdel(&tmp);
	}
	ft_putchar('\n');
}

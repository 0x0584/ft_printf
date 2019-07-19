/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbigint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:48:31 by archid-           #+#    #+#             */
/*   Updated: 2019/07/19 01:40:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

void			ft_putbigint(t_bigint *big)
{
	t_uint32 size;

	size = BIGINT_COUPLE_SIZE(big);
	if (big->sign)
		ft_putchar('-');
	while (size--)
	{
		ft_putchar(big->couple_digits[size] >> 4);
		if ((big->couple_digits[size] & 0xF0) ^ 0xF0)
			ft_putchar(big->couple_digits[size] & 0xF0);
	}
}

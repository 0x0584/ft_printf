/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbigint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:48:31 by archid-           #+#    #+#             */
/*   Updated: 2019/07/19 04:09:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

void			ft_putbigint(t_bigint *big)
{
	t_uint32 temp[2];

	temp[1] = BIGINT_COUPLE_SIZE(big);
	if (big->sign)
		ft_putchar('-');
	temp[0] = 0;
	ft_putendl("------- .>>> ");
	while (temp[0] < temp[1])
	{
		ft_putchar((big->couple_digits[temp[0]] >> 4) + '0');
		if ((big->couple_digits[temp[0]] & 0x0F) != 0x0F)
			ft_putchar((big->couple_digits[temp[0]] & 0x0F) + '0');
		temp[0]++;
	}
}

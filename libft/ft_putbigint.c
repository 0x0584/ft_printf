/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbigint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:48:31 by archid-           #+#    #+#             */
/*   Updated: 2019/07/20 10:59:16 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

void	ft_putbigint(t_bigint *big)
{
	t_uint32 temp[2];

	if (!big)
	{
		ft_putstr("(null)");
		return ;
	}
	temp[1] = BINT_COUPLE_SIZE(big);
	temp[0] = 0;
	if (big->sign)
		ft_putchar('-');
	while (temp[0] < temp[1])
	{
		ft_putchar(BINT_LD(big, temp[0]) + '0');
		if (BINT_IS_RD(big, temp[0]))
			ft_putchar(BINT_RD(big, temp[0]) + '0');
		temp[0]++;
	}
}

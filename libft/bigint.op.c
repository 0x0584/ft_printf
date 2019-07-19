/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 22:47:50 by archid-           #+#    #+#             */
/*   Updated: 2019/07/18 22:48:07 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

t_bigint		*bigint_add(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_mul(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_pow(t_bigint *big1, t_uint32 power);

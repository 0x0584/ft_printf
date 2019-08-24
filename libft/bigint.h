/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:01:23 by archid-           #+#    #+#             */
/*   Updated: 2019/07/25 20:45:34 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

# include "libft.h"

# define BLOCK_MAX					64
# define BLOCK_SIZE					32
# define BLOCK_MASK					0xFFFFFFFFUL

struct s_biggy
{
	t_uint32	size;
	t_uint32	block[BLOCK_MAX];
};

t_bigint	bigint_init(uintmax_t val);
t_bigint	bigint_dup(t_bigint u);
t_uint64	bigint_size(t_bigint u);

int			bigint_cmp(t_bigint u, t_bigint v);
t_bigint	bigint_maxof(t_bigint u, t_bigint v);
t_bigint	bigint_minof(t_bigint u, t_bigint v);

t_bigint	bigint_add(t_bigint u, t_bigint v);
t_bigint	bigint_sub(t_bigint u, t_bigint v);
t_bigint	bigint_mul(t_bigint u, t_bigint v);
t_bigint	bigint_bls(t_bigint u, t_uint32 shift);

t_bigint	bigint_inadd(t_bigint *u, t_bigint v);
t_bigint	bigint_insub(t_bigint *u, t_bigint v);
t_bigint	bigint_inmul(t_bigint *u, t_bigint v);
t_bigint	bigint_inbls(t_bigint *u, t_uint32 shift);

t_bigint	bigint_pow(t_bigint u, t_uint32 exp);
t_bigint	bigint_intmul(t_bigint big, t_uint32 num);
void		bigint_asbin(t_bigint u);

#endif

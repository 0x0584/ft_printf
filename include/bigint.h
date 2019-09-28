/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:01:23 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:59:37 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

# include "libft.h"

# define BLOCK_MAX					514
# define BLOCK_SIZE					0x20
# define BLOCK_MASK					0xFFFFFFFFUL

typedef struct	s_biggy
{
	t_u64			size;
	t_u32			block[BLOCK_MAX];
}				t_bigint;

t_bigint		bigint_init(uintmax_t val);
t_bigint		bigint_dup(t_bigint u);
t_u64			bigint_size(t_bigint u);

int				bigint_cmp(t_bigint u, t_bigint v);
t_bigint		bigint_maxof(t_bigint u, t_bigint v);
t_bigint		bigint_minof(t_bigint u, t_bigint v);

t_bigint		bigint_add(t_bigint u, t_bigint v);
t_bigint		bigint_sub(t_bigint u, t_bigint v);
t_bigint		bigint_mul(t_bigint u, t_bigint v);
t_bigint		bigint_bls(t_bigint u, t_u32 shift);

t_bigint		bigint_inadd(t_bigint *u, t_bigint v);
t_bigint		bigint_insub(t_bigint *u, t_bigint v);
t_bigint		bigint_inmul(t_bigint *u, t_bigint v);
t_bigint		bigint_inbls(t_bigint *u, t_u32 shift);

t_bigint		bigint_pow(t_bigint u, t_u32 exp);
t_bigint		bigint_umul(t_bigint big, t_u32 num);
void			bigint_asbin(t_bigint u);

#endif

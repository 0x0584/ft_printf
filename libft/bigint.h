/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 bigint.h											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/18 01:01:23 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/25 20:45:34 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

#include "libft.h"

# define BINT_MASK				0x0F

# define BINT_COUPLE_SIZE(b)		(b->ten_exp / 2 + (b->ten_exp % 2 != 0))
# define BINT_LD(b, c)				(b->couple_digits[c] >> 4)
# define BINT_RD(b, c)				(b->couple_digits[c] & BINT_MASK)
# define BINT_IS_RD(b, c)			(BINT_RD(b, c) != BINT_MASK)
# define BINT_SUB_LD(b1, b2, c)		(BINT_LD(b1, c) - BINT_LD(b2, c))
# define BINT_SUB_RD(b1, b2, c)		(BINT_RD(b1, c) - BINT_RD(b2, c))

struct s_biggy
{
	t_uint8		*couple_digits;
	t_uint32	ten_exp;
	bool		sign;
};


/*
** bigint.c -- BinInt allocation
*/

t_bigint		*bigint_new(const char *big_number);
t_bigint		*bigint_init(t_int128 number);
t_bigint		*bigint_clone(t_bigint *big);
void			bigint_free(t_bigint **big_number);

t_bigint		*bigint_cmp(t_bigint *b1, t_bigint *b2, bool get_max);
t_bigint		*bigint_maxof(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_minof(t_bigint *big1, t_bigint *big2);

/*
** bigint.op -- BigInt Operations
*/

t_bigint		*bigint_add(t_int128 big1, t_int128 big2);
t_bigint		*bigint_sub(t_int128 big1, t_int128 big2);
t_bigint		*bigint_mul(t_int128 big1, t_int128 big2);
t_bigint		*bigint_pow(t_int128 big1, t_int128 power);

t_bigint		*bigint_bigadd(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_bigsub(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_bigmul(t_bigint *big1, t_bigint *big2);

t_bigint		*bigint_bigpow(t_bigint *big1, t_int32 power);
char			*bigint_tostr(t_bigint *big);

/*
** bigint.sop.c -- string helpers for bigint.op.c
*/

char			*mul_as_str(const char *s1, const char *s2);
char			*sub_as_str(const char *s1, const char *s2);
char			*sum_as_str(const char *s1, const char *s2);

#endif

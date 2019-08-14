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

#include "libft.h"

#define EXP_DIFF(a, b)				(a->ten_exp - b->ten_exp)

/*
** FIXME: implement a full bigint library
**
** NOTE: This only works on positive integers for the moment!
**		 Will finish this at some point in the near future. 
*/

typedef struct	s_biggy
{
	char			*base;
	t_uint32		ten_exp;
	bool			sign;
}				t_bigint;

typedef enum	e_bigint_compare
{
	BIGINT_MAXOF, BIGINT_MINOF
}				t_bigint_cmp;


/*
** bigint.c -- BinInt allocation
*/

t_bigint		*bigint_new(const char *big_number);
void			bigint_free(t_bigint **big_number);
t_bigint		*bigint_cmp(t_bigint *b1, t_bigint *b2, t_bigint_cmp cmp);


/*
** bigint.op -- BigInt Operations
*/

t_bigint		*bigint_bigadd(t_bigint *b1, t_bigint *b2);
t_bigint		*bigint_bigmul(t_bigint *b1, t_bigint *b2);
t_bigint		*bigint_bigpow(t_bigint *b1, t_int32 power);

/* 
** bigint.other.c -- Other function fo BigInt
*/

t_bigint		*bigint_init(t_int128 number);
t_bigint		*bigint_add(t_int128 b1, t_int128 b2);
t_bigint		*bigint_mul(t_int128 b1, t_int128 b2);
t_bigint		*bigint_pow(t_int128 b1, t_int128 power);
void			bigint_refdel(void *b);

/*
** t_bigint		*bigint_sub(t_int128 b1, t_int128 b2); 
** t_bigint		*bigint_bigsub(t_bigint *b1, t_bigint *big2);
*/

/*
** bigint.sop.c -- string helpers for bigint.op.c
*/

char			*mul_as_str(const char *s1, const char *s2);
char			*sum_as_str(const char *s1, const char *s2);
char			*sub_as_str(const char *s1, const char *s2);

#endif

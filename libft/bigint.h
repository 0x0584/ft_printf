/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 01:01:23 by archid-           #+#    #+#             */
/*   Updated: 2019/07/22 13:44:11 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

#include "libft.h"

/* IDEA:

   the basic thing to do is to create a string, and wach time compute
   te next digit, store it in a character. it's better to has some sort
   constant reallocation after we have passed the limit.


   this is to solve a problem of getting teh value of teh float, since
   for example for 32bit floats is mantessa * 2 ^ (exponent - 127)
   while for 64bit is is mantessa * 2 ^ (exponent - 1023)

   ------------------------------------------------------------

						Denormalized
   Single Precision 	± 2-149 to (1 – 2-23)×2-126
   Double Precision 	± 2-1074 to (1 – 2-52)×2-1022

						Normalized
						± 2-126 to (2 – 2-23)×2127
						± 2-1022 to (2 – 2-52)×21023

						Approximate Decimal
						± approximately 10-44.85 to approximately 1038.53
						± approximately 10-323.3 to approximately 10308.3

   ------------------------------------------------------------
 */

/* what are the differences between  */
# define BIGINT_MASK				0x0F

# define BIGINT_COUPLE_SIZE(b)		(b->ten_exp / 2 + (b->ten_exp % 2 != 0))
# define BIGINT_LD(b, c)			(b->couple_digits[c] >> 4)
# define BIGINT_RD(b, c)			(b->couple_digits[c] & BIGINT_MASK)
# define BIGINT_IS_RD(b, c)			(BIGINT_RD(b, c) != BIGINT_MASK)

typedef struct	s_biggy
{
	/* each byte can hold two

	   10010111 & 0xf	-> 7
	   10010111 >> 4	-> 9
	 */
	t_uint8			*couple_digits;

	/* (-1)^{sign} \times 10^{ten_exp} */
	t_uint32		ten_exp;
	bool			sign;
}				t_bigint;

t_bigint		*bigint_new(const char *big_number);
t_bigint		*bigint_init(t_int128 number);
void			bigint_free(t_bigint **big_number);

t_bigint		*bigint_maxof(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_minof(t_bigint *big1, t_bigint *big2);

t_bigint		*bigint_add(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_sub(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_mul(t_bigint *big1, t_bigint *big2);
t_bigint		*bigint_div(t_bigint *big1, t_bigint *big2);

t_bigint		*bigint_pow(t_bigint *big1, t_uint32 power);
t_int8			 bigint_cmp(t_bigint *big1, t_bigint *big2);
t_int8			bigint_ucmp(t_bigint *big1, t_bigint *big2);

char			*bigint_tostr(t_bigint *big);

#endif

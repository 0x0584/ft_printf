/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ieee754.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 18:00:10 by archid-           #+#    #+#             */
/*   Updated: 2019/07/03 05:42:25 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IEEE754_H
# define FT_IEEE754_H

# include "types.h"

# ifdef MACHINE_IS_LITTLE_ENDIAN

/* TODO: add long double too */

typedef union u_ieee754_float		t_float754;
typedef union u_ieee754_double		t_double754;

union		u_ieee754_float
{
	float		f;
	struct	s_float
	{
		t_uint32	man:23;
		t_uint8		exp:8;
		t_uint8		neg:1;
	}			ieee;
	struct	s_float_nan
	{
		t_uint32	man:22;
		t_uint8		nan:1;
		t_uint8		exp:8;
		t_uint8		neg:1;
	}			nan;
};

union		u_ieee754_double
{
	double		d;
	struct	s_double
	{
		t_uint32	man1:32;
		t_uint32	man0:20;
		t_uint16	exp:11;
		t_uint8		neg:1;

	}			ieee;
	struct	s_double_nan
	{
		t_uint32	man1:32;
		t_uint32	man0:19;
		t_uint8		nan:1;
		t_uint16	exp:11;
		t_uint8		neg:1;
	}			nan;
};

# endif
#endif

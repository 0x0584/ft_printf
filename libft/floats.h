/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 floats.h											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/02 18:00:10 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/03 05:42:25 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef FLOATS_H
# define FLOATS_H

# include "types.h"

# ifndef MACHINE_IS_LITTLE_ENDIAN
#  error 'this implementation works on Little Endian Machines only.'
# endif

# define IEEE754_32BIT_BIAS					0x7F
# define IEEE754_64BIT_BIAS					0x3FF

/* TODO: add long double too */

typedef union u_ieee754_float		t_float32;
typedef union u_ieee754_double		t_float64;
typedef union u_ieee854_long_double	t_float128;

union		u_ieee754_float
{
	float		f;
	struct	s_float
	{
		t_uint32	m:23;
		t_uint8		e:8;
		t_uint8		s:1;
	}			ieee;
	struct	s_float_nan
	{
		t_uint32	m:22;
		t_uint8		nan:1;
		t_uint8		e:8;
		t_uint8		s:1;
	}			nan;
};

union		u_ieee754_double
{
	double		d;
	struct	s_double
	{
		t_uint32	m1:32;
		t_uint32	m0:20;
		t_uint16	e:11;
		t_uint8		s:1;

	}			ieee;
	struct	s_double_nan
	{
		t_uint32	m1:32;
		t_uint32	m0:19;
		t_uint8		nan:1;
		t_uint16	e:11;
		t_uint8		s:1;
	}			nan;
};

union		u_ieee854_long_double
{
	double		d;
	struct	s_long_double_nan
	{
		unsigned int m1:32;
		unsigned int m0:30;
		unsigned int nan:1;
		unsigned int one:1;
		unsigned int e:15;
		unsigned int s:1;
		unsigned int z:16;
	}			ieee;
	struct	s_long_double
	{
		unsigned int m1:32;
		unsigned int m0:32;
		unsigned int e:15;
		unsigned int s:1;
		unsigned int z:16;
	}			nan;
};

#endif

/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 floats.h											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/02 18:00:10 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/07/25 20:14:24 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#ifndef FLOATS_H
# define FLOATS_H

# include "types.h"

# ifndef MACHINE_IS_LITTLE_ENDIAN
#  error this implementation works on Little Endian machines only.
# endif

# define F32BIT_BIAS			(0x0000007FU)
# define F64BIT_BAIS			1023

/* TODO: add long double too */
/* TODO: find what are the special numbers */

union		u_ieee754_float
{
	float				f;
	t_uint32			i;
	struct	ieee_float
	{
		t_uint32	m:23;
		t_uint8		e:8;
		t_uint8		s:1;
	}					ieee;
};

union		u_ieee754_double
{
	double				d;
	t_uint64			i;
	struct	ieee_double
	{
		t_uint64	m:52;
		t_uint16	e:11;
		t_uint8		s:1;
	}					ieee;
};

union		u_ieee754_long_double
{
	long double			ld;
	t_uint128			i;

	struct	ieee_long_double
	{
		t_uint64	m1:64;
		t_uint64	m2:48;
		t_uint16	e:15;
		t_uint8		s:1;
	}					ieee;
};
#endif

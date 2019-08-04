/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 floats.h											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/02 18:00:10 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/25 20:14:24 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef FLOATS_H
# define FLOATS_H

# include "types.h"

# ifndef MACHINE_IS_LITTLE_ENDIAN
#  error this implementation works on Little Endian machines only.
# endif

# define F32BIT_BIAS			(0x0000007FU)
# define F32BIT_MASK_SIGN		(0x00000001U << 31U)
# define F32BIT_MASK_EXP		(0x000000FFU << 23U)
# define F32BIT_MASK_MAN		(0xFFFFFFFFU >> 9U)
# define F32BIT_SHIFT_SIGN		31U
# define F32BIT_SHIFT_EXP		23U
# define F32BIT_SHIFT_MAN		0U

# define F32BIT_MAN(f)			((f.i & F32BIT_MASK_MAN) >> F32BIT_SHIFT_MAN)
# define F32BIT_EXP(f)			((f.i & F32BIT_MASK_EXP) >> F32BIT_SHIFT_EXP)
# define F32BIT_SIGN(f)			((f.i & F32BIT_MASK_SIGN) >> F32BIT_SHIFT_SIGN)

# define F64BIT_MAN_SIZE		52

/* FIXME: add long double too */
/* FIXME: find what are the special numbers */

union		u_ieee754_float
{
	float			f;
	t_uint32		i;
	struct	ieee_float {
		t_uint32	m:23;
		t_uint8		e:8;
		t_uint8		s:1;
	} ieee;
};

union		u_ieee754_double
{
	double			d;
	t_uint64		i;
	struct	ieee_double
	{
		t_uint64	m:52;
		t_uint16	e:11;
		t_uint8		s:1;
	}		ieee;
};

#endif

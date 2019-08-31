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

# define F128BIT_MAN			63
# define F128BIT_BAIS			16383
# define F128BIT_FULLBAIS		(F128BIT_MAN + F128BIT_BAIS)
# define F128BIT_IMPL			(1ULL << F128BIT_MAN)

# define F64BIT_MAN				52
# define F64BIT_BAIS			1023
# define F64BIT_FULLBAIS		(F64BIT_MAN + F64BIT_BAIS)
# define F64BIT_IMPL			(1ULL << F64BIT_MAN)

# define F32BIT_MAN				23
# define F32BIT_BAIS			127
# define F32BIT_FULLBAIS		(F32BIT_MAN + F32BIT_BAIS)
# define F32BIT_IMPL			(1ULL << F32BIT_MAN)

# define DRAGON4_BUFF_SIZE		52

union		u_ieee754_float
{
	float				f;
	t_uint32			i;
	struct	s_ieee_float
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
	struct	s_ieee_double
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

	struct	s_ieee_long_double
	{
		t_uint64	m1:63;
		t_uint64	m2:1;
		t_uint16	e:15;
		t_uint8		s:1;
	}					ieee;
};

typedef enum		e_ieee_floating_point_types
{
	IEEE_FLOAT,
	IEEE_DOUBLE,
	IEEE_LONG_DOUBLE
}					t_ieeetype;

typedef union		u_ieee_floating_point
{
	union u_ieee754_long_double ld;
	union u_ieee754_double		d;
	union u_ieee754_float		f;
}					t_ieeefp;

typedef enum		e_ieee_floating_point_format
{
	IEEE_HEX,
	IEEE_EXPONENT,
	IEEE_NORMAL,
	IEEE_SUITABLE
}					t_ieee_fmt;

t_int32				dragon4(t_ieeefp fp, t_ieeetype type,
								char *buff, t_uint32 buff_size);
void				handle_precision(char **fp_buff, t_ieee_fmt ftype,
										int exp, int preci);
char				*ft_ftoa(float f, t_uint32 pre);
char				*ft_dtoa(double d, t_uint32 pre);
char				*ft_ldtoa(long double ld, t_uint32 pre);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ieeefp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:13:09 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ieeefp.h"
#include "format.h"

void	ieee_extract_parts(t_ieeefp *fp, t_u128 *man, t_s32 *exp)
{
	if (fp->type == IEEE_FLOAT)
	{
		*man = GET_MAN(fp->as.f.ieee.m, fp->as.f.ieee.e, F32BIT_IMPL);
		*exp = GET_EXP(fp->as.f.ieee.e, F32BIT_FULLBAIS);
	}
	else if (fp->type == IEEE_DOUBLE)
	{
		*man = GET_MAN(fp->as.d.ieee.m, fp->as.d.ieee.e, F64BIT_IMPL);
		*exp = GET_EXP(fp->as.d.ieee.e, F64BIT_FULLBAIS);
	}
	else
	{
		*man = GET_MAN(fp->as.ld.ieee.m1, fp->as.ld.ieee.e, F128BIT_IMPL);
		*exp = GET_EXP(fp->as.ld.ieee.e, F128BIT_FULLBAIS);
	}
}

void	ieee_extract_hex_parts(t_ieeefp *fp, t_u128 *man, t_s32 *exp)
{
	if (fp->type == IEEE_FLOAT)
	{
		*man = GET_MAN(fp->as.f.ieee.m, fp->as.f.ieee.e, F32BIT_IMPL);
		*exp = fp->as.f.ieee.e - F32BIT_BAIS;
	}
	else if (fp->type == IEEE_DOUBLE)
	{
		*man = GET_MAN(fp->as.d.ieee.m, fp->as.d.ieee.e, F64BIT_IMPL);
		*exp = fp->as.d.ieee.e - F64BIT_BAIS;
	}
	else
	{
		*man = GET_MAN(fp->as.ld.ieee.m1, fp->as.ld.ieee.e, F128BIT_IMPL);
		*exp = fp->as.ld.ieee.e - F128BIT_BAIS;
	}
}

bool	ieee_get_sign(t_ieeefp *fp)
{
	bool sign;

	if (fp->type == IEEE_FLOAT)
		sign = fp->as.f.ieee.s;
	else if (fp->type == IEEE_DOUBLE)
		sign = fp->as.d.ieee.s;
	else
		sign = fp->as.ld.ieee.s;
	return (sign);
}

bool	ieee_is_zero(t_ieeefp *fp)
{
	if (fp->type == IEEE_FLOAT)
		return (fp->as.f.f == 0.0);
	else if (fp->type == IEEE_DOUBLE)
		return (fp->as.d.d == 0.0);
	else
		return (fp->as.ld.ld == 0.0);
}

void	ieee_set_fp(t_ieeefp *fp, t_frmt *frmt)
{
	bool islong;

	islong = (frmt->length == MOD_L_CAP);
	if (islong)
		fp->as.ld.ld = frmt->data.ld;
	else
		fp->as.d.d = frmt->data.d;
	fp->type = islong ? IEEE_LONG_DOUBLE : IEEE_DOUBLE;
}

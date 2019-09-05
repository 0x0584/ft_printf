#include "ieeefp.h"

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

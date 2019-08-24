#include "float.h"
#include "bigint.h"

/**
 * Dragon4 Algorithm
 * ===================
 *
 * 1. get the value of IEEE 754 floating point number
 * 2. represent the number as a fraction as $\frac{num}{denum}$
 * 3. get the exponent $n$ so that we can scale the fraction as
 *		$\frac{num}{denum} = d.ddd \times 10^{n}$
 * 4.1 extract digits using integer division of
 *		$digit = num \div denum$
 * 4.2 computer the remainder after the extraction as following
 *		$num_{new} = (num_{old} - (digit * denum)) \times 10$
 * 4.3 repeat until $num \eq 0$
 *
 * Appendix:
 *
 *  value of IEEE 754 denormalized floating point number is:
 *
 *		$value = \frac{man}{2^{mansize}} \times 2^{1 - bais}$
 *
 *  value of IEEE 754 normalized floating point number is:
 *
 *		$value = 1 + \frac{man}{2^{mansize}} \times 2^{exp - bais}$
 *
 * represent the number as a fraction based on it's exponent
 *
 *		if exp >= 0	then $value = man \times 2^{exp}$
 *		if exp < 0 then $value = \frac{man}{2^{-exp}}$
 */

static const t_bigint bigten = {1, {10}};

static void		set_num_denum(t_ieeefp fp, t_ieeetype type,
								t_bigint *num, t_bigint *denum)
{
	t_uint128		man;
	t_int32			exp;

	if (type == IEEE_FLOAT)
	{
		man = (t_uint128) fp.f.ieee.m + (fp.f.ieee.e ? F32BIT_IMPL : 0ULL);
		exp = (t_int32) fp.f.ieee.e - F32BIT_FULLBAIS + (fp.f.ieee.e ? 0 : 1);
	}
	else if (type == IEEE_DOUBLE)
	{
		man = (t_uint128) fp.d.ieee.m + (fp.d.ieee.e ? F64BIT_IMPL : 0ULL);
		exp = (t_int32) fp.d.ieee.e - F64BIT_FULLBAIS + (fp.d.ieee.e ? 0 : 1);
	}
	else
	{
		man = (t_uint128) fp.ld.ieee.m1 + (fp.ld.ieee.e ? F128BIT_IMPL : 0ULL);
		exp = (t_int32) fp.ld.ieee.e - F128BIT_FULLBAIS + (fp.ld.ieee.e ? 0 : 1);
	}
	*num = bigint_init(man);
	*denum = bigint_init(1);
	if (exp >= 0)
		bigint_asbin(bigint_inbls(num, exp));
	else
		bigint_inbls(denum, -exp);
}

static t_uint32	get_sci_exponent(long double d)
{
	t_int32			exp;
	bool			sign;

	exp = 0;
	if (d == .0 || (d >= 1.0 && d <= 9.0))
		return (exp);
	sign = (d < .0);
	if (d < .0)
		d *= -1;
	if (d >= 10.0)
		while (d >= 10.0 && ++exp)
			d /= 10;
	else
		while (d < 1.0 && ++exp)
			d *= 10;
	return (sign ? -exp : exp);
}

static void		get_as_fraction(t_ieeefp fp, t_ieeetype type,
									t_bigint *num, t_bigint *denum)
{
	t_int32			exp;

	set_num_denum(fp, type, num, denum);
	if (type == IEEE_FLOAT)
		exp = get_sci_exponent(fp.f.f);
	else if (type == IEEE_DOUBLE)
		exp = get_sci_exponent(fp.d.d);
	else
		exp = get_sci_exponent(fp.ld.ld);
	if (!exp)
		return ;
	else if (exp > 0)
		bigint_inmul(denum, bigint_pow(bigten, exp));
	else
		bigint_inmul(num, bigint_pow(bigten, -exp));
}

/* to get digits of the fraction we have constructed */
static t_uint16	dumb_div(t_bigint num, t_bigint denum)
{
	t_uint16		result;
	t_bigint		foo;
	int				diff;

	result = 5;
	foo = bigint_intmul(denum, result);
	if ((diff = bigint_cmp(num, foo)) > 0)
	{
		while ((diff = bigint_cmp(num, bigint_inadd(&foo, denum))) > 0)
			result++;
		return (!diff ? result + 1 : result);
	}
	else if (diff < 0)
	{
		while ((diff = bigint_cmp(num, bigint_insub(&foo, denum)) < 0))
				result--;
		return (result - 1);
	}
	return (result);
}

void			dragon4(t_ieeefp fp, t_ieeetype type,
							char *buff, t_uint32 buff_size)
{
	t_bigint		num;
	t_bigint		denum;
	t_uint32		i;

	i = 0;
	get_as_fraction(fp, type, &num, &denum);
	while (num.size && i < buff_size)
	{
		buff[i] = '0' + dumb_div(num, denum);
		bigint_insub(&num, bigint_intmul(denum, buff[i++] - '0'));
		bigint_inmul(&num, bigten);
	}
}

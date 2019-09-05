#include "dragon4.h"
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

const t_bigint	bigten = {1, {10}};

static void		set_num_denum(t_ieeefp *fp, t_bigint *num, t_bigint *denum)
{
	t_u128		man;
	t_s32		exp;

	ieee_extract_parts(fp, &man, &exp);
	*num = bigint_init(man);
	*denum = bigint_init(1);
	if (exp > 0)
		bigint_inbls(num, exp);
	else
		bigint_inbls(denum, -exp);
}

static t_u32	get_sci_exponent(long double d)
{
	t_s32	exp;

	exp = 0;
	if (d == .0 || (d >= 1.0 && d <= 9.0))
		return (exp);
	if (d < .0)
		d *= -1;
	if (d >= 10.0)
	{
		while (d >= 10.0 && ++exp)
			d /= 10;
		return exp;
	}
	while (d < 1.0 && ++exp)
		d *= 10;
	return (-exp);
}

static t_s32	get_as_fraction(t_ieeefp *fp, t_bigint *num, t_bigint *denum)
{
	t_s32	exp;

	set_num_denum(fp, num, denum);
	if (fp->type == IEEE_FLOAT)
		exp = get_sci_exponent(fp->as.f.f);
	else if (fp->type == IEEE_DOUBLE)
		exp = get_sci_exponent(fp->as.d.d);
	else
		exp = get_sci_exponent(fp->as.ld.ld);
	if (exp == 0)
		return (0);
	else if (exp > 0)
		bigint_inmul(denum, bigint_pow(bigten, (t_u32)exp));
	else
		bigint_inmul(num, bigint_pow(bigten, (t_u32)-exp));
	return (exp);
}

/* to get digits of the fraction we have constructed */
static t_u16	dumb_div(t_bigint num, t_bigint denum)
{
	t_u16		result;
	t_bigint	foo;
	int			diff;

	result = 5;
	foo = bigint_umul(denum, result);
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

t_s32			dragon4(t_ieeefp *fp, char **abuff)
{
	t_bigint	num;
	t_bigint	denum;
	t_u32		i;
	t_s32		exp;
	char		*buff;

	i = 0;
	buff = ft_strnew(DRAGON4_BUFF_SIZE);
	exp = get_as_fraction(fp, &num, &denum);
	while (num.size && i < DRAGON4_BUFF_SIZE)
	{
		buff[i] = '0' + dumb_div(num, denum);
		bigint_insub(&num, bigint_umul(denum, buff[i++] - '0'));
		bigint_inmul(&num, bigten);
	}
	if (abuff)
		*abuff = buff;
	return (exp);
}

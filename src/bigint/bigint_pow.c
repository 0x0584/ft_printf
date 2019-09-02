#include "bigint.h"

t_bigint		bigint_pow(t_bigint u, t_uint32 exp)
{
	t_bigint tmp;
	t_uint32 exp2;

	tmp = bigint_init(1);
	if (exp == 0)
		return (tmp);
	exp2 = exp / 2;
	while (exp2--)
		tmp = bigint_mul(tmp, u);
	bigint_inmul(&tmp, tmp);
	if (exp % 2)
		bigint_inmul(&tmp, u);
	return (tmp);
}

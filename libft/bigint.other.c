/* created: 2019-08-13 22:25:47 */

#include "bigint.h"

t_bigint		*bigint_init(t_int128 number)
{
	char		*num_as_str;
	t_bigint	*big;

	num_as_str = ft_lltoa(number);
	big = bigint_new(num_as_str);
	ft_strdel(&num_as_str);
	return (big);
}

void			bigint_refdel(void *o)
{
	t_bigint **bigref;
	
	bigref = o;
	bigint_free(bigref);
}

t_bigint		*bigint_add(t_int128 big1, t_int128 big2)
{
	t_bigint *result;
	t_bigint *tmps[2];

	tmps[0] = bigint_init(big1);
	tmps[1] = bigint_init(big2);
	result = bigint_bigadd(tmps[0], tmps[1]);
	ft_memdel_all(bigint_refdel, &tmps[0], &tmps[1]);
	return (result);
}

t_bigint		*bigint_mul(t_int128 big1, t_int128 big2)
{
	t_bigint *result;
	t_bigint *tmps[2];

	tmps[0] = bigint_init(big1);
	tmps[1] = bigint_init(big2);
	result = bigint_bigmul(tmps[0], tmps[1]);
	ft_memdel_all(bigint_refdel, &tmps[0], &tmps[1]);
	return (result);
}

t_bigint		*bigint_pow(t_int128 big1, t_int128 power)
{
	t_bigint *result;
	t_bigint *tmps;

	tmps = bigint_init(big1);
	result = bigint_bigpow(tmps, power);
	bigint_free(&tmps);
	return (result);
}

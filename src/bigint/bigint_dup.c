#include "bigint.h"

t_bigint	bigint_dup(t_bigint u)
{
	t_bigint v;

	ft_memcpy(&v, &u, sizeof(t_bigint));
	return (v);
}

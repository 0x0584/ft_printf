/* 2019-08-18 20:05:32 */

#include "vlq.h"

void	vlq_add_acc(t_vlq **au, t_vlq *v)
{
	t_vlq *tmp;

	if (!au || !*au || !v)
		return ;
	tmp = vlq_add(*au, v);
	vlq_free(au);
	*au = tmp;
}

t_vlq	*vlq_add(t_vlq *u, t_vlq *v)
{
	t_vlq		*sum;
	t_int32		lens[2];
	t_uint64	carry[2];

	lens[0] = vlq_len(u);
	lens[1] = vlq_len(v);
	if (!(sum = vlq_new(MAX(lens[0], lens[1]) + 2, true)))
		return (NULL);
	ft_bzero(carry, 2 * sizeof(t_uint64));
	while (lens[0] >= 0 || lens[1] >= 0 || carry[1])
	{
		carry[0] = carry[1];
		carry[0] += GET_NUMBER(u, lens[0]);
		carry[0] += GET_NUMBER(v, lens[1]);
		carry[1] = GET_MSB(carry[0]);
		sum->base[MAX(lens[0], lens[1] + 1)] |= GET_N_MSB(carry[0]);
		lens[0]--;
		lens[1]--;
	}
	vlq_trim(&sum);
	return (sum);
}

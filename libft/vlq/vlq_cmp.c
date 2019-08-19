/* created: 2019-08-18 22:27:15 */

#include "vlq.h"

long			vlq_cmp(t_vlq *u, t_vlq *v)
{
	t_uint32 lens[2];
	t_uint32 i;

	if (!u || !v)
		return 0;
	lens[0] = vlq_len(u);
	lens[1] = vlq_len(v);
	if (lens[0] - lens[1])
		return (lens[0] - lens[1]);
	i = 0;
	while (i < lens[0] && u->base[i] == v->base[i])
		i++;
	if (i == lens[0])
		return (0);
	return (GET_N_MSB(u->base[i]) - GET_N_MSB(v->base[i]));
}

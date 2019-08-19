/* created: 2019-08-18 21:48:46 */

#include "vlq.h"

t_uint32		vlq_len(t_vlq *vlq)
{
	t_uint32 len;

	if (!vlq)
		return (0);
	while (GET_MSB(vlq->base[len]))
		len++;
	return (len + 1);
}

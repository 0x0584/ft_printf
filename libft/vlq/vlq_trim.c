/* created: 2019-08-18 22:03:25 */

#include "vlq.h"

void	vlq_trim(t_vlq **avlq)
{
	t_uint32	i;
	t_uint32	len;
	t_vlq		*vlq;

	if (!avlq || !*avlq)
		return ;
	i = 0;
	while (GET_MSB((*avlq)->base[i]))
		if (GET_N_MSB((*avlq)->base[i]))
			break ;
		else
			i++;
	if (i == 0)
		return ;
	len = vlq_len(*avlq);
	if (!(vlq = vlq_new(len - i, true)))
		return ;
	while (--len >= i)
		vlq->base[len - i] |= GET_N_MSB((*avlq)->base[len]);
	vlq_free(avlq);
	*avlq = vlq;
}

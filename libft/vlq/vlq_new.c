/* created: 2019-08-18 19:06:26 */

#include "vlq.h"

t_vlq	*vlq_new(t_uint32 length, bool sign)
{
	t_vlq		*vlq;
	t_uint32	i;

	if (!length || !(vlq = malloc(length * sizeof(t_vlq))))
		return (NULL);
	i = 0;
	vlq->sign = sign;
	while (i < length - 1)
		vlq->base[i++] = MSB;
	vlq->base[i] = 0;
	return (vlq);
}

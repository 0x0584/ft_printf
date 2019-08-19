/* created: 2019-08-19 05:58:59 */

#include "vlq.h"

void	vlq_del(void *vlq)
{
	t_vlq *foo;

	foo = vlq;
	vlq_free(&foo);
}

void	vlq_free(t_vlq **avlq)
{
	if (!avlq || !*avlq)
		return ;
	ft_memdel_all(free, (*avlq)->base, *avlq, NULL);
	*avlq = NULL;
}

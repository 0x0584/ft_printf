/*		   File:	ft_strprepend.c
 *		 Author:	ANAS RCHID
 *	Description:	NULL
 *
 *	  Created: <2019-07-06 Sat 14:50:31>
 *	  Updated: <2019-07-06 Sat 15:36:44>
 */

#include "libft.h"

void		ft_strprepend(char **dest, const char *prefix)
{
	if (!dest || !prefix)
		return ;
	else if (!*dest)
		*dest = ft_strnew(0);
	ft_strinsert_at(dest, prefix, 0);
}

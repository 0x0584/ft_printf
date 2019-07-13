/*		   File:	ft_strprepend.c
 *		 Author:	ANAS RCHID
 *	Description:	NULL
 *
 *	  Created: <2019-07-06 Sat 14:50:31>
 *	  Updated: <2019-07-06 Sat 15:36:44>
 */

#include "libft.h"

ssize_t		ft_strprepend(char **dest, const char *prefix)
{
	return (ft_strnprepend(dest, prefix, ft_strlen(prefix)));
}

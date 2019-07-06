/*		   File:	buffer.utils.c
 *		 Author:	ANAS RCHID
 *	Description:	NULL
 *
 *	  Created: <2019-07-06 Sat 14:58:57>
 *	  Updated: <2019-07-06 Sat 15:01:42>
 */

#include "buffer.h"

char	*buffutils_zeros(int n_spaces)
{
	char *s;

	UNLESS_RET(n_spaces > 0, NULL);
	UNLESS_RET(s = ft_strnew(n_spaces), NULL);
	while (n_spaces--)
		s[n_spaces] = '0';
	return (s);
}

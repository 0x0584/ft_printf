/**
 *		 File:	buffer.utils.c
 *		 Author:	ANAS RCHID
 *	Description:	NULL
 *
 *	  Created: <2019-07-06 Sat 14:58:57>
 *	  Updated: <2019-07-30 Tue 13:19:25>
 */

#include "buffer.h"

char	*buffutils_pad(const char c, size_t sz)
{
	char *s;

	UNLESS_RET(s = ft_strnew(sz), NULL);
	while (sz--)
		s[sz] = (char)c;
	return (s);
}

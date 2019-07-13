/*		   File:	ft_strprepend.c
 *		 Author:	ANAS RCHID
 *	Description:	NULL
 *
 *	  Created: <2019-07-06 Sat 14:50:31>
 *	  Updated: <2019-07-06 Sat 16:06:28>
 */

#include "libft.h"

/*
 * use va_arg to add a flag of freeing both dest and prefix or not
 * something like read's O_RDONLY
 */
ssize_t		ft_strnprepend(char **dest, const char *prefix, size_t prefixsz)
{
	char	*s;
	size_t	destsz;

	UNLESS_RET(dest && *dest, -1);
	destsz = ft_strlen(*dest);
	UNLESS_RET(s = ft_strnew(destsz + prefixsz), 0);
	while(destsz--)
		s[destsz + prefixsz] = (*dest)[destsz];
	while (prefixsz--)
		s[prefixsz] = prefix[prefixsz];
	ft_strdel(dest);
	*dest = s;
	return (destsz + prefixsz);
}

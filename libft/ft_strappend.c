#include "libft.h"

void	ft_strappend(char **astr, const char *s)
{
	if (!astr || !s)
		return ;
	else if (!*astr)
		*astr = ft_strnew(0);
	ft_strinsert_at(astr, s, ft_strlen(*astr));
}

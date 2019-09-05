#include "libft.h"

void	ft_strchange(char **astr, char *s)
{
	ft_strdel(astr);
	*astr = s;
}

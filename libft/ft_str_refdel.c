#include "libft.h"

void	ft_str_refdel(void *strref)
{
	char **pstr;
	
	pstr = strref;
	ft_strdel(pstr);
}

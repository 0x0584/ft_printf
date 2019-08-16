#include "libft.h"

void	ft_strtoupper(char **str)
{
	char *tmp;
	
	if (!str || !*str)
		return ;
	tmp = *str;
	while (tmp)
	{
		if (*tmp >= 'a' && *tmp <= 'z')
			*tmp -= 0x20;
		tmp++;
	}
}

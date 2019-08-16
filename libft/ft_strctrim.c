#include "libft.h"

void	ft_strctrim(char **str, char c)
{
	size_t	index;
	char	*bar;
	
	if (!str || !*str || !c)
		return ;
	index = 0;
	bar = *str;
	while (bar[index] == c)
		index++;
	bar = (bar[index] ? ft_strdup(bar + index) : ft_strnew(0));
	ft_strdel(str);
	*str = bar;
}

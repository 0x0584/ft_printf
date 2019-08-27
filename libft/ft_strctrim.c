#include "libft.h"

void	ft_strctrim(char **str, char c, bool left)
{
	char *head;
	char *tail;

	if (!str || !*str || !c)
		return ;
	head = *str;
	tail = head + ft_strlen(*str);
	while ((left ? *head : *tail) == c)
		(void)(left ? head++ : tail--);
	ft_strdel(str);
	*str = ft_strrdup(head, tail);
}

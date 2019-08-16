#include "libft.h"

size_t		ft_strichr(const char *s, char c)
{
	char *ptr;
	
	ptr = ft_strchr(s, c);
	return (ptr ? ptr - s : -1);
}

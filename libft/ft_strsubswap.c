#include "libft.h"

void	ft_strsubswap(char **astr, const char *s1, const char *s2)
{
	if (!SAFE_PTRVAL(astr))
		return ;

	ft_strreplace(astr, s1, s2);
	ft_strreplace(astr, s2, s1);
}

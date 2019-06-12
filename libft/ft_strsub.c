/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_strsub.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/04 05:42:35 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/04/08 08:07:41 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*buff;
	size_t	i;

	i = 0;
	if (!s || !(buff = ALLOC(char *, len + 1, sizeof(char))))
		return (NULL);
	while (s[start] && len)
	{
		buff[i] = s[start + i];
		i++;
		len--;
	}
	return (buff);
}

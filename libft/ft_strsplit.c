/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_strsplit.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/05 06:51:01 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/04/08 10:32:46 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**aspltd;
	char	*range[2];
	size_t	tmp[2];

	if (!s)
		return (NULL);
	tmp[0] = 0;
	tmp[1] = ft_wordcount(s, c) + 1;
	if (!(aspltd = ALLOC(char **, tmp[1], sizeof(char *))))
		return (NULL);
	while (tmp[0] < tmp[1] - 1)
	{
		while (*s && *s == c)
			s++;
		range[0] = (char *)s;
		while (*s && *s != c)
			s++;
		range[1] = (char *)s - 1;
		aspltd[tmp[0]++] = ft_strrdup(range[0], range[1]);
	}
	return (aspltd);
}

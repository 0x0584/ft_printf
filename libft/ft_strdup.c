/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_strdup.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/03/31 00:04:18 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/04/06 08:46:52 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	length;
	char	*buff;

	i = -1;
	length = ft_strlen(str) + 1;
	if (!(buff = ALLOC(char *, length, sizeof(char))))
		return (NULL);
	while (++i < length - 1)
		buff[i] = str[i];
	return (buff);
}

/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_dumb_realloc.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/18 01:40:07 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/05/01 03:15:54 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_dumb_realloc(void **ptr, size_t oldsz, size_t newsz)
{
	/* void *mem; */
	/* void *tmp; */

	/* if (!(mem = ALLOC(void *, 1, newsz))) */
	/*	return (NULL); */
	/* (void)ft_memcpy(mem, ptr, oldsz); */
	/* tmp = *ptr; */
	/* free(*ptr); */
	/* return (*ptr = mem); */

	/* FIXME: you need to check this again! */
	return (ptr + oldsz - newsz);
}

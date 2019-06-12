/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_lstnew.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/07 07:02:23 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/04/07 08:37:43 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *alst;

	if (!(alst = ALLOC(t_list *, 1, sizeof(t_list))))
		return (NULL);
	alst->content = content ? ft_memdup(content, content_size) : NULL;
	alst->content_size = content ? content_size : 0;
	return (alst);
}

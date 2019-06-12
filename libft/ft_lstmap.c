/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_lstmap.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/07 08:47:01 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/04/07 09:25:43 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp[2];

	if (!lst || !(*tmp = ALLOC(t_list *, 1, sizeof(t_list))))
		return (NULL);
	*tmp = ft_memdup((*f)(lst), sizeof(t_list));
	tmp[1] = *tmp;
	while ((lst = lst->next))
	{
		tmp[1]->next = ft_memdup((*f)(lst), sizeof(t_list));
		tmp[1] = tmp[1]->next;
	}
	return (*tmp);
}

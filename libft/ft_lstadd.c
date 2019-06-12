/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_lstadd.c										:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <marvin@42.fr>						+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/04/07 07:53:21 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/04/07 08:42:19 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (SAFE_PTRVAL(alst) && new)
	{
		tmp = *alst;
		new->next = tmp;
		*alst = new;
	}
	if (!alst)
		return (0);
	else if (!*alst)
		*alst = new;
	return (1);
}

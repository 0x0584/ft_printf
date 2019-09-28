/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 07:27:42 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 18:02:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **alst)
{
	t_list *tmp[2];

	if (!SAFE_PTRVAL(alst))
		return (NULL);
	tmp[0] = *alst;
	while (tmp[0]->next)
		tmp[0] = tmp[0]->next;
	tmp[1] = tmp[0];
	tmp[0] = NULL;
	return (tmp[1]);
}

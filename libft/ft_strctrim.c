/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 05:58:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:51:21 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strctrim(char **str, char c, bool left)
{
	char *head;
	char *tail;
	char *tmp;

	if (!str || !*str || !c)
		return ;
	head = *str;
	tail = head + ft_strlen(*str) - 1;
	while (*head && tail > *str && (left ? *head : *tail) == c)
		(void)(left ? head++ : tail--);
	tmp = ft_strrdup(head, tail);
	ft_strdel(str);
	*str = tmp;
}

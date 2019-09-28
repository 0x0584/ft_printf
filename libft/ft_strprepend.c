/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:50:31 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 17:46:26 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strprepend(char **dest, const char *prefix)
{
	if (!dest || !prefix)
		return ;
	else if (!*dest)
		*dest = ft_strnew(0);
	ft_strinsert_at(dest, prefix, 0);
}

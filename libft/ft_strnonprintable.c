/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnonprintable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:40:19 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 18:16:47 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnonprintable(const char *str)
{
	char	*np;
	char	*hex;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	np = ft_strnew(0);
	while (str[i])
	{
		if (ft_isprint((int)str[i]))
			ft_strappend(&np, (char[]){str[i], '\0'});
		else
		{
			hex = ft_itoa_base((int)str[i], BASE_OCT);
			ft_strpad(&hex, '0', (t_u32)(2 - ft_strlen(hex)), TOWARD_HEAD);
			ft_strappend(&np, (char[]){'\\', '0', '\0'});
			ft_strappend(&np, hex);
			free(hex);
		}
		i++;
	}
	return (np);
}

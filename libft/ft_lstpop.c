/*
 * File: ft_lstpop.c
 * Author: Anas Rchid (0x0584)
 *
 * Created: <2019-05-22 Wed 07:27:42>
 * Updated: <2019-05-22 Wed 07:50:52>
 *
 * Copyright (C) 2019
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.	If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

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

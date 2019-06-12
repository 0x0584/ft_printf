/*
 * File: ft_swap.c
 * Author: Anas Rchid (0x0584)
 *
 * Created: <2019-05-11 Sat 03:52:32>
 * Updated: <2019-05-11 Sat 03:54:49>
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

int			ft_swap(void *u, void *v, size_t size)
{
	void *tmp;

	if (!(tmp = ALLOC(void *, 1, size)))
		return (0);
	ft_memcpy(tmp, v, size);
	ft_memcpy(v, u, size);
	ft_memcpy(u, tmp, size);
	return (1);
}

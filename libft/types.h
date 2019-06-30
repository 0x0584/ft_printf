/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 01:22:11 by archid-           #+#    #+#             */
/*   Updated: 2019/06/30 01:24:41 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TYPES_H
# define TYPES_H

# define INT_VALMAX			(2147483647)
# define INT_VALMIN			(-2147483648)

typedef void				*t_obj;

typedef signed char			t_int8;
typedef signed short		t_int16;
typedef signed int			t_int32;
typedef signed long			t_int64;
typedef signed long long	t_int128;

typedef unsigned char		t_uint8;
typedef unsigned short		t_uint16;
typedef unsigned int		t_uint32;
typedef unsigned long		t_uint64;
typedef unsigned long long	t_uint128;

typedef struct	s_list		t_list;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 01:22:11 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 18:24:50 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>

# define INT_VALMAX					(2147483647)
# define INT_VALMIN					(-2147483648)

/*
** there's a good question on how to get the type of endian on your machine
** https://stackoverflow.com/q/12791864/5744492
*/

# define MACHINE_IS_LITTLE_ENDIAN

/*
**			   --------------- Number types ---------------
*/

typedef char						t_s8;
typedef short						t_s16;
typedef int							t_s32;
typedef long						t_s64;
typedef long long					t_s128;

typedef unsigned char				t_u8;
typedef unsigned short				t_u16;
typedef unsigned int				t_u32;
typedef unsigned long				t_u64;
typedef unsigned long long			t_u128;

/*
**		--------------- Objects are just (void *) ---------------
*/

typedef void						*t_obj;

/*
**			  --------------- List types ---------------
*/

typedef struct s_list				t_list;
typedef struct s_list				*t_plist;

#endif

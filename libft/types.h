/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 types.h											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/30 01:22:11 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/02 18:24:06 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define INT_VALMAX			(2147483647)
# define INT_VALMIN			(-2147483648)

/*
** there's a good question on how to get the type of endian on your machine
** https://stackoverflow.com/q/12791864/5744492
*/

# define MACHINE_IS_LITTLE_ENDIAN

/*
**			   --------------- Basic types ---------------
*/

typedef char				t_int8;
typedef short				t_int16;
typedef int					t_int32;
typedef long				t_int64;
typedef long long			t_int128;

typedef unsigned char		t_uint8;
typedef unsigned short		t_uint16;
typedef unsigned int		t_uint32;
typedef unsigned long		t_uint64;
typedef unsigned long long	t_uint128;

/*
**		--------------- Objects are just (void *) ---------------
*/

typedef void				*t_obj;

/*
**			  --------------- List types ---------------
*/

typedef struct s_list		t_list;
typedef struct s_list		*t_plist;

#endif

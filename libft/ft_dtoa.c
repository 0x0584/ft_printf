/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_dtoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/25 19:48:43 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/26 21:51:20 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

#define BUFF_SIZE			52

char			*ft_dtoa(double d)
{
	char			*buff;
	t_ieeefp		fp;

	buff = ft_strnew(BUFF_SIZE);
	fp.d.d = d;
	dragon4(fp, IEEE_DOUBLE, buff, BUFF_SIZE);
	return (buff);
}

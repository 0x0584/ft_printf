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
#include "ieeefp.h"

char	*ft_dtoa(double d)
{
	char		*buff;
	t_int32		exp;
	t_ieeefp	fp;

	buff = ft_strnew(DRAGON4_BUFF_SIZE);
	fp.d.d = d;
	exp = dragon4(fp, IEEE_DOUBLE, buff, DRAGON4_BUFF_SIZE);
	ft_putendl("----");
	handle_precision(&buff, IEEE_NORMAL, exp, 6);
	return (buff);
}

/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_ftoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/30 02:45:42 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/02 18:38:14 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ftoa(float f, t_int8 precision)
{
	t_float754 foo;

	foo.f = f;

	ft_putnbr(precision);
	ft_putendl("");
	ft_putnbr(foo.ieee.man);
	ft_putendl("");
	ft_putnbr(foo.ieee.exp);
	ft_putendl("");
	ft_putnbr(foo.ieee.neg);
	ft_putendl("");

	return (NULL);
}

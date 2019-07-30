/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 main.c												:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/24 20:00:58 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/27 09:12:17 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <stdio.h>

#include "buffer.h"
#include "ft_printf.h"
#include "libft.h"

#include "bigint.h"

int main(int argc, char *argv[])
{
	ft_printf("this is a %06d test and this %6d\n", 10, 50);
	ft_putendl("------------------------");
	printf("this is a %06d test and this %6.5d\n", 10, 50);
	return 0;
}

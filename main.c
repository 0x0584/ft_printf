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

/* FIXME: negative number and 0-flag */

int main(int argc, char *argv[])
{

	ft_printf("[this is a %6d test and this %-6d]\n", 10, 50);
	ft_putendl("------------------------");
	printf("[this is a %10.8d test and this %-6d]\n", 220, 50);

	/* char *bar = ft_itoa_base(255, 16); */
	/* printf("%s", bar); */
	/* free(bar); */
	return 0;
}

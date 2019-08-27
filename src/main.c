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
#include "ft_printf.h"

int main(void)
{
	ft_printf("[this is a %-6d test and this %-6d]\n", 10, 50);
	ft_putendl("------------------------");
	printf("[this is a %-6d test and this %-6d]\n", 10, 50);

	char *bar = ft_itoa_base(255, BASE_LHEX);
	printf("%s", bar);
	free(bar);
	return 0;
}

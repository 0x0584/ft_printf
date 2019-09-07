/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:00:58 by archid-           #+#    #+#             */
/*   Updated: 2019/07/27 09:12:17 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include "ieeefp.h"
#include "utf8.h"

int main(void)
{
	/* ft_printf("[left %-6d right %6d zero % 06d]\n", 10, 50, -13); */
	/* ft_putendl("------------------------"); */
	/* printf("[left %-6d right %6d zero % 06d]\n", 10, 50, -13); */


	/*
	   NOTE: negative and octal are not working good? probably an
	   unsigned problem
	*/

	/* char *foo = ft_strdup("000this is000"); */
	/* ft_strctrim(&foo, '0', TOWARD_HEAD); */
	/* ft_putendl(foo); */
	/* getchar(); */
	/* ft_strctrim(&foo, '0', TOWARD_TAIL); */
	/* ft_putendl(foo); */
	/* ft_strdel(&foo); */

	/* t_ieeefp fp; */

	/* fp.d.d = 0; */
	/* fp.d.ieee.e = 0x7FF; */

	/* double dd = 0.99999; */

	/* printf("%d", MAX(-1, 0)); */
	/* char *fmt = "(%8.2s) (%8.8s) (%8.10s) (%8.0s)\n"; */

	/* ft_printf(fmt,  "this", "this", "this", "this"); */
	/* ft_putendl("------------------------"); */
	/* printf(fmt, "this", "this", "this", "this"); */
	/* char foo[5]; */
	/* char *dest = NULL, *dest2 = ft_strnew(0); */

    wchar_t *wstr = L"♥♦♣♠", *bar = wstr;


	/* while (*bar != L'\0') */
	/* { */
	/* 	ft_bzero(foo, 5); */
	/* 	u8_tostr_ch(foo, *bar++); */
	/* 	ft_strappend(&dest2, foo); */
	/* } */
	/* u8_tostr(&dest, wstr); */

	/* printf("(%s) %u", dest, sizeof(wchar_t)); */
	/* free(dest2); */

	char *fmt = "%{cyan_fg} this (%%) %{red_fg} (%2$.3ls) %{reset} "
		"%{bold} (%1$.4f) %{reset}\n";
	char *s = NULL;

	ft_printf(fmt, 0.099382, bar);
	ft_dprintf(2, fmt, 0.099382, bar);
	ft_asprintf(&s, fmt, 0.099382, bar);

	ft_putstr(s);
	free(s);
	/* int ret = printf(" this is", 10); */
	/* printf("%d", ret); */
	/* char *bar = ieee_dtoa(0.00899L, 4); */

	/* printf("(%s)", bar); */
	/* free(bar); */
	return 0;
}

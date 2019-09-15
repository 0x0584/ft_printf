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
#include "bigint.h"

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

    	// wchar_t *wstr = L"漢字漢字漢字", *bar = L"♥♦♣♠";

	/* while (*bar != L'\0') */
	/* { */
	/* 	ft_bzero(foo, 5); */
	/* 	u8_tostr_ch(foo, *bar++); */
	/* 	ft_strappend(&dest2, foo); */
	/* } */
	/* u8_tostr(&dest, wstr); */

	/* printf("(%s) %u", dest, sizeof(wchar_t)); */
	/* free(dest2); */

	/* char *fmt = "%{cyan_fg}(%1$#06d)\n(%1$#06x)\n(%1$#06u)\n(%1$#06o)%{reset}\n"; */
	/* char *s = NULL; */

	/* printf(fmt, 50); */
	/* printf(" ]]] (%.a)", (double)2); */
	/* ft_printf("(%1$#06d)\n(%1$#06x)\n(%1$#06u)\n(%1$#06o)\n", 1412); */
	/* ft_printf("(%1$#06d) (%1$#06x) (%1$#06u) (%1$#06o)\n", 1412); */
	/* ft_printf("one: (%2$+.f) (%1$5.3e) (%2$a) (%1$+8.4g)\n", (double)39, (double)2); */
	/* ft_printf("one: (%2$+.f) (%1$5.3e) (%2$a) (%1$+8.4g)\n", 39.0, 2.0); */
	/* ft_printf("two: (%2$+.Lf) (%1$5.3Le) (%2$La) (%1$+8.4Lg)\n", 3999999.1415L, 88882.7182L); */

	/* ft_printf("(%2$.3ls) (%1$.3s) (%2$ls) (%1$s)", "this", L"♥♦♣♠"); */
	/* ft_printf("(%2$8.3ls) (%1$8.3s) (%2$8ls) (%1$8s)", "this", L"♥♦♣♠"); */
	/* ft_printf("(%0*d) (%*.*d)", 5, 10, 5, 5, 10); */

	ft_printf("%{yellow_fg}%{underline}Flag d test:%{reset}%{yellow_fg}\n\n"
			  "(%1$d) (%1$.6d) (%1$6d) (%1$6.6d) (%1$06d)\n"
			  "(%1$+d) (%1$-6.3d) (%1$+6.3d) (%1$06d) (%1$+06d) (%1$06.3d)\n\n"
			  "Flag x test:\n"
			  "(%1$x) (%1$.6x) (%1$6x) (%1$6.6x) (%1$06x)\n"
			  "(%1$+x) (%1$-6.3x) (%1$+6.3x) (%1$06x) (%1$+06x) (%1$06.3x)\n\n"
			  "Flag o test:\n"
			  "(%1$o) (%1$.6o) (%1$6o) (%1$6.6o) (%1$06o)\n"
			  "(%1$+o) (%1$-6.3o) (%1$+6.3o) (%1$06o) (%1$+06o) (%1$06.3o)\n\n"
			  "Flag u test:\n"
			  "(%1$u) (%1$.6u) (%1$6u) (%1$6.6u) (%1$06u)\n"
			  "(%1$+u) (%1$-6.3u) (%1$+6.3u) (%1$06u) (%1$+06u) (%1$06.3u)"
			  "\n%{reset}\n",
			  1412);

	ft_printf("%{green_fg}%{underline}Flag f test:%{reset}%{green_fg}\n\n"
			  "(%1$f) (%1$.6f) (%1$6f) (%1$6.3f) (%1$6.6f) (%1$6.8f) (%1$06f)\n"
			  "(%1$+f) (%1$-6.3f) (%1$+6.3f) (%1$06f) (%1$+06f) (%1$06.3f)\n\n"
			  "Flag a test:\n"
			  "(%1$a) (%1$.6a) (%1$6a) (%1$6.6a) (%1$06a)\n"
			  "(%1$+a) (%1$-6.3a) (%1$+6.3a) (%1$06a) (%1$+06a) (%1$06.3a)\n\n"
			  "Flag e test:\n"
			  "(%1$e) (%1$.6e) (%1$6e) (%1$6.6e) (%1$06e)\n"
			  "(%1$+e) (%1$-6.3e) (%1$+6.3e) (%1$06e) (%1$+06e) (%1$06.3e)\n\n"
			  "Flag g test:\n"
			  "(%1$g) (%1$.6g) (%1$6g) (%1$6.6g) (%1$06g) (%1$06.3g)\n"
			  "(%1$+g) (%1$-6.3g) (%1$+6.3g) (%1$06g) (%1$+06g) (%1$06.3g)"
			  "\n%{reset}\n",
			  3.1415);

	ft_printf("%{cyan_fg}%{underline}Flag s%{reset}%{cyan_fg}\n\n"
			  "(%1$s) (%1$.5s) (%1$5.s) (%1$5.3s) (%1$5.5s) (%1$5.8s) "
			  "(%1$+s) (%1$0s)\n"
			  "(%2$ls) (%2$.5ls) (%2$5.ls) (%2$5.3ls) (%2$5.5ls) (%2$5.8ls) "
			  "(%2$+ls) (%2$0ls)\n"
			  "(%1$r) (%1$.5r) (%1$5.r) (%1$5.1r) (%1$5.5r) (%1$5.8r) "
			  "(%1$+r) (%1$0r)\n"
			  "(%3$v)\n"
			  "\n%{reset}\n",
			  "fuzz", L"♥♦♣♠", (char []){1, 2, '\n', '\t', 'a', 'b', '\0'});

	/* ft_dprintf(2, fmt, 0.099382, bar); */
	/* ft_asprintf(&s, fmt, 0.099382, bar); */

	/* ft_putstr(s); */
	/* free(s); */
	/* int ret = printf(" this is", 10); */
	/* printf("%d", ret); */
	/* char *bar = ieee_dtoa(0.00899L, 4); */

	/* printf("(%s)", bar); */
	/* free(bar); */
	return 0;
}

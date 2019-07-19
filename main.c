#include <stdio.h>

#include "buffer.h"
#include "ft_printf.h"
#include "libft.h"

#include "bigint.h"

int main(int argc, char *argv[])
{
	/* t_int8 dest[100]; */
	/* t_int64 ret = ft_utf8tostr(dest, 100, */
	/*						   L"@&@{čřžŧ¶'`[łĐŧđĐ¶←^€~[←^ø{&}čž\n", 200); */
	/* (void)printf("ret >> %ld\n\n", ret); */
	/* write(1, dest, ret); */

	/* (void)ft_ftoa(3.1415f, 10); */

	t_bigint *foo;

	ft_dprintf(1, "BEGIN flag0: '%3$ls' flag1: '%1$lc' flag2: '%2$010d' END\n",
			  L'ø', 'A', L"čř");

	ft_putendl("1012224579978655642335");
	foo = bigint_new("1012224579978655642335");
	ft_putbigint(foo);
	bigint_free(&foo);

	/*
	ft_putendl("//////// ");
	char *s_float = ft_ftoa(3.1415, 8);
	free(s_float);
	*/

	/* ft_dprintf(1, "BEGIN flag1: %2$d flag2: %1$d END\n", 11, 10); */

	/* ft_dprintf(1, "string: %2$0 2.8ls  number: %1$#10.4lld	char: %3$12.9lc\n",
	   10, "this", 'a'); */
	/* dprintf(1, "%s  %d  %c\n", "this", 10, 'a'); */
	return 0;
}

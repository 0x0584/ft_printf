#include "buffer.h"
#include "ft_printf.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	ft_dprintf(1, "string: %2$0 2.8ls  number: %1$#10.4lld  char: %3$12.9lc\n",
			   10, "this", 'a');
	/* dprintf(1, "%s  %d  %c\n", "this", 10, 'a'); */
    return 0;
}

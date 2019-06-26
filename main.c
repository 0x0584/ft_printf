#include "buffer.h"
#include "ft_printf.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	ft_dprintf(1, "string: %2$s  number: %1$d  char: %3$c\n", 10, "this", 'a');
	/* dprintf(1, "%s  %d  %c\n", "this", 10, 'a'); */
    return 0;
}

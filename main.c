#include "buffer.h"

int main(int argc, char *argv[])
{
	t_buff *foo = buff_alloc(0x20);
	t_buff *bar;

	buff_append(&foo, "here is one");
	buff_append(&foo, " here is two");
	buff_append(&bar, " coolc \n \n ");
	buff_append(&bar, " here is bar ");

	buff_write(1, foo);
	ft_putendl("\n ----------- ");
	buff_write(1, bar);

	buff_free(&foo);
	buff_free(&bar);

    return 0;
}

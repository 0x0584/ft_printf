#include "ft_printf.h"

int main(int argc, char *argv[])
{
	int ret = ft_printf("(%010d)", 30);
	printf("\n----\n");
	int ret2 = printf("(%010d)", 30);
	printf("\n----\n");
	printf("%d %d", ret, ret2);
    return 0;
}

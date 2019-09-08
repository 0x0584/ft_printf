#include "ft_printf.h"

int main(int argc, char *argv[])
{
	int ret = ft_printf("(%c) (%c)", '\0', '\0');
	printf("\n----\n");
	int ret2 = printf("(%c) (%c)", '\0', '\0');
	printf("\n----\n");
	printf("%d %d", ret, ret2);
    return 0;
}

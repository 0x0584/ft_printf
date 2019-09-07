#include "ft_printf.h"

int		ft_dprintf(const int fd, const char *fmt, ...)
{
	va_list args;
	t_buff	*buff;
	t_list	*lstfrmt;
	int		n_chars;

	lstfrmt = NULL;
	n_chars = 0;
	if (!(buff = buff_alloc(0x20)))
		return (-1);
	va_start(args, fmt);
	format_parse(fmt, &lstfrmt);
	format_populate(&lstfrmt, &args);
	if (!format_to_buff(lstfrmt, buff))
		n_chars = -1;
	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	if (!n_chars)
		n_chars = buff_write(fd, buff);
	buff_free(&buff);
	return (n_chars);
}

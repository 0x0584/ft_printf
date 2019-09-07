#include "ft_printf.h"

int		ft_asprintf(char **astr, const char *fmt, ...)
{
	va_list args;
	t_buff	*buff;
	t_list	*lstfrmt;
	int		n_chars;

	if (!astr)
		return (-1);
	lstfrmt = NULL;
	buff = buff_alloc(0x20);
	va_start(args, fmt);
	format_parse(fmt, &lstfrmt);
	format_populate(&lstfrmt, &args);
	format_to_buff(lstfrmt, buff);
	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	n_chars = buff->len;
	*astr = ft_strdup(buff->base);
	buff_free(&buff);
	return (n_chars);

}

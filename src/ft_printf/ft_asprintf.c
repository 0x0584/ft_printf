#include "ft_printf.h"

int		ft_asprintf(char **astr, const char *fmt, ...)
{
	va_list args;
	t_buff	*buff;
	t_list	*lstfrmt;
	int		n_chars;

	lstfrmt = NULL;
	n_chars  = 0;
	if (!astr || !(buff = buff_alloc(0x20)))
		return (-1);
	va_start(args, fmt);
	format_parse(fmt, &lstfrmt);
	format_populate(&lstfrmt, &args);
	if (!format_to_buff(lstfrmt, buff))
		return (-1);
	ft_lstdel(&lstfrmt, format_free);
	va_end(args);
	if (!n_chars)
	{
		n_chars = buff->len;
		*astr = ft_strdup(buff->base);
	}
	buff_free(&buff);
	return (n_chars);
}

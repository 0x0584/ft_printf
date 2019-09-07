#include "utf8.h"

t_u16		utf8_chlen(t_s32 wch)
{
	if (wch <= 0x7F)
		return (1);
	else if (wch <= 0x7FF)
		return (2);
	else if (wch <= 0XFFFF)
		return (3);
	return (4);
}

size_t		utf8_strsize(wchar_t *s)
{
	size_t len;
	wchar_t *walk;

	len = 0;
	walk = s;
	while (*walk != L'\0')
		len += utf8_chlen(*walk++);
	return (len);
}

size_t		utf8_wstrlen(wchar_t *s)
{
	size_t len;
	wchar_t *walk;

	len = 0;
	walk = s;
	while (walk[len] != L'\0')
		len++;
	return (len);
}

char		*utf8_moveto(wchar_t *s, char *buff, size_t nth_ch)
{
	size_t len;
	size_t walk;

	len = 0;
	walk = 0;
	while (walk < nth_ch)
		len += utf8_chlen(s[walk++]);
	return (buff + len);
}

#ifndef UTF8_H
# define UTF8_H

#include "types.h"

void		utf8_tostr(t_s8 **dest, const wchar_t *wsrc);
t_s16		utf8_tostr_ch(t_s8 *dest, t_s32 wch);

t_u16		utf8_chlen(t_s32 wch);
size_t		utf8_strlen(wchar_t *s);
size_t		utf8_wstrlen(wchar_t *s);
char		*utf8_moveto(wchar_t *s, char *buff, size_t nth_ch);

#endif /* UTF8_H */

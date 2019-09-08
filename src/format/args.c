#include "format.h"

bool	get_signed_args(t_frmt *frmt, va_list *arglst)
{
	if (!frmt || !arglst)
		return false;
	else if (!(frmt->conv == CONV_INT || frmt->conv == CONV_CHAR))
		return false;
	if (frmt->length == MOD_LL)
		frmt->data.ll = va_arg(*arglst, long long);
	else if (frmt->length == MOD_L)
		frmt->data.l = va_arg(*arglst, long);
	else if (frmt->length == MOD_Z)
		frmt->data.sz = va_arg(*arglst, ssize_t);
	else if (frmt->length == MOD_J)
		frmt->data.j = va_arg(*arglst, intmax_t);
	else
		frmt->data.i = va_arg(*arglst, int);
	return (true);
}

bool	get_unsigned_args(t_frmt *frmt, va_list *arglst)
{
	if (!frmt || !arglst)
		return false;
	if (!(frmt->conv == CONV_UOCT || frmt->conv == CONV_UDEC
			|| frmt->conv == CONV_UBIN || frmt->conv == CONV_UHEX
			|| frmt->conv == CONV_PTR))
		return (false);
	if (frmt->length == MOD_L || frmt->conv == CONV_PTR)
		frmt->data.ul = va_arg(*arglst, unsigned long);
	else if (frmt->length == MOD_LL)
		frmt->data.ull = va_arg(*arglst, unsigned long long);
	else if (frmt->length == MOD_Z)
		frmt->data.sz = va_arg(*arglst, size_t);
	else if (frmt->length == MOD_J)
		frmt->data.j = va_arg(*arglst, uintmax_t);
	else
		frmt->data.ui = va_arg(*arglst, unsigned int);
	return (true);
}

bool	get_floating_point_args(t_frmt *frmt, va_list *arglst)
{
	if (!frmt || !arglst)
		return false;

	if (!(frmt->conv == CONV_DBL || frmt->conv == CONV_LDBL
			|| frmt->conv == CONV_GDBL || frmt->conv == CONV_EDBL
			|| frmt->conv == CONV_HDBL))
		return false;
	if (frmt->length == MOD_L_CAP)
		frmt->data.ld = va_arg(*arglst, long double);
	else
		frmt->data.d = va_arg(*arglst, double);
	return (true);
}

bool	get_string_args(t_frmt *frmt, va_list *arglst)
{
	if (!frmt || !arglst || frmt->conv != CONV_STR)
		return (false);
	if (frmt->length == MOD_L)
		frmt->data.wstr = va_arg(*arglst, wchar_t *);
	else
		frmt->data.str = va_arg(*arglst, char *);
	return (true);
}

void	set_arg_index(char **fmt, t_frmt *frmt)
{
	char *tmp;

	tmp = *fmt;
	frmt->iarg = hungry_getnbr(fmt);
	if (*fmt[0] == '$')
		*fmt += 1;
	else
	{
		*fmt = tmp;
		frmt->iarg = 0;
	}
}

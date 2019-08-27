#include "format.h"
#include "float.h"

static char		*ldbl_as_hex(t_float128 ld)
{
	(void)ld;
	return NULL;
}

static char		*dbl_as_hex(t_float64 dbl)
{
	char *result;
	char *tmp;

	result = NULL;
	tmp = ft_itoa(dbl.ieee.e - F64BIT_BAIS);
	if (*tmp != '-')
		ft_strinsert_at(&tmp, "+", 0);
	ft_strinsert_at(&tmp, "p", 1);
	result = tmp;
	tmp = ft_uitoa_base(dbl.ieee.m | 0x10000000000000, HEX);
	ft_strinsert_at(&tmp, ".", 1 + (*tmp == '-'));
	if (tmp[ft_strlen(tmp) - 1] == '.')
		ft_strinsert_at(&tmp, "0", ft_strlen(tmp));
	ft_strinsert_at(&result, tmp, 0);
	ft_strinsert_at(&result, "0x", 0);
	if (dbl.ieee.s)
		ft_strinsert_at(&result, "-", 0);
	ft_strdel(&tmp);
	return (result);
}

static char		*dbl_as_exp(char *dbl)
{
	char	*result;
	int		i;
	int		exp;

	i = 0;
	result = NULL;

	/* This means that we have something like 0.xxxx */
	if ((exp = ft_strichr(dbl, '.')) == 1)
		while (dbl[i + 2] == 0)
			i++;
	exp = (exp == 1 && dbl[i + 2] ? -(i + (*dbl == '0')) : exp - 1);
	result = ft_itoa(exp);
	if (ft_strlen(result) < 3 && *result == '-')
		ft_strinsert_at(&result, "0", 1);
	else if (*result != '-')
		ft_strinsert_at(&result, ft_strlen(result) == 1 ? "+0" : "+", 0);
	ft_strinsert_at(&result, "e", 0);
	ft_strinsert_at(&result, dbl, 0);
	ft_strreplace(&result, ".", "");
	ft_strctrim(&result, '0', true);
	ft_strinsert_at(&result, ".", 1);
	return (result);
}

static char		*handle_std_double(t_frmt *frmt)
{
	char	*buff;
	char	*result;
	t_float64 d;
	t_float128 ld;

	result = NULL;
	/* TODO: hexa does not need duble as string, so this must change! */
	buff = (frmt->length == MODIF_L ?
			ft_ldtoa(frmt->u_data.ld) : ft_dtoa(frmt->u_data.d));
	if (frmt->conv == DOUBLE_EXP || frmt->conv == DOUBLE_EXP2)
	    result = dbl_as_exp(buff);
	else if (frmt->conv == DOUBLE_HEXA || frmt->conv == DOUBLE_HEXA2)
	{
		if (frmt->length == MODIF_L)
			ld.ld = frmt->u_data.ld;
		else
			d.d = frmt->u_data.d;
		result = (frmt->length == MODIF_L ? ldbl_as_hex(ld) : dbl_as_hex(d));
	}
	if (!result)
		return (buff);
	ft_strdel(&buff);
	return (result);
}

static char		*handle_g_double(t_frmt *frmt)
{
	char *buff;

	buff = NULL;
	(void)frmt;
	return (buff);
}

/* FIXME: implement this (or this might already be implemented) */

char			*handle_double(t_frmt *frmt)
{
	char *result;

	result = NULL;
	if (frmt->conv == DOUBLE_G || frmt->conv == DOUBLE_G2)
		result = handle_g_double(frmt);
	else
		result = handle_std_double(frmt);
	if(frmt->conv == DOUBLE_EXP2 || frmt->conv == DOUBLE_HEXA2
	   || frmt->conv == DOUBLE_G2 || frmt->conv == DOUBLE_NORMAL2)
		ft_strtoupper(&result);
	return (result);
}

#include "format.h"

/* TODO: check the type if e or f or a or g */

static char		*double_as_exp(char *dbl)
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
	ft_strctrim(&result, '0');
	ft_strinsert_at(&result, ".", 1);
	return (result);
}

static char		*double_as_hex(char *dbl)
{
	(void)dbl;
	return NULL;
}

static char		*handle_std_double(t_frmt *frmt)
{
	char	*buff;
	char	*result;

	result = NULL;
	buff = (frmt->length == MODIF_L ?
			ft_ldtoa(frmt->u_data.ld) : ft_dtoa(frmt->u_data.d));
	ft_putendl(buff);
	(void)getchar();
	if (frmt->conv == DOUBLE_EXP || frmt->conv == DOUBLE_EXP2)
	    result = double_as_exp(buff);
	else if (frmt->conv == DOUBLE_HEXA || frmt->conv == DOUBLE_HEXA2)
		result = double_as_hex(buff);
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

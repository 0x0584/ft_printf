/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tostr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:59:08 by archid-           #+#    #+#             */
/*   Updated: 2019/09/28 19:14:38 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "format.h"
#include "ieeefp.h"
#include "dragon4.h"

static t_ieeesp		ieee_is_spval(t_ieeefp *fp)
{
	if (fp->type == IEEE_FLOAT)
	{
		if (fp->as.d.ieee.e == 0x7F && fp->as.d.ieee.m)
			return (IEEE_NOT_A_NUMBER);
		else if (fp->as.d.ieee.e == 0x7F)
			return (!fp->as.d.ieee.s ? IEEE_INFINI_P : IEEE_INFINI_N);
	}
	else if (fp->type == IEEE_DOUBLE)
	{
		if (fp->as.d.ieee.e == 0x7FF && fp->as.d.ieee.m)
			return (IEEE_NOT_A_NUMBER);
		else if (fp->as.d.ieee.e == 0x7FF)
			return (!fp->as.d.ieee.s ? IEEE_INFINI_P : IEEE_INFINI_N);
	}
	else if (fp->type == IEEE_LONG_DOUBLE)
	{
		if (fp->as.d.ieee.e == 0x7FFF && fp->as.d.ieee.m)
			return (IEEE_NOT_A_NUMBER);
		else if (fp->as.d.ieee.e == 0x7FFF)
			return (!fp->as.d.ieee.s ? IEEE_INFINI_P : IEEE_INFINI_N);
	}
	return (IEEE_NA);
}

char				*ieee_sp_as_str(t_ieeefp *fp, t_frmt *frmt)
{
	char		*s;
	bool		is_sp;
	t_ieeesp	sp;

	if (!(sp = ieee_is_spval(fp)))
		return (NULL);
	s = NULL;
	is_sp = false;
	if ((is_sp = (sp == IEEE_INFINI_P || sp == IEEE_INFINI_N)))
		s = ft_strdup(frmt->is_upcase ? "INF" : "inf");
	else if ((is_sp = sp == IEEE_NOT_A_NUMBER))
		s = ft_strdup(frmt->is_upcase ? "NAN" : "nan");
	if (is_sp)
	{
		if (sp == IEEE_NOT_A_NUMBER)
			frmt->flags &= ~(FLAG(FL_SPACE) | FLAG(FL_PLUS));
		frmt->flags &= ~FLAG(FL_ZERO);
	}
	return (s);
}

char				*ieee_tostr(t_ieeefp *fp, t_ieee_fmt style, t_frmt *frmt)
{
	char	*buff;
	t_s32	exp2;

	exp2 = dragon4(fp, &buff);
	if (style == IEEE_SUITABLE)
	{
		style = (exp2 < (t_s32)frmt->prec && exp2 >= -4)
					? IEEE_NORMAL : IEEE_EXPONENT;
		frmt->prec -= (1 + (style == IEEE_NORMAL) * exp2);
	}
	dragon4_prec(&buff, &exp2, style, frmt->prec);
	if (ieee_get_sign(fp))
		ft_strinsert_at(&buff, "-", 0);
	if (HAS_FLAG(frmt, FL_HASH) && !ft_strchr(buff, '.'))
		ft_strappend(&buff, ".");
	if (style == IEEE_EXPONENT)
		ieee_sci_style(&buff, exp2, frmt->is_upcase);
	return (buff);
}

char				*ieee_hex_style(t_ieeefp *fp, t_u32 prec, bool upcase)
{
	char	*result;
	char	*tmp;
	t_u128	man;
	t_s32	exp;

	ieee_extract_hex_parts(fp, &man, &exp);
	tmp = ft_itoa_base((t_s32)exp, BASE_DEC);
	if (*tmp != '-')
		ft_strinsert_at(&tmp, "+", 0);
	ft_strinsert_at(&tmp, upcase ? "P" : "p", 0);
	result = tmp;
	tmp = ft_utoa_base((t_u128)man, upcase ? BASE_UHEX : BASE_LHEX);
	if (prec && ft_strlen(tmp) > prec)
		ft_strchange(&tmp, ft_strrdup(tmp, tmp + prec));
	else if (prec && ft_strlen(tmp) < prec)
		ft_strpad(&tmp, '0', prec - ft_strlen(tmp) + 1, TOWARD_TAIL);
	ft_strinsert_at(&tmp, ".", 1);
	if (*tmp && tmp[ft_strlen(tmp) - 1] == '.')
		ft_strappend(&tmp, "0");
	ft_strinsert_at(&result, tmp, 0);
	ft_strinsert_at(&result, upcase ? "0X" : "0x", 0);
	if (ieee_get_sign(fp))
		ft_strinsert_at(&result, "-", 0);
	free(tmp);
	return (result);
}

void				ieee_sci_style(char **astr, t_s32 exp, bool upcase)
{
	char	*fp_sci;

	if (!SAFE_PTRVAL(astr))
		return ;
	fp_sci = ft_itoa_base(exp, BASE_DEC);
	if (*fp_sci == '-' && ft_strlen(fp_sci) < 3)
		ft_strinsert_at(&fp_sci, "0", 1);
	else if (*fp_sci != '-')
		ft_strinsert_at(&fp_sci, ft_strlen(fp_sci) < 2 ? "+0" : "+", 0);
	ft_strinsert_at(&fp_sci, upcase ? "E" : "e", 0);
	ft_strinsert_at(&fp_sci, *astr, 0);
	ft_strdel(astr);
	*astr = fp_sci;
}

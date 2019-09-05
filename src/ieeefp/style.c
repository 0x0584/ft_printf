#include "ieeefp.h"
#include "libft.h"

void	ieee_sci_style(char **astr, t_s32 exp, bool upcase)
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
	*astr = ft_strdup(fp_sci);
}

char	*ieee_hex_style(t_ieeefp *fp, t_u32 prec, bool upcase)
{
	char *result;
	char *tmp;
	t_u128 man;
	t_s32 exp;

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

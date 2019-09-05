#include "format.h"

char	*ieee_sp_as_str(t_ieeesp sp, t_frmt *frmt)
{
	char *s;
	bool is_sp;

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

t_ieeesp ieee_is_spval(t_ieeefp *fp)
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

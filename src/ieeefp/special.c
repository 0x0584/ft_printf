#include "format.h"
#include "ieeefp.h"

t_ieeesp is_special_value(t_ieeefp fp, t_ieeetype type)
{
	if (type == IEEE_FLOAT)
	{
		if (fp.d.ieee.e == 0x7F && fp.d.ieee.m)
			return (IEEE_NOT_A_NUMBER);
		else if (fp.d.ieee.e == 0x7F)
			return (!fp.d.ieee.s ? IEEE_INFINI_P : IEEE_INFINI_N);
	}
	else if (type == IEEE_DOUBLE)
	{
		if (fp.d.ieee.e == 0x7FF && fp.d.ieee.m)
			return (IEEE_NOT_A_NUMBER);
		else if (fp.d.ieee.e == 0x7FF)
			return (!fp.d.ieee.s ? IEEE_INFINI_P : IEEE_INFINI_N);
	}
	else if (type == IEEE_LONG_DOUBLE)
	{
		if (fp.d.ieee.e == 0x7FFF && fp.d.ieee.m)
			return (IEEE_NOT_A_NUMBER);
		else if (fp.d.ieee.e == 0x7FFF)
			return (!fp.d.ieee.s ? IEEE_INFINI_P : IEEE_INFINI_N);
	}
	return (IEEE_NA);
}

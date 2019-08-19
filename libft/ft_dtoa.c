/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_dtoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/07/25 19:48:43 by archid-		   #+#	  #+#			  */
/*	 Updated: 2019/07/26 21:51:20 by archid-		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

#define EXP_DBL(d)		(d.ieee.e - F64BIT_BAIS)

static void		split_double(t_float64 dbl, char **int_part, char **frac_part)
{
	char *buff;

	buff = ft_uitoa_base(dbl.ieee.m, BIN);
	ft_strpad(&buff, '0', 53 - ft_strlen(buff), true);
	if (EXP_DBL(dbl) >= 0 && EXP_DBL(dbl) < 52)
	{
		ft_strinsert_at(&buff, ".", EXP_DBL(dbl) + 1);
		ft_strctrim(&buff, '0', false);
		*int_part = ft_strchr(buff, '.') + 1;
		*frac_part = ft_strdup((*int_part)[0] ? *int_part : "0");
		*int_part = ft_strrdup(buff, *int_part - 2);
	}
	else if (EXP_DBL(dbl) < 0)
	{
		*int_part = ft_strdup("0");
		ft_strpad(&buff, '0', -(EXP_DBL(dbl) + 1), true);
		ft_strctrim(&buff, '0', false);
		*frac_part = ft_strdup(*buff ? buff : "0");
	}
	else
	{
		ft_strctrim(&buff, '0', false);
		*int_part = ft_strdup(buff);
		*frac_part = ft_strdup("0");
	}
	ft_strdel(&buff);
}

char			*ft_dtoa(double d)
{
	t_float64		dbl;
	char			*int_part;
	char			*frac_part;
	char			*buff;

	dbl.d = d;
	ASSERT_RET(!dbl.ieee.m && !dbl.ieee.e, ft_strdup(dbl.ieee.s ?
														"-0.0" : "0.0"));
	ASSERT_RET(dbl.ieee.e == 0x7FF, dbl.ieee.m ? ft_strdup("nan") :
									ft_strdup(dbl.ieee.s ? "-inf" : "inf"));
	if (EXP_DBL(dbl) != -F64BIT_BAIS)
		dbl.ieee.m |= 0x10000000000000;
	else
		dbl.ieee.e += 1;
	split_double(dbl, &int_part, &frac_part);
	buff = NULL;
	return (buff);
}

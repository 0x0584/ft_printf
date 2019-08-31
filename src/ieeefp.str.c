/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:34:48 by archid-           #+#    #+#             */
/*   Updated: 2019/08/06 14:38:58 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ldtoa(long double ld)
{
	(void)ld;

	return (NULL);
}
/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_ftoa.c											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/30 02:45:42 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/07/26 16:32:12 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "float.h"

/*
   TODO: Finish ftoa()

   IDEA:
   ~~~~~

   1. compute $2^{exp - BAIS}$

   2. compute the fraction form the mantissa as the following:

		- mantissa is in the following form 1.mantissa_in_binary
		so each time we should $\Sigma{bit \times 1/2^{i}}$, which would
		give us a fraction.

		- the question is how to get the integer part? well,
		we multiply by $10^{i}$. Thus $\Sigma{bit \times 5^{i}}$

   3. test on the sign of $exp - BAIS$.

		- Fraction Part: if positive, skip $exp - BAIS$ digits from mantissa's
		front. otherwise if negative \textit{pad $exp - BAIS$ zero's but with
		a one first} -- since the number written as is $2^{exp - BAIS} \times
		1.mantissa$.

		- Integer Part: based on what we had done, take whatever on the left!

   4. Let $i$ be the Integer Part of a floating point number $u$, and $f$ it's
		fractional part. compute $i \times 2^{exp - BAIS}$ and $f \times
		2^{exp - BAIS}$.
*/

char	*ft_ftoa(float f)
{
	(void)f;
	return (NULL);
}
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
#include "ieeefp.h"

char	*ft_dtoa(double d)
{
	char		*buff;
	t_int32		exp;
	t_ieeefp	fp;

	buff = ft_strnew(DRAGON4_BUFF_SIZE);
	fp.d.d = d;
	exp = dragon4(fp, IEEE_DOUBLE, buff, DRAGON4_BUFF_SIZE);
	ft_putendl("----");
	handle_precision(&buff, IEEE_NORMAL, exp, 6);
	return (buff);
}

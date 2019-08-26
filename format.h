/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.h											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/17 22:16:27 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/08/06 15:51:27 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#ifndef FORMAT_H
# define FORMAT_H

# include "libft.h"
# include "buffer.h"

/* XXX: add enums and union into format structure */
/* FIXME: create a flags enum, add mask... */

/* the general rule of a format string:
 *
 *	%{{arg-index}{$}}{0(blank)#-+'}{min-width}.{precision}{len-modi}{type}
 */
/* FIXME: add priorities */
typedef struct	s_format
{
	/*
	** Indexes to sort a list of t_frmt based on
	*/
	int								argindex;
	int								fmtindex;

	int								width;
	int								precision;
	bool							is_alter;
	bool							prefix_zeros;
	bool							prefix_signe;
	bool							prefix_plus_blank;
	bool							padding_on_left;

	enum		e_modifiers
	{
		MODIF_HH, MODIF_H,
		MODIF_L, MODIF_LL,

		MODIF_DEFAULT = -1
	}								length;

	enum		e_conversions
	{
		SIGNED_DECI,

		U_OCTA, U_DECI, U_HEXA, U_HEXA2,

		DBL_EXP, DBL_EXP2,
		DBL_NRML, DBL_NRML2,
		DBL_G, DBL_G2,
		DBL_HEXA, DBL_HEXA2,

		CHAR, STRING, POINTER, PERCENTAGE,

		STRING_FRMT = -2,
		DEFAULT_CONV
	}								conv;

	/* NOTE:
	 *
	 * i'm not sure about all the type conversion the man in not clean
	 * about those (or it might be just me) * so i've putted here any
	 * possible data type
	 */

	union		u_data
	{
		unsigned char		c;
		short				s;
		int					i;
		long				l;
		long long			ll;
		unsigned short		us;
		unsigned char		uc;
		unsigned int		ui;
		unsigned long		ul;
		unsigned long long	ull;
		double				d;
		long double			ld;
		char				*str;
		t_int32				*wstr;
		t_int32				wc;
		unsigned char		*ustr;
	}								u_data;
}				t_frmt;

void			handle_format(char **fmt, t_plist *alstfrmt, int *index);
int				handle_relative_args(va_list *arglst, t_plist *alstfrmt);
void			format_free(void *dat, size_t size);
t_frmt			*format_const_string(int index, char *str);

/*
** format.checks.c: verify conversion and modifiers. also flags
*/
int				check_conversion(char **fmt, t_frmt *frmt);
int				check_modifier(char **fmt, t_frmt *frmt);
int				check_flags(char **fmt, t_frmt *frmt);

/*
** format.buffer.c: fill a buffer from a list of t_frmt
*/

void			format_to_buff(t_list *lstfrmt, t_buff *buff);
void			format_dbg(t_frmt *frmt);
bool			format_isnumeric(t_frmt *frmt);
bool			format_isfloat(t_frmt *frmt);
char			format_getsign(t_frmt *frmt);
char			*format_ieee_float(t_frmt *frmt);

/*
** format.handler.c
*/

char			*handle_unsigned_deci(t_frmt *frmt, const char *base);
char			*handle_signed_deci(t_frmt *frmt);
char			*handle_double(t_frmt *frmt);
char			*handle_char(t_frmt *frmt);
char			*handle_string(t_frmt *frmt);

#endif

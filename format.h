/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 format.h											:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: archid- <archid-@student.1337.ma>			+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2019/06/17 22:16:27 by archid-		   #+#	  #+#			  */
/*   Updated: 2019/07/27 10:09:39 by archid-          ###   ########.fr       */
/*																			  */
/* ************************************************************************** */

#ifndef FORMAT_H
# define FORMAT_H

# include "libft.h"
# include "buffer.h"

# define IS_LITERAL(fmt)		(fmt.type == '%')
# define IS_INT(fmt)			(fmt.type == 'd' || fmt.type == 'i')
# define IS_UINT(fmt)			(fmt.type == 'u')
# define IS_CHAR(fmt)			(fmt.type == 'c')
# define IS_STRING(fmt)			(fmt.type == 's')
# define IS_DOUBLE(fmt)			(fmt.type == 'f' || fmt.type == 'F')
# define IS_DOUBLE_E(fmt)		(fmt.type == 'e' || fmt.type == 'E')
# define IS_DOUBLE_G(fmt)		(fmt.type == 'g' || fmt.type == 'G')
# define IS_DOUBLE_A(fmt)		(fmt.type == 'a' || fmt.type == 'A')
# define IS_HEXA(fmt)			(fmt.type == 'x' || fmt.type == 'X')
# define IS_OCTAL(fmt)			(fmt.type == 'o')
# define IS_POINTER(fmt)		(fmt.type == 'p')

/* FIXME: add enums and union into format structure */
/* TODO: create a flags enum, add mask... */

/* the general rule of a format string:
 *
 *	%{{arg-index}{$}}{0(blank)#-+'}{min-width}.{precision}{len-modi}{type}
 */
/* FIXME: add priorities */
typedef struct	s_format
{
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
		UNSIGNED_OCTA,
		UNSIGNED_DECI,
		UNSIGNED_HEXA,
		UNSIGNED_HEXA2,
		DOUBLE_EXP,
		DOUBLE_EXP2,
		DOUBLE_NORMAL,
		DOUBLE_NORMAL2,
		DOUBLE_G,
		DOUBLE_G2,
		DOUBLE_HEXA,
		DOUBLE_HEXA2,
		CHAR,
		STRING,
		POINTER,
		PERCENTAGE,

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
bool			format_getsign(t_frmt *frmt);
char			*format_ieee_float(t_frmt *frmt);

char			*handle_double(t_frmt *frmt);

#endif

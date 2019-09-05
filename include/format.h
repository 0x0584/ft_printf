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
# include "ieeefp.h"

# define FLAG(fl)					(1U << fl)
# define IS_FLAG(val, fl)			((val & FLAG(fl)) != 0)
# define HAS_FLAG(frmt, fl)			(IS_FLAG(frmt->flags, fl))

typedef enum	e_flags
{
	FL_NA,

	FL_ZERO, FL_SPACE, FL_MINUS, FL_PLUS, FL_HASH
}				t_flags;


/* XXX: add enums and union into format structure */
/*
   XXX: create a flags enum, add mask...
   just create enums and move on. you're trying to
   implement many things at one.
*/

/* the general rule of a format string:
 *
 *	%{{arg-index}{$}}{0(blank)#-+'}{min-width}.{precision}{len-modi}{type}
 */

/*
   XXX: add priorities
   never ask anybody not listen to anyone!
*/

typedef enum	e_length_modifiers
{
	MOD_HH, MOD_H,
	MOD_L, MOD_LL, MOD_L_CAP,
	MOD_Z, MOD_J,

	MOD_NA = -1
}				t_modif;

typedef	enum	e_conversions
{
	CONV_INT, CONV_UBIN, CONV_UOCT, CONV_UDEC, CONV_UHEX,
	CONV_DBL, CONV_LDBL, CONV_GDBL, CONV_EDBL, CONV_HDBL,
	CONV_CHAR, CONV_STR, CONV_PTR,

	CONV_FRMT = -2, CONV_NA
}				t_conv;


/* NOTE:
 *
 * i'm not sure about all the type conversion the man in not clean
 * about those (or it might be just me) * so i've putted here any
 * possible data type
 */

typedef union	u_data
{
	short				s;
	int					i;
	long				l;
	long long			ll;

	unsigned char		c;
	unsigned short		us;
	unsigned char		uc;
	unsigned int		ui;
	unsigned long		ul;
	unsigned long long	ull;
	double				d;
	long double			ld;
	char				*str;
	t_s32				*wstr;
	t_s32				wc;
	unsigned char		*ustr;

	void			    *p;
	intmax_t j;
	uintmax_t jj;

}				t_data;

typedef struct	s_format
{
	int		        iarg;
	int		    	ifrmt;

	t_flags	    	flags;
	t_modif	    	length;
	t_conv	    	conv;
	bool	    	is_upcase;	  /* set when a conversion is uppercase */

	t_data	    	data;
	t_u32    	width;
	t_u32	   	prec;
	bool			has_radix;
}				t_frmt;

void			format_handle(char **fmt, t_plist *alstfrmt, int *index);
int				format_populate(t_plist *alstfrmt, va_list *arglst);
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
**
*/

char			*format_handle_conversion(t_frmt *frmt);

char			*handle_unsigned_deci(t_frmt *frmt, const char *base);
char			*handle_signed_deci(t_frmt *frmt);
char			*handle_floating_point(t_frmt *frmt);
char			*handle_char(t_frmt *frmt);
char			*handle_string(t_frmt *frmt);

bool			flag_alterform(t_frmt *frmt, char **astr, size_t *pad);
void			flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad);

void			adjust_prefix(t_frmt *frmt, char **astr, size_t *pad);
void			adjust_padding(t_frmt *frmt, char **astr, size_t *pad);
void			adjust_precision(t_frmt *frmt, char **astr, size_t *pad);

char			*ieee_sp_as_str(t_ieeesp sp, t_frmt *frmt);
char			*ieee_tostr(t_ieeefp *fp, t_ieee_fmt style, t_frmt *frmt);

#endif

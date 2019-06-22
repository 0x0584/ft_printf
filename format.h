/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:16:27 by archid-           #+#    #+#             */
/*   Updated: 2019/06/22 17:21:27 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_H
# define FORMAT_H

# include "libft/libft.h"
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

enum e_modifiers
{
	MODIF_HH, MODIF_H,
	MODIF_L, MODIF_LL,
	MODIF_J, MODIF_T, MODIF_Z,

	MODIF_DEFAULT = -1
};

enum e_conversions {
	SIGNED_DECI,
	UNSIGNED_OCTA,
	UNSIGNED_DECI,
	UNSIGNED_HEXA,
	UNSIGNED_HEXA2,
	DOUBLE_EXP,
	DOUBLE_EXP2,
	DOUBLE_NORMAL,
	DOUBLE_NORMAL2,
	CHAR,
	STRING,
	POINTER,
	PERCENTAGE,

	DEFAULT_CONV = -1
};

/* the general rule of a format string:
 *
 *  %{{arg-index}{$}}{0(blank)#-+'}{min-width}.{precision}{len-modi}{type}
 */
typedef struct	s_format
{
	char	type;				/* %d or %s .... */

	union u_data {
		long long int i;
		long double d;
		char *s;
		char c;
		void *p;
	} u;
	enum	e_modifiers length;
	enum	e_conversions conv;

	int		argindex;			/* n$ would give us which argument to
								 * access at point. default is -1
								 */
	int		fmtindex;			/* this is the order as they appeared in the
								 * format string. */
	int		width;				/* this is the field's minimum width. in
								 * a case where the value (as string) is
								 * left that this width. it if filled with
								 * blanks on the left.
								 */
	bool	is_alter;			/* this is the flag #, which is
								 * alternate form.
								 *  - no effect for %{c,d,i,n,p,s,u}
								 *  - prefix a 0 for %o
								 *    default is not
								 *  - prefix 0{x,X} for %{x,X}
								 *    default is not
								 *  - keep decimal point for %{a,A,e,E,f,F,g,G}
								 *    default is only if a digit follows
								 *  - keep trailing zeros for %{g,G}.
								 *    default is not
								 */
	bool	prefix_zeros;		/* this is the 0 flag. padding on the left with
								 * zeros: 00013
								 *  default padding: blanks
								 *  annulated by precision for %{d,i,o,u,x,X}
								 */
	bool	prefix_signe;		/* +10 */
	bool	prefix_plus_blank;	/* _10 where _ is the blank */
	bool	padding_on_left;			/* this is the - flag,
								 *  annulates the 0 flag. */
	bool	is_dot;				/* this is the . flag. which is the precision
								 *  annulates the zeros-padding */
	int precision;				/* .precision */
}				t_frmt;

void	handle_format(char **fmt, va_list *arglst, t_buff *buff);
t_frmt	parse_conversion(char **fmt);

void	set_alterform(t_frmt fmt, t_buff *buff);


#endif

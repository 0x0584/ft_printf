/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:16:27 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 02:46:31 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_H
# define FORMAT_H

# include "libft.h"
# include "buffer.h"
# include "ieeefp.h"
# include "colors.h"

# define FLAG(fl)					(1U << fl)
# define IS_FLAG(val, fl)			((val & FLAG(fl)) != 0)
# define HAS_FLAG(frmt, fl)			(IS_FLAG(frmt->flags, fl))

# define IS_PREFIX_SIGN(c)			(c == '+' || c == '-' || c == ' ')

# define LONG_TYPES					"DOUSC"
# define UPPER_TYPES				"XFEAGB"

# define LEN_DIFF(s1, s2)			(s2 ? (size_t)(s2 - s1 - 1) : ft_strlen(s1))

typedef enum	e_flags
{
	FL_NA,

	FL_ZERO, FL_SPACE,
	FL_MINUS, FL_PLUS,
	FL_HASH
}				t_flags;

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
	CONV_CHAR, CONV_STR, CONV_PTR, CONV_COLOR, CONV_PERC,

	CONV_FRMT = -2, CONV_NA
}				t_conv;

typedef union	u_data
{
	t_s8			c;
	t_s16			s;
	t_s32			i;
	t_s64			l;
	t_s128			ll;
	ssize_t			sz;
	intmax_t		j;

	t_u8			uc;
	t_u16			us;
	t_u32			ui;
	t_u64			ul;
	t_u128			ull;
	size_t			usz;
	uintmax_t		uj;

	double			d;
	long double		ld;

	char			*str;
	wchar_t			*wstr;
	wchar_t			wc;
}				t_data;

typedef struct	s_format
{
	t_data			data;
	int				iarg;
	int				ifrmt;

	t_flags			flags;
	t_modif			length;
	t_conv			conv;
	bool			is_upcase;
	bool			is_nulchr;
	bool			reverse_string;
	bool			non_printable;

	t_u32			width;
	bool			width_as_arg;

	bool			has_radix;
	t_u32			prec;
	bool			prec_as_arg;
}				t_frmt;

void			format_parse(const char *fmt, t_list **alst);
void			format_doparse(char **fmt, t_plist *alst, int *index);
bool			format_apply_color(char **fmt, t_list **alst, int *index);
bool			format_percentage(char **fmt, t_list **alst, int *index);
int				format_populate(t_plist *alst, va_list *arglst);
int				format_to_buff(t_list *lstfrmt, t_buff *buff);
void			format_free(void *dat, size_t size);
t_frmt			*format_const_string(int index, char *str);

bool			get_signed_args(t_frmt *frmt, va_list *arglst);
bool			get_unsigned_args(t_frmt *frmt, va_list *arglst);
bool			get_floating_point_args(t_frmt *frmt, va_list *arglst);
bool			get_string_args(t_frmt *frmt, va_list *arglst);

int				check_conversion(char **fmt, t_frmt *frmt);
int				check_modifier(char **fmt, t_frmt *frmt);
int				check_flags(char **fmt, t_frmt *frmt);

void			format_dbg(t_frmt *frmt);
bool			format_isnumeric(t_frmt *frmt);
bool			format_isfloat(t_frmt *frmt);
char			format_getsign(t_frmt *frmt);
char			*format_ieee_float(t_frmt *frmt);

char			*format_handle_conversion(t_frmt *frmt);
char			*handle_unsigned_deci(t_frmt *frmt, const char *base);
char			*handle_signed_deci(t_frmt *frmt);
char			*handle_floating_point(t_frmt *frmt);
char			*handle_char(t_frmt *frmt);
char			*handle_string(t_frmt *frmt);

bool			flag_alterform(t_frmt *frmt, char **astr, size_t *pad);
void			flag_zero_padding(t_frmt *frmt, char **astr, size_t *pad);

void			adjustments(t_frmt *frmt, char **astr, size_t *pad);
void			adjust_prefix(t_frmt *frmt, char **astr, size_t *pad);
void			adjust_padding(t_frmt *frmt, char **astr, size_t *pad);
bool			adjust_base_prefix(char **astr, t_frmt *frmt,
									bool replace, bool insert);

char			*ieee_sp_as_str(t_ieeefp *fp, t_frmt *frmt);
char			*ieee_tostr(t_ieeefp *fp, t_ieee_fmt style, t_frmt *frmt);
void			ieee_set_fp(t_ieeefp *fp, t_frmt *frmt);

void			set_arg_index(char **fmt, t_frmt *frmt);
void			set_precision(char **fmt, t_frmt *frmt);
void			set_width(char **fmt, t_frmt *frmt);
void			get_wild_args(t_frmt *frmt, va_list *alst);

size_t			format_init_padding(t_frmt *frmt, char const *str);

#endif

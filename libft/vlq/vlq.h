#ifndef VLQ_H
# define VLQ_H

#include "../libft.h"

/*
 * variable length quantity
 */

# define MSB						0x8000000000000000
# define N_MSB						0x7FFFFFFFFFFFFFFF

# define GET_MSB(u)					(u >> 63)
# define GET_N_MSB(u)				(u & N_MSB)
# define GET_NUMBER(v, i)			(i >= 0 ? v->base[i] & N_MSB: 0)

/*
 * the base is an array cunstructed as the following
 *
 * the number is represented an array of t_uint64 elems, where suppose we have
 * N elements, all the N - 1 elements have MSB set to 1, except for the last
 * which has 0.
 */

typedef struct	s_variable_length_quantity
{
	bool			sign;
	t_uint64		*base;
}				t_vlq;

/* FIXME: handle negative values. For the momen, only positive
 * numbers are handled*/

/* Main functions */

t_vlq			*vlq_new(t_uint32 size, bool sign);
t_vlq			*vlq_new_base(char *num, char *base);
char			*vla_tostr(t_vlq *vlq, char *base);
void			vlq_free(t_vlq **avlq);
char			*vlq_base(t_vlq *vlq, char *base);
long			vlq_cmp(t_vlq *u, t_vlq *v);
t_uint32		vlq_len(t_vlq *vlq);
void			vlq_trim(t_vlq **avlq);

/* Operations */

t_vlq			*vlq_add(t_vlq *u, t_vlq *v);
t_vlq			*vlq_mul(t_vlq *u, t_vlq *v);
t_vlq			*vlq_sub(t_vlq *u, t_vlq *v);
t_vlq			*vlq_div(t_vlq *u, t_vlq *v);
t_vlq			*vlq_mod(t_vlq *u, t_vlq *v);
t_vlq			*vlq_pow(t_vlq *vlq, t_vlq *exp);
t_vlq			*vlq_bls(t_vlq *vlq, t_uint32 shift);
t_vlq			*vlq_brs(t_vlq *vlq, t_uint32 shift);

void			vlq_add_acc(t_vlq **au, t_vlq *v);
void			vlq_sub_acc(t_vlq **au, t_vlq *v);
void			vlq_mul_acc(t_vlq **au, t_vlq *v);
void			vlq_div_acc(t_vlq **au, t_vlq *v);
void			vlq_mod_acc(t_vlq **au, t_vlq *v);
void			vlq_pow_acc(t_vlq **avlq, t_vlq *exp);
void			vlq_bls_acc(t_vlq **avlq, t_uint32 shift);
void			vlq_brs_acc(t_vlq **avlq, t_uint32 shift);

#endif

#ifndef DRAGON4_H
# define DRAGON4_H

#include "libft.h"
#include "ieeefp.h"

# define DRAGON4_BUFF_SIZE					52

t_s32				dragon4(t_ieeefp *fp, char **buff);
void				dragon4_prec(char **fp_buff, t_s32 *exp,
									t_ieee_fmt style, t_u32 preci);

#endif /* DRAGON4_H */

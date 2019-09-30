/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:25:43 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 04:14:56 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAGON4_H
# define DRAGON4_H

# include "libft.h"
# include "ieeefp.h"

# define DRAGON4_BUFF_SIZE					52

t_s32				dragon4(t_ieeefp *fp, char **buff);
void				dragon4_prec(char **fp_buff, t_s32 *exp,
									t_ieee_fmt style, t_u32 preci);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:29:45 by archid-           #+#    #+#             */
/*   Updated: 2019/06/24 20:26:44 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include "libft.h"

int		ft_printf(const char *fmt, ...);
int		ft_dprintf(const int fd, const char *fmt, ...);
int		ft_sprintf(char *str, const char *fmt, ...);
int		ft_snprintf(char *str, size_t size, const char *fmt, ...);
int		ft_asprintf(char **ret, const char *fmt, ...);

#endif

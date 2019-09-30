/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:59:49 by archid-           #+#    #+#             */
/*   Updated: 2019/09/30 04:15:55 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include <stdbool.h>

# define COL_RESET			   "\x1b[0m"
# define COL_BOLD			   "\x1b[1m"
# define COL_DIM               "\x1b[2m"
# define COL_ITALIC            "\x1b[3m"
# define COL_UNDERLINE		   "\x1b[4m"

# define COL_FG_BLACK		   "\x1b[30m"
# define COL_FG_RED			   "\x1b[31m"
# define COL_FG_GREEN		   "\x1b[32m"
# define COL_FG_YELLOW		   "\x1b[33m"
# define COL_FG_BLUE		   "\x1b[34m"
# define COL_FG_MAGENTA		   "\x1b[35m"
# define COL_FG_CYAN		   "\x1b[36m"
# define COL_FG_WHITE		   "\x1b[37m"

# define COL_BG_BLACK		   "\x1b[40m"
# define COL_BG_RED		       "\x1b[41m"
# define COL_BG_GREEN		   "\x1b[42m"
# define COL_BG_YELLOW		   "\x1b[43m"
# define COL_BG_BLUE		   "\x1b[44m"
# define COL_BG_MAGENTA	       "\x1b[45m"
# define COL_BG_CYAN		   "\x1b[46m"
# define COL_BG_WHITE		   "\x1b[47m"

# define COLORS_BUFF_SIZE			11

typedef struct	s_color
{
	char *base;
	bool is_auto_reset;
}				t_color;

#endif

#include "format.h"

static char *all_colors[][2] =
{
	{"black_fg", COL_FG_BLACK},
	{"red_fg", COL_FG_RED},
	{"green_fg", COL_FG_GREEN},
	{"yellow_fg", COL_FG_YELLOW},
	{"blue_fg", COL_FG_BLUE},
	{"magenta_fg", COL_FG_MAGENTA},
	{"cyan_fg", COL_FG_CYAN},
	{"white_fg", COL_FG_WHITE},

	{"black_bg", COL_BG_BLACK},
	{"red_bg", COL_BG_RED},
	{"green_bg", COL_BG_GREEN},
	{"yellow_bg", COL_BG_YELLOW},
	{"blue_bg", COL_BG_BLUE},
	{"magenta_bg", COL_BG_MAGENTA},
	{"cyan_bg", COL_BG_CYAN},
	{"white_bg", COL_BG_WHITE},

	{"reset", COL_RESET},
	{"bold", COL_BOLD},
	{"white", COL_DIM},
	{"dim", COL_DIM},
	{"italic", COL_ITALIC},
	{"underline", COL_UNDERLINE},

	{NULL, NULL}
};

static char *get_color(char *buff)
{
	t_s16 i;

	i = 0;
	while (buff && all_colors[i][0])
	{
		if (!ft_strcmp(all_colors[i][0], buff))
			return (all_colors[i][1]);
		i++;
	}
	return (NULL);
}

#define COLORS_BUFF_SIZE			11

static t_color	read_color(char **fmt)
{
	char		buff[COLORS_BUFF_SIZE];
	size_t		size;
	t_color		col;

	col = (t_color){NULL, (*fmt)[0] == '$'};
	size = 0;
	*fmt += col.is_auto_reset;
	ft_bzero(buff, COLORS_BUFF_SIZE * sizeof(char));
	while ((*fmt)[size] && (*fmt)[size] != '}'
				&& size < COLORS_BUFF_SIZE)
	{
		buff[size] = (*fmt)[size];
		size++;
	}
	if ((*fmt)[size] != '}')
		return col;
	col.base = get_color(buff);
	*fmt += size + 1;
	return (col);
}

bool			format_apply_color(char **fmt, t_list **alstfrmt, int *index)
{
	t_color			col;

	if (*fmt[0] != '{')
		return (false);
	*fmt += 1;
	if (!(col = read_color(fmt)).base)
		return true;
	ft_lstpush(alstfrmt,
					ft_lstnew(format_const_string(*index, col.base),
							  sizeof(t_frmt)));
	return true;
}

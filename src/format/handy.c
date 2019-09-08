#include "format.h"

void	format_free(void *dat, size_t size)
{
	if (size)
		free(dat);
}

t_frmt	*format_const_string(int index, char *str)
{
	static t_frmt frmt;

	ft_bzero(&frmt, sizeof(t_frmt));
	frmt.conv = CONV_FRMT;
	frmt.ifrmt = index;
	frmt.data.str = str;
	return (&frmt);
}

static bool		format_percentage(char **fmt, t_list **alst, int *index)
{
	if ((*fmt)[0] != '%')
		return (false);

	ft_lstpush(alst, ft_lstnew(format_const_string(*index, "%"),
									sizeof(t_frmt)));
	*fmt += 1;
	return (true);
}

void			format_parse(const char *fmt, t_list **alstfrmt)
{
	int index = 0;
	char *tmp;

	while (fmt && ++index)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (!format_percentage((char **)&fmt, alstfrmt, &index))
				format_doparse((char **)&fmt, alstfrmt, &index);
			continue;
		}
		tmp = ft_strchr(fmt, '%');
		ft_lstpush(alstfrmt, ft_lstnew(format_const_string(index,
			ft_strrdup(fmt, fmt + LEN_DIFF(fmt, tmp))), sizeof(t_frmt)));
		fmt = tmp;
	}
}

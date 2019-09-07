#include "format.h"

/* FIXME: free string as so */
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

void	format_parse(const char *fmt, t_list **alstfrmt)
{
	int index = 0;
	char *tmp;

	while (fmt && ++index)
	{
		if (*fmt == '%')
		{
			format_doparse((char **)&fmt, alstfrmt, &index);
			continue;
		}
		tmp = ft_strchr(fmt, '%');
		ft_lstpush(alstfrmt, ft_lstnew(format_const_string(index,
			ft_strrdup(fmt, fmt + LEN_DIFF(fmt, tmp))), sizeof(t_frmt)));
		fmt = tmp;
	}
}

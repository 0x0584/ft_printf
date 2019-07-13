/*		   File:	ft_lst_mergesort.c
 *		 Author:	ANAS RCHID
 *	Description:	Implementation of merge sort for lists
 *
 *	  Created: <2019-07-05 Fri 20:54:41>
 *	  Updated: <2019-07-06 Sat 02:36:24>
 */

#include "libft.h"


static t_plist		helper_merge(t_plist left, t_plist right,
							   int (cmp)(t_plist, t_plist))
{
	t_plist root;
	bool	sort_on_left;

	UNLESS_RET(left, right);
	UNLESS_RET(right, left);
	sort_on_left = cmp(left, right) > 0;
	root = sort_on_left ? left : right;
	root->next = helper_merge(sort_on_left ? left->next : left,
							  sort_on_left ? right : right->next,
							  cmp);
	return (root);
}

static void		   helper_halfsplit(t_plist root, t_plist *ahead,
									t_plist *atail)
{
	t_plist foo;
	t_plist bar;

	bar = root;
	foo = root->next;
	while (foo)
	{
		foo = foo->next;
		if (foo)
		{
			bar = bar->next;
			foo = foo->next;
		}
	}
	*ahead = root;
	*atail = bar->next;
	bar->next = NULL;
}

void				ft_lst_mergesort(t_plist *alst, int (cmp)(t_plist, t_plist))
{
	t_plist left;
	t_plist right;

	if (!alst || !*alst || !(*alst)->next)
		return ;
	helper_halfsplit(*alst, &left, &right);
	ft_lst_mergesort(&left, cmp);
	ft_lst_mergesort(&right, cmp);
	*alst = helper_merge(left, right, cmp);
}

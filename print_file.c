/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:40:05 by epillot           #+#    #+#             */
/*   Updated: 2017/01/18 18:52:23 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void     std_cross(t_flist *list, int tab[7], t_lsopt *opt)
{
	if (!list)
		return ;
	if (list->left)
		std_cross(list->left, tab, opt);
	if ((opt->f_print && !S_ISDIR(list->mode)) || opt->d_print)
	{
		print_content(list, *opt, tab);
		opt->printed = 1;
	}
	if (list->right)
		std_cross(list->right, tab, opt);
}

static void		rev_cross(t_flist *list, int tab[7], t_lsopt *opt)
{
	if (!list)
		return ;
	if (list->right)
		rev_cross(list->right, tab, opt);
	if ((opt->f_print && !S_ISDIR(list->mode)) || opt->d_print)
	{
		print_content(list, *opt, tab);
		opt->printed = 1;
	}
	if (list->left)
		rev_cross(list->left, tab, opt);
}

void	print_file(t_flist *list, t_lsopt *opt, int dir)
{
	int		tab[7];

	ft_bzero(tab, sizeof(tab));
	if (opt->l)
	{
		get_additional_part(list, *opt, tab);
		if (tab[3] && tab[5] > tab[3] + tab[4] + 2)
			tab[3] = tab[5] - tab[4] - 2;
		else if (tab[3])
			tab[5] = tab[3] + tab[4] + 2;
		if (list && dir)
			ft_printf("total %d\n", tab[6]);
	}
	if (opt->r)
		rev_cross(list, tab, opt);
	else
		std_cross(list, tab, opt);
}

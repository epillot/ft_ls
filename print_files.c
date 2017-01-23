/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 12:36:55 by epillot           #+#    #+#             */
/*   Updated: 2017/01/23 15:29:23 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_content_l(t_flist *list, int tab[7], t_lsopt opt)
{
	char	link[PATH_MAX];

	ft_printf("%s  %*hu ", list->perm, tab[0], list->nb_link);
	ft_printf("%-*s  %-*s  ", tab[1], list->usr_id, tab[2], list->grp_id);
	if (S_ISCHR(list->mode) || S_ISBLK(list->mode))
	{
		ft_printf("%*d, ", tab[3], major(list->rdev));
		ft_printf("%*d ", tab[4], minor(list->rdev));
	}
	else
		ft_printf("%*lld ", tab[5], list->size);
	if (opt.p && S_ISDIR(list->mode))
		ft_printf("%s %s/", list->time, list->name);
	else
		ft_printf("%s %s", list->time, list->name);
	if (*list->perm == 'l')
	{
		ft_bzero(link, PATH_MAX);
		readlink(list->path, link, PATH_MAX);
		ft_printf(" -> %s\n", link);
	}
	else
		ft_putchar('\n');
}

static void		print_content(t_flist *list, t_lsopt opt, int tab[6])
{
	if (opt.l)
		print_content_l(list, tab, opt);
	else if (opt.p && S_ISDIR(list->mode))
		ft_printf("%s/\n", list->name);
	else
		ft_printf("%s\n", list->name);
}

static void		std_cross(t_flist *list, int tab[7], t_lsopt *opt)
{
	if (!list)
		return ;
	if (list->left)
		std_cross(list->left, tab, opt);
	if (opt->d_print || !S_ISDIR(list->mode))
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
	if (opt->d_print || !S_ISDIR(list->mode))
	{
		print_content(list, *opt, tab);
		opt->printed = 1;
	}
	if (list->left)
		rev_cross(list->left, tab, opt);
}

void			print_files(t_flist *list, t_lsopt *opt, int dir)
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

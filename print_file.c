/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:40:05 by epillot           #+#    #+#             */
/*   Updated: 2017/01/12 19:59:03 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void     print_std(t_flist *list, int tab[6], t_lsopt opt)
{
	if (!list)
		return ;
	if (list->left)
		print_std(list->left, tab, opt);
	print_content(list, opt, tab);
	if (list->right)
		print_std(list->right, tab, opt);
}

static void		print_rev(t_flist *list, int tab[6], t_lsopt opt)
{
	if (!list)
		return ;
	if (list->right)
		print_rev(list->right, tab, opt);
	print_content(list, opt, tab);
	if (list->left)
		print_rev(list->left, tab, opt);
}

void	print_file(t_flist *list, t_lsopt opt)
{
	int		tab[6];

	ft_bzero(tab, sizeof(tab));
	if (opt.l)
		get_width(list, tab);
	if (opt.r)
		print_rev(list, tab, opt);
	else
		print_std(list, tab, opt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:40:05 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 19:08:38 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void     print_std(t_flist *list, char *str, int tab[6], t_lsopt opt)
{
	if (!list)
		return ;
	if (list->left)
		print_std(list->left, list->left->file_name, tab, opt);
	print_content(list, opt, str, tab);
	if (list->right)
		print_std(list->right, list->right->file_name, tab, opt);
}

static void		print_rev(t_flist *list, char *str, int tab[6], t_lsopt opt)
{
	if (!list)
		return ;
	if (list->right)
		print_rev(list->right, list->right->file_name, tab, opt);
	print_content(list, opt, str, tab);
	if (list->left)
		print_rev(list->left, list->left->file_name, tab, opt);
}

void	print_file(t_flist *list, char *str, t_lsopt opt)
{
	int		tab[6];

	ft_bzero(tab, sizeof(tab));
	if (opt.l)
		get_width(list, tab);
	if (opt.r)
		print_rev(list, str, tab, opt);
	else
		print_std(list, str, tab, opt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:33:08 by epillot           #+#    #+#             */
/*   Updated: 2017/01/20 12:57:02 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_dir_content(t_flist *list, t_lsopt *opt, int size)
{
	t_flist		*new;

	new = NULL;
	if (size > 1 && opt->printed)
		ft_printf("\n%s:\n", list->path);
	else if (size > 1)
	{
		ft_printf("%s:\n", list->path);
		opt->printed = 1;
	}
	else if (opt->printed)
		ft_putchar('\n');
	get_flist(list->name, list->path, *opt, &new);
	print_files(new, opt, 1);
	print_dir(new, opt, 2, 1);
	free_list(&new);
}

static void		std_cross(t_flist *list, t_lsopt *opt, int size, int nb)
{
	if (!list || (nb && !opt->rec))
		return ;
	if (list->left)
		std_cross(list->left, opt, size, nb);
	if (S_ISDIR(list->mode) && (!nb ||
				(ft_strcmp(list->name, ".") && ft_strcmp(list->name, ".."))))
		print_dir_content(list, opt, size);
	if (list->right)
		std_cross(list->right, opt, size, nb);
}

static void		rev_cross(t_flist *list, t_lsopt *opt, int size, int nb)
{
	if (!list || (nb && !opt->rec))
		return ;
	if (list->right)
		rev_cross(list->right, opt, size, nb);
	if (S_ISDIR(list->mode) && (!nb
				|| (ft_strcmp(list->name, ".") && ft_strcmp(list->name, ".."))))
		print_dir_content(list, opt, size);
	if (list->left)
		rev_cross(list->left, opt, size, nb);
}

void			print_dir(t_flist *list, t_lsopt *opt, int size, int nb)
{
	if (opt->r)
		rev_cross(list, opt, size, nb);
	else
		std_cross(list, opt, size, nb);
}

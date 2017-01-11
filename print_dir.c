/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:33:08 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 19:44:25 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		list_size(t_flist *list)
{
	if (!list)
		return (0);
	return (1 + list_size(list->left) + list_size(list->right));
}

static blkcnt_t	get_total(t_flist *list)
{
	int	size;

	if (!list)
		return (0);
	size = list->nb_blocks;
	return (get_total(list->left) + get_total(list->right) + size);
}

static void		print_std(t_flist *list, t_lsopt opt, int size)
{
	t_flist		*new;

	new = NULL;
	if (!list)
		return ;
	if (list->left)
		print_std(list->left, opt, size);
	get_file_list(list->file_name, opt, &new);
	if (size > 1)
		ft_printf("%s:\n", list->file_name);
	if (opt.l)
		ft_printf("total %lld\n", get_total(new));
	print_file(new, list->file_name, opt);
	if (list->right)
		print_std(list->right, opt, size);
}

static void		print_rev(t_flist *list, t_lsopt opt, int size)
{
	t_flist		*new;

	new = NULL;
	if (!list)
		return ;
	if (list->right)
		print_rev(list->right, opt, size);
	get_file_list(list->file_name, opt, &new);
	if (size > 1)
		ft_printf("%s:\n", list->file_name);
	if (opt.l)
		ft_printf("total %lld\n", get_total(new));
	print_file(new, list->file_name, opt);
	if (list->left)
		print_rev(list->left, opt, size);
}

void			print_dir(t_flist *list, t_lsopt opt)
{
	int		size;

	size = list_size(list);
	if (opt.r)
		print_rev(list, opt, size);
	else
		print_std(list, opt, size);
}

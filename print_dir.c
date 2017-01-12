/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:33:08 by epillot           #+#    #+#             */
/*   Updated: 2017/01/12 20:48:07 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		list_size(t_flist *list)
{
	if (!list)
		return (0);
	return (1 + list_size(list->left) + list_size(list->right) + list_size(list->next));
}

static blkcnt_t	get_total(t_flist *list)
{
	int	size;

	if (!list)
		return (0);
	size = list->nb_blocks;
	return (get_total(list->left) + get_total(list->right) + size);
}

static void		print_std(t_flist *list, t_lsopt opt, int *size, int *printed)
{
	t_flist		*new;
	t_ll		*l;

	new = NULL;
	l = NULL;
	if (!list)
		return ;
	if (list->left)
		print_std(list->left, opt, size, printed);
	if ((get_file_list(list->path, opt, &new, &l) == -1))
		return ;
	if (*size > 1 || *printed > 0)
		ft_printf("%s:\n", list->path);
	if (opt.l)
		ft_printf("total %lld\n", get_total(new));
	print_file(new, opt);
	(*printed)++;
	if (--(*size) > 0)
		ft_putchar('\n');
	while (l != NULL)
	{
		print_dir(l->list, opt, printed);
		l = l->next;
	}
	if (list->right)
		print_std(list->right, opt, size, printed);
}

static void		print_rev(t_flist *list, t_lsopt opt, int *size, int *printed)
{
	t_flist		*new;
	t_ll		*l;

	new = NULL;
	if (!list)
		return ;
	if (list->right)
		print_rev(list->right, opt, size, printed);
	get_file_list(list->file_name, opt, &new, &l);
	if (*size > 1 || *printed > 0)
		ft_printf("%s:\n", list->file_name);
	if (opt.l)
		ft_printf("total %lld\n", get_total(new));
	print_file(new, opt);
	(*printed)++;
	if (--(*size) > 0)
		ft_putchar('\n');
	if (list->left)
		print_rev(list->left, opt, size, printed);
}

void			print_dir(t_flist *list, t_lsopt opt, int *printed)
{
	int		size;

	size = list_size(list);
	if (opt.r)
		print_rev(list, opt, &size, printed);
	else
		print_std(list, opt, &size, printed);
}

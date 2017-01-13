/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:33:08 by epillot           #+#    #+#             */
/*   Updated: 2017/01/13 19:28:19 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static blkcnt_t	get_total(t_flist *list)
{
	int	size;

	if (!list)
		return (0);
	size = list->nb_blocks;
	return (get_total(list->left) + get_total(list->right) + size);
}

static void		print_std(t_flist *list, t_lsopt opt, int *printed, int nb)
{
	t_flist		*new;

	new = NULL;
	if (!list)
		return ;
	if (list->left)
		print_std(list->left, opt, printed, nb);
	if (!nb || (S_ISDIR(list->mode) && ft_strcmp(list->file.name, ".") && ft_strcmp(list->file.name, "..")))
	{
		if ((get_file_list(list->file, opt, &new) == -1))
			return ;
		if (*printed > 0 && nb)
			ft_printf("\n%s:\n", list->file.path);
		else if (nb)
			ft_printf("%s:\n", list->file.path);
		else if (*printed > 0)
			ft_putchar('\n');
		if (opt.l)
			ft_printf("total %lld\n", get_total(new));
		print_file(new, opt);
		(*printed)++;
		if (opt.rec)
			print_std(new, opt, printed, 1);
		free_list(&new);
	}
	if (list->right)
		print_std(list->right, opt, printed, nb);
}

static void		print_rev(t_flist *list, t_lsopt opt, int *printed)
{
	t_flist		*new;

	new = NULL;
	if (!list)
		return ;
	if (list->right)
		print_rev(list->right, opt, printed);
	get_file_list(list->file, opt, &new);
	if (*printed > 0)
		ft_printf("%s:\n", list->file.name);
	if (opt.l)
		ft_printf("total %lld\n", get_total(new));
	print_file(new, opt);
	(*printed)++;
	if (list->left)
		print_rev(list->left, opt, printed);
}

void			print_dir(t_flist *list, t_lsopt opt, int *printed, int nb)
{
	if (opt.r)
		print_rev(list, opt, printed);
	else
		print_std(list, opt, printed, nb);
}

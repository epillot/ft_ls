/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:09:10 by epillot           #+#    #+#             */
/*   Updated: 2017/01/12 16:21:59 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_content_l(t_flist *list, int tab[6])
{
	int		ret;
	char	link[PATH_MAX];

	ft_printf("%s %*hu ", list->perm, tab[0], list->nb_link);
	ft_printf("%-*s %-*s ", tab[1], list->usr_id, tab[2], list->grp_id);
	if (*list->perm == 'c' || *list->perm == 'b')
		ft_printf("%*d,%*d ", tab[3], major(list->rdev), tab[4], minor(list->rdev));
	else
		ft_printf("%*lld ", tab[5], list->size);
	ft_printf("%s %s", list->time, list->file_name);
	if (*list->perm == 'l')
	{
		ret = readlink(list->path, link, PATH_MAX);
		link[ret] = '\0';
		ft_printf(" -> %s\n", link);
	}
	else
		ft_putchar('\n');
}

void		print_content(t_flist *list, t_lsopt opt, int tab[6])
{
	if (opt.l)
		print_content_l(list, tab);
	else
		ft_printf("%s\n", list->file_name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:09:10 by epillot           #+#    #+#             */
/*   Updated: 2017/01/17 17:53:44 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_content_l(t_flist *list, int tab[7])
{
	char	link[NAME_MAX + 1];

	ft_printf("%s  %*hu ", list->perm, tab[0], list->nb_link);
	ft_printf("%-*s  %-*s  ", tab[1], list->usr_id, tab[2], list->grp_id);
	if (*list->perm == 'c' || *list->perm == 'b')
		ft_printf("%*d, %*d ", tab[3], major(list->rdev), tab[4], minor(list->rdev));
	else
		ft_printf("%*lld ", tab[5], list->size);
	ft_printf("%s %s", list->time, list->name);
	if (*list->perm == 'l')
	{
		ft_bzero(link, NAME_MAX + 1);
		readlink(list->path, link, NAME_MAX);
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
		ft_printf("%s\n", list->name);
}

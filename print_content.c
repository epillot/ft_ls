/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:09:10 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 18:56:10 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_content_l(t_flist *list, char *str, int tab[6])
{
	char	link[PATH_MAX];
	int		ret;
//	char	*s;

	ft_printf("%s %*hu ", list->perm, tab[0], list->nb_link);
	ft_printf("%-*s %-*s ", tab[1], list->usr_id, tab[2], list->grp_id);
	if (*list->perm == 'c' || *list->perm == 'b')
		ft_printf("%*d,%*d ", tab[3], major(list->rdev), tab[4], minor(list->rdev));
	else
		ft_printf("%*lld ", tab[5], list->size);
	ft_printf("%s %s", list->time, list->file_name);
	if (*list->perm == 'l')
	{
//		ft_sprintf(&s, "%s/%s", str, list->file_name);
		ret = readlink(str, link, PATH_MAX);
//		free(s);
		link[ret] = '\0';
		ft_printf(" -> %s\n", link);
	}
	else
		ft_putchar('\n');
}

void		print_content(t_flist *list, t_lsopt opt, char *str, int tab[6])
{
	if (opt.l)
		print_content_l(list, str, tab);
	else
		ft_printf("%s\n", list->file_name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 11:45:18 by epillot           #+#    #+#             */
/*   Updated: 2017/01/10 18:56:17 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <limits.h>

static blkcnt_t	get_total(t_flist *list)
{
	int	size;

	if (!list)
		return (0);
	size = list->nb_blocks;
	return (get_total(list->left) + get_total(list->right) + size);
}

static void		print_content(t_flist *list, char *str, int tab[6])
{
	char	link[PATH_MAX];
	int		ret;
	char	*s;

	if (!list)
		return ;
	if (list->left)
		print_content(list->left, str, tab);
	ft_printf("%s %*hu ", list->perm, tab[0], list->nb_link);
	ft_printf("%-*s %-*s ", tab[1], list->usr_id, tab[2], list->grp_id);
	if (*list->perm == 'c' || *list->perm == 'b')
		ft_printf("%*d,%*d ", tab[3], major(list->rdev), tab[4], minor(list->rdev));
	else
		ft_printf("%*lld ", tab[5], list->size);
	ft_printf("%s %s", list->time, list->file_name);
	if (*list->perm == 'l')
	{
		ft_sprintf(&s, "%s/%s", str, list->file_name);
		ret = readlink(s, link, PATH_MAX);
		link[ret] = '\0';
		ft_printf(" -> %s\n", link);
	}
	else
		ft_putchar('\n');
	if (list->right)
		print_content(list->right, str, tab);
}

int				main(int ac, char **av)
{
	t_lsopt		opt;
	int			i;
	t_flist		*list;
	int			tab[6];

	list = NULL;
	ft_bzero(tab, sizeof(tab));
	i = get_option_ls(ac, av, &opt);
	get_file_list(av[i], opt, &list);
	get_width(list, tab);
	ft_printf("total %lld\n", get_total(list));
	print_content(list, av[i], tab);
}

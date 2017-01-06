/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 11:45:18 by epillot           #+#    #+#             */
/*   Updated: 2017/01/06 15:49:28 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_content(t_flist *list)
{
	if (!list)
		return ;
	if (list->left)
		print_content(list->left);
	ft_printf("%s%5hu %-8s %s %7lld %s %s\n", list->perm, list->nb_link, list->usr_id, list->grp_id, list->size, list->time, list->file_name);
	if (list->right)
		print_content(list->right);
}

int			main(int ac, char **av)
{
	t_lsopt		option;
	int			i;
	t_flist		*list;

	i = get_option_ls(ac, av, &option);
//	ft_printf("ok1\n");
	get_file_list(av[i], option, &list);
//	ft_printf("ok2\n");
	print_content(list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 11:45:18 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 19:47:13 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		get_arg_list_f(int ac, char **av, t_lsopt opt, t_flist **list)
{
	int     i;
	t_stat  buf;

	i = 0;
	while (i < ac)
	{
		if (lstat(av[i], &buf) != -1)
			if (!S_ISDIR(buf.st_mode))
				get_file_list2(av[i], buf, opt, list);
		i++;
	}
}

static void		get_arg_list_d(int ac, char **av, t_lsopt opt, t_flist **list)
{
	int		i;
	t_stat	buf;

	i = 0;
	if (ac == 0)
	{
		av[0] = ".";
		ac = 1;
	}
	while (i < ac)
	{
		if (lstat(av[i], &buf) != -1)
			if (S_ISDIR(buf.st_mode))
				get_file_list2(av[i], buf, opt, list);
		i++;
	}
}

int				main(int ac, char **av)
{
	t_lsopt		opt;
	int			i;
	t_flist		*list;

	list = NULL;
	i = get_option_ls(ac, av, &opt);
	ac -= i;
	av += i;
	get_arg_list_f(ac, av, opt, &list);
	print_file(list, list->file_name, opt);
	if (list)
		ft_putchar('\n');
	list = NULL;
	get_arg_list_d(ac, av, opt, &list);
	print_dir(list, opt);
}

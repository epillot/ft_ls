/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:11:27 by epillot           #+#    #+#             */
/*   Updated: 2017/01/13 19:32:24 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*static int		add_node_arg(char *file, t_stat buf, t_lsopt opt, t_flist **list)
{
	t_flist	*elem;

	if (!(elem = create_node(file, buf, file)))
		return (0);
	if (*list)
		link_node(list, elem, opt);
	else
		*list = elem;
	return (1);
}*/

static void		get_arg_list_f(int ac, char **av, t_lsopt opt, t_flist **list)
{
	int     i;
	t_stat  buf;
	t_file	file;

	i = 0;
	while (i < ac)
	{
		ft_strcpy(file.name, av[i]);
		ft_strcpy(file.path, av[i]);
		if (opt.l)
		{
			if (lstat(av[i], &buf) != -1)
				if (!S_ISDIR(buf.st_mode))
					add_node(file, buf, opt, list);
		}
		else
		{
			if (stat(av[i], &buf) != -1)
				if (!S_ISDIR(buf.st_mode))
					add_node(file, buf, opt, list);
		}
		i++;
	}
}

static void		get_arg_list_d(int ac, char **av, t_lsopt opt, t_flist **list)
{
	int		i;
	t_stat	buf;
	t_file	file;

	i = 0;
	if (ac == 0)
	{
		av[0] = ".";
		ac = 1;
	}
	while (i < ac)
	{
		ft_strcpy(file.name, av[i]);
		ft_strcpy(file.path, av[i]);
		if (opt.l)
		{
			if (lstat(av[i], &buf) != -1)
				if (S_ISDIR(buf.st_mode))
					add_node(file, buf, opt, list);
		}
		else
		{
			if (stat(av[i], &buf) != -1)
				if (S_ISDIR(buf.st_mode))
					add_node(file, buf, opt, list);
		}
		i++;
	}
}

int				main(int ac, char **av)
{
	t_lsopt		opt;
	int			i;
	t_flist		*list;
	int			printed;

	list = NULL;
	printed = 0;
	i = get_option_ls(ac, av, &opt);
	ac -= i;
	av += i;
	get_arg_list_f(ac, av, opt, &list);
	if (list)
	{
		print_file(list, opt);
		free_list(&list);
		printed++;
	}
	get_arg_list_d(ac, av, opt, &list);
	print_dir(list, opt, &printed, 0);
	free_list(&list);
	return (0);
}

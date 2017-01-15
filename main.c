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

static int		init_file(char *param, t_file *file, int err)
{
	int	i;
	
	i = 0;
	while (i < NAME_MAX + 1 && param[i])
	{
		file->name[i] = param[i];
		file->path[i] = param[i];
		i++;
	}
	if (i == NAME_MAX + 1 && err)
	{
		errno = ENAMETOOLONG;
		ft_printf("ft_ls: %s: %s\n", param, strerror(errno));
		return (0);
	}
	else if (i < NAME_MAX + 1)
	{
		file->name[i] = '\0';
		file->path[i] = '\0';
		return (1);
	}	
	return (0);
}

static void		get_arg_list_f(int ac, char **av, t_lsopt opt, t_flist **list)
{
	int     i;
	t_stat  buf;
	t_file	file;

	i = 0;
	while (i < ac)
	{
		if (init_file(av[i], &file, 1))
		{
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
		if (init_file(av[i], &file, 0))
		{
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

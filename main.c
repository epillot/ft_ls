/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:11:27 by epillot           #+#    #+#             */
/*   Updated: 2017/01/18 16:07:14 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		sort_param_ascii(int ac, char **av)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < ac - 1)
	{
		j = i + 1;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				tmp = av[i];
				av[i] = av[j];
				av[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int		init_file(char *arg, t_file *file)
{
	int	i;

	i = 0;
	while (i < NAME_MAX + 1 && arg[i])
	{
		file->name[i] = arg[i];
		file->path[i] = arg[i];
		i++;
	}
	if (i == NAME_MAX + 1)
	{
		errno = ENAMETOOLONG;
		ls_error(0, arg);
		return (0);
	}
	else
	{
		file->name[i] = '\0';
		file->path[i] = '\0';
		return (1);
	}
	return (0);
}

static void		add_arg_in_list(char *arg, t_lsopt opt, t_flist **list)
{
	t_stat	buf;
	t_file	file;

	if (init_file(arg, &file))
	{
		if (opt.l)
		{
			if (lstat(arg, &buf) != -1)
				add_node(file, buf, opt, list);
			else
				ls_error(0, arg);
		}
		else
		{
			if (stat(arg, &buf) != -1)
				add_node(file, buf, opt, list);
			else if (lstat(arg, &buf) != -1)
				add_node(file, buf, opt, list);
			else
				ls_error(0, arg);
		}
	}
}

static void		get_arg_list(int ac, char **av, t_lsopt opt, t_flist **list)
{
	int		i;

	i = 0;
	if (ac == 0)
	{
		av[0] = ".";
		ac = 1;
	}
	while (i < ac)
	{
		add_arg_in_list(av[i], opt, list);
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
	sort_param_ascii(ac, av);
	get_arg_list(ac, av, opt, &list);
	opt.f_print = 1;
	print_file(list, &opt, 0);
	opt.d_print = 1;
	print_dir(list, &opt, ac, 0);
	free_list(&list);
	return (0);
}

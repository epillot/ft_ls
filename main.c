/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:11:27 by epillot           #+#    #+#             */
/*   Updated: 2017/01/17 18:12:34 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		init_file(char *param, t_file *file)
{
	int	i;
	
	i = 0;
	while (i < NAME_MAX + 1 && param[i])
	{
		file->name[i] = param[i];
		file->path[i] = param[i];
		i++;
	}
	if (i == NAME_MAX + 1)
	{
		errno = ENAMETOOLONG;
		ls_error(0, param);
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

void			get_arg_list(int ac, char **av, t_lsopt opt, t_flist **list)
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
		if (init_file(av[i], &file))
		{
			if (opt.l)
			{
				if (lstat(av[i], &buf) != -1)
					add_node(file, buf, opt, list);
				else
					ls_error(0, av[i]);
			}
			else
			{
				if (stat(av[i], &buf) != -1)
					add_node(file, buf, opt, list);
				else
					ls_error(0, av[i]);
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

	list = NULL;
	i = get_option_ls(ac, av, &opt);
	ac -= i;
	av += i;
	get_arg_list(ac, av, opt, &list);
	opt.f_print = 1;
	print_file(list, &opt, 0);
	opt.d_print = 1;
	print_dir(list, &opt, ac, 0);
	free_list(&list);
	return (0);
}

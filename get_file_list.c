/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/13 19:28:44 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		get_path(char *file, char *parent, char path[PATH_MAX])
{
	if (*parent)
	{
		ft_strcpy(path, parent);
		if (path[ft_strlen(parent) - 1] != '/')
			path[ft_strlen(parent)] = '/';
		ft_strcpy(path + ft_strlen(parent) + 1, file);
	}
	else
		ft_strcpy(path, file);
}

int				get_file_list(t_file file, t_lsopt opt, t_flist **list)
{
	DIR			*dir;
	t_dirent	*info;
	t_stat		buf;
	t_file		new;

	if (!(dir = opendir(file.path)))
	{
		ft_printf("ft_ls: %s: %s\n", file.path, strerror(errno));
		return (-1);
	}
	while ((info = readdir(dir)))
	{
		if (opt.a || info->d_name[0] != '.')
		{
			ft_strcpy(new.name, info->d_name);
			get_path(new.name, file.path, new.path);
			if (lstat(new.path, &buf) != -1)
				add_node(new, buf, opt, list);
		}
	}
	closedir(dir);
	return (1);
}

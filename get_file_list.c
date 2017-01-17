/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/17 16:51:53 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		get_path(char *file, char *parent, char path[PATH_MAX])
{
/*	if (*parent)
	{
		ft_strcpy(path, parent);
		if (path[ft_strlen(parent) - 1] != '/')
			path[ft_strlen(parent)] = '/';
		ft_strcpy(path + ft_strlen(parent) + 1, file);
	}
	else
		ft_strcpy(path, file);*/
	int i = 0;
	while (i < PATH_MAX && parent[i])
	{
		path[i] = parent[i];
		i++;
	}
	if (i < PATH_MAX && path[i - 1] != '/')
		path[i++] = '/';
	if (PATH_MAX - i <= (int)ft_strlen(file))
	{
		errno = ENAMETOOLONG;
		ft_putstr_fd("ft_ls: ", 2); //%s: %s\n", file, strerror(errno));
		ft_putstr_fd(file, 2);
		ft_putchar_fd(' ', 2);
		ft_putendl_fd(strerror(errno), 2);
		return (0);
	}
	else
	{
		while (*file)
			path[i++] = *file++;
		path[i] = '\0';
		return (1);
	}
}

int				get_file_list(char *file, char *path, t_lsopt opt, t_flist **list)
{
	DIR			*dir;
	t_dirent	*info;
	t_stat		buf;
	t_file		new;

	if (!(dir = opendir(path)))
	{
		ls_error(0, file);
		return (-1);
	}
	while ((info = readdir(dir)))
	{
		if (opt.a || info->d_name[0] != '.')
		{
			ft_strncpy(new.name, info->d_name, NAME_MAX + 1);
			//new.name = ft_strdup(info->d_name);
			if (get_path(new.name, path, new.path))
			{
				if (lstat(new.path, &buf) != -1)
					add_node(new, buf, opt, list);
				else
					ls_error(0, new.name);
			}
		}
	}
	closedir(dir);
	return (1);
}

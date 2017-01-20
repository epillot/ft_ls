/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/20 16:16:14 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		is_in(char *name)
{
	if (ft_strcmp(name, ".") == 0)
		return (0);
	if (ft_strcmp(name, "..") == 0)
		return (0);
	return (1);
}

static int		get_path(char *file, char *parent, char path[PATH_MAX])
{
	int	i;

	i = 0;
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
		ls_error(0, file);
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

void			get_flist(char *file, char *path, t_lsopt opt, t_flist **list)
{
	DIR			*dir;
	t_dirent	*info;
	t_stat		buf;
	t_file		new;

	if (!(dir = opendir(path)))
	{
		ls_error(0, file);
		return ;
	}
	while ((info = readdir(dir)))
	{
		if (opt.a || info->d_name[0] != '.' || (opt.aa && is_in(info->d_name)))
		{
			ft_strncpy(new.name, info->d_name, NAME_MAX + 1);
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
}

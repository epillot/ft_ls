/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/12 20:48:04 by epillot          ###   ########.fr       */
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

int				get_file_list(char *file, t_lsopt opt, t_flist **list, t_ll **l)
{
	DIR			*dir;
	t_dirent	*info;
	t_stat		buf;
	char		path[PATH_MAX];
	t_flist		*elem;
	t_ll		*tmp;
	t_ll		*tmp2;

	if (!(dir = opendir(file)))
	{
		ft_printf("ft_ls: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	while ((info = readdir(dir)))
	{
		if (opt.a || info->d_name[0] != '.')
		{
			get_path(info->d_name, file, path);
			if (lstat(path, &buf) != -1)
			{	
				if (!(elem = create_node(info->d_name, buf, path)))
					return (-1);
				if (*list)
					link_node(list, elem, opt);
				else
					*list = elem;
				if (opt.rec && *elem->perm == 'd' && ft_strcmp(info->d_name, ".") && ft_strcmp(info->d_name, ".."))
				{
					if (*l)
					{
						tmp = *l;
						tmp2 = ft_memalloc(sizeof(l));
						tmp2->list = elem;
						while (tmp->next)
							tmp = tmp->next;
						tmp->next = tmp2;
					}
					else
					{
						*l = ft_memalloc(sizeof(l));
						(*l)->list = elem;
					}
				}
			}
		}
	}
	return (1);
}

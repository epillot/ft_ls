/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/06 17:00:41 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>

static t_flist	*create_node(t_dirent *info, t_stat buf)
{
	t_flist		*output;
	t_passwd	*uid;
	t_group		*gid;

	if (!(output = (t_flist*)ft_memalloc(sizeof(t_flist))))
		return (NULL);
	if (!(uid = getpwuid(buf.st_uid)))
		return (NULL);
	if (!(gid = getgrgid(buf.st_gid)))
		return (NULL);
	get_right(buf.st_mode, output->perm);
	output->nb_link = buf.st_nlink;
	output->usr_id = uid->pw_name;
	output->grp_id = gid->gr_name;
	output->size = buf.st_size;
	if (!(output->time = get_time(buf.st_mtime)))
		return (NULL);
	ft_strcpy(output->file_name, info->d_name);
	return (output);
}

static void		link_node(t_flist *elem, t_flist *root)
{
	if (!root)
		return ;
	if (root->left == NULL && ft_strcmp(elem->file_name, root->file_name) < 0)
	{
		root->left = elem;
		return ;
	}
	if (root->right == NULL && ft_strcmp(elem->file_name, root->file_name) > 0)
	{
		root->right = elem;
		return ;
	}
	if (ft_strcmp(elem->file_name, root->file_name) > 0)
		link_node(elem, root->right);
	else
		link_node(elem, root->left);
}

int				get_file_list(char *file, t_lsopt opt, t_flist **list)
{
	DIR			*dir;
	t_dirent	*info;
	t_stat		buf;
	char		*path;
	t_flist		*elem;
	int i = 0;

	dir = opendir(file);
	info = readdir(dir);
	(void)opt;
	ft_sprintf(&path, "%s/%s", file, info->d_name);
	stat(path, &buf);
	free(path);
	*list = create_node(info, buf);
//	ft_printf("ok2-1");
	while ((info = readdir(dir)))
	{
		//ft_printf("%s\n", strerror(errno));
		ft_sprintf(&path, "%s/%s", file, info->d_name);
		if (stat(path, &buf) != -1)
		{	
			if (!(elem = create_node(info, buf)))
				return (-1);
	//		ft_printf("elem created: %s ", elem->file_name);
			link_node(elem, *list);
			i++;
	//		ft_printf("linked_node: %d\n", i);
		}
		free(path);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/10 18:56:20 by epillot          ###   ########.fr       */
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
	get_perm(buf.st_mode, output->perm);
	output->nb_link = buf.st_nlink;
	output->usr_id = uid->pw_name;
	output->grp_id = gid->gr_name;
	output->size = buf.st_size;
	output->mtime = buf.st_mtime;
	output->nb_blocks = buf.st_blocks;
	if (*output->perm == 'c' || *output->perm == 'b')
		output->rdev = buf.st_rdev;
	if (!(output->time = get_time(buf.st_mtime)))
		return (NULL);
	ft_strcpy(output->file_name, info->d_name);
	return (output);
}

static void		link_node_file_name(t_flist *elem, t_flist **root)
{
	t_flist	*tmp;

	tmp = *root;
	if (ft_strcmp(elem->file_name, tmp->file_name) < 0)
	{
		*root = (*root)->left;
		if (!*root)
			tmp->left = elem;
	}
	else
	{
		*root = (*root)->right;
		if (!*root)
			tmp->right = elem;
	}
}

static void		link_node(t_flist *elem, t_flist **root)
{
	t_flist	*tmp;

	tmp = *root;
	if (*root)
		while (tmp)
			link_node_file_name(elem, &tmp);
	else
		*root = elem;
}

static void		link_node_time(t_flist *elem, t_flist **root)
{
	t_flist	*tmp1;
	t_flist	*tmp2;

	tmp1 = *root;
	if (*root)
	{
		while (tmp1)
		{
			tmp2 = tmp1;
			if (elem->mtime == tmp1->mtime)
				link_node_file_name(elem, &tmp1);
			else if (elem->mtime > tmp1->mtime)
			{
				tmp1 = tmp1->left;
				if (!tmp1)
					tmp2->left = elem;
			}
			else
			{
				tmp1 = tmp1->right;
				if (!tmp1)
					tmp2->right = elem;
			}
		}
	}
	else
		*root = elem;
}

int				get_file_list(char *file, t_lsopt opt, t_flist **list)
{
	DIR			*dir;
	t_dirent	*info;
	t_stat		buf;
	char		*path;
	t_flist		*elem;

	dir = opendir(file);
	while ((info = readdir(dir)))
	{
		if (ft_sprintf(&path, "%s/%s", file, info->d_name) == -1)
			return (-1);
		if (lstat(path, &buf) != -1)
		{	
			if (!(elem = create_node(info, buf)))
				return (-1);
			if (opt.t == 1)
				link_node_time(elem, list);
			else
				link_node(elem, list);
		}
		free(path);
	}
	return (1);
}

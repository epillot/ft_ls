/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 19:08:12 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

	if (!(dir = opendir(file)))
	{
		ft_printf("ft_ls: %s: %s\n", file, strerror(errno));
		exit(EXIT_FAILURE);
	}
	while ((info = readdir(dir)))
	{
		if (ft_sprintf(&path, "%s/%s", file, info->d_name) == -1)
			return (-1);
		if (lstat(path, &buf) != -1)
		{	
			if (!(elem = create_elem(info->d_name, buf)))
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

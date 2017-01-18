/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:36:40 by epillot           #+#    #+#             */
/*   Updated: 2017/01/18 18:42:41 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_flist	*create_node(t_file file, t_stat buf)
{
	t_flist     *output;

	if (!(output = (t_flist*)ft_memalloc(sizeof(t_flist))))
		return (NULL);
	output->uid = buf.st_uid;
	output->gid = buf.st_gid;
	output->mode = buf.st_mode;
	output->nb_link = buf.st_nlink;
	output->size = buf.st_size;
	output->mtime = buf.st_mtime;
	output->nb_blocks = buf.st_blocks;
	output->rdev = buf.st_rdev;
	if (!(output->name = ft_strdup(file.name)))
		return (NULL);
	if (!(output->path = ft_strdup(file.path)))
		return (NULL);
	return (output);
}

static void		check_ascii(t_flist *elem, t_flist **node)
{
	t_flist	*tmp;

	tmp = *node;
	if (ft_strcmp(elem->name, tmp->name) < 0)
	{
		*node = (*node)->left;
		if (!*node)
			tmp->left = elem;
	}
	else
	{
		*node = (*node)->right;
		if (!*node)
			tmp->right = elem;
	}
}

static void		add_node_ascii(t_flist *root, t_flist *elem)
{
	while (root)
		check_ascii(elem, &root);
}

static void		add_node_time(t_flist *root, t_flist *elem)
{
	t_flist	*tmp;

	while (root)
	{
		tmp = root;
		if (elem->mtime == root->mtime)
			check_ascii(elem, &root);
		else if (elem->mtime > root->mtime)
		{
			root = root->left;
			if (!root)
				tmp->left = elem;
		}
		else
		{
			root = root->right;
			if (!root)
				tmp->right = elem;
		}
	}
}

void			add_node(t_file file, t_stat buf, t_lsopt opt, t_flist **list)
{
	t_flist *elem;

	if (!(elem = create_node(file, buf)))
		ls_error(1, NULL);
	if (*list)
	{
		if (opt.t)
			add_node_time(*list, elem);
		else
			add_node_ascii(*list, elem);
	}
	else
		*list = elem;
}

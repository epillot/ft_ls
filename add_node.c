/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:36:40 by epillot           #+#    #+#             */
/*   Updated: 2017/01/13 19:36:47 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		link_node_ascii_aux(t_flist *elem, t_flist **node)
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

static void		link_node_ascii(t_flist *root, t_flist *elem)
{

	while (root)
		link_node_ascii_aux(elem, &root);
}

static void		link_node_time(t_flist *root, t_flist *elem)
{
	t_flist	*tmp;

	while (root)
	{
		tmp = root;
		if (elem->mtime == root->mtime)
			link_node_ascii_aux(elem, &root);
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

static void		link_node(t_flist *root, t_flist *elem, t_lsopt opt)
{
	if (opt.t)
		link_node_time(root, elem);
	else
		link_node_ascii(root, elem);
}

void			add_node(t_file file, t_stat buf, t_lsopt opt, t_flist **list)
{
	t_flist *elem;

	if (!(elem = create_node(file, buf)))
		return ;
	if (*list)
		link_node(*list, elem, opt);
	else
		*list = elem;
}

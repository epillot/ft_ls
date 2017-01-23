/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:36:40 by epillot           #+#    #+#             */
/*   Updated: 2017/01/23 14:53:45 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static void		add_node_right(t_flist *root, t_flist *elem)
{
	t_flist	*tmp;

	while (root)
	{
		tmp = root;
		root = root->right;
		if (!root)
			tmp->right = elem;
	}
}

static void		add_node_time(t_flist *root, t_flist *elem)
{
	t_flist	*tmp;

	while (root)
	{
		tmp = root;
		if (elem->time_ref == root->time_ref)
			check_ascii(elem, &root);
		else if (elem->time_ref > root->time_ref)
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

static void		add_node_size(t_flist *root, t_flist *elem)
{
	t_flist	*tmp;

	while (root)
	{
		tmp = root;
		if (elem->size == root->size)
			check_ascii(elem, &root);
		else if (elem->size > root->size)
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
	t_flist	*tmp;

	if (!(elem = create_node(file, buf, opt)))
		ls_error(1, NULL, &opt);
	if (*list)
	{
		tmp = *list;
		if (opt.t)
			add_node_time(*list, elem);
		else if (opt.ss)
			add_node_size(*list, elem);
		else if (opt.f)
			add_node_right(*list, elem);
		else
		{
			while (tmp)
				check_ascii(elem, &tmp);
		}
	}
	else
		*list = elem;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:14:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 18:11:58 by epillot          ###   ########.fr       */
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
	while (tmp)
		link_node_file_name(elem, &tmp);
}

static void		link_node_time(t_flist *elem, t_flist **root)
{
	t_flist	*tmp1;
	t_flist	*tmp2;

	tmp1 = *root;
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

int				get_file_list2(char *file, t_stat buf, t_lsopt opt, t_flist **list)
{
	t_flist	*elem;

	if (!(elem = create_elem(file, buf)))
		return (0);
	if (*list)
	{
		if (opt.t == 1)
			link_node_time(elem, list);
		else
			link_node(elem, list);
	}
	else
		*list = elem;
	return (1);
}

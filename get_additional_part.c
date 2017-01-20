/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_additional_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:50:08 by epillot           #+#    #+#             */
/*   Updated: 2017/01/20 17:25:22 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_width(t_flist *list, int tab[7])
{
	int	size;

	if ((size = nb_size(list->nb_link)) > tab[0])
		tab[0] = size;
	if ((size = ft_strlen(list->usr_id)) > tab[1])
		tab[1] = size;
	if ((size = ft_strlen(list->grp_id)) > tab[2])
		tab[2] = size;
	if (S_ISCHR(list->mode))
	{
		if ((size = nb_size(major(list->rdev))) > tab[3])
			tab[3] = size;
		if ((size = nb_size(minor(list->rdev))) > tab[4])
			tab[4] = size;
	}
	else
	{
		if ((size = nb_size(list->size)) > tab[5])
			tab[5] = size;
	}
}

void		get_additional_part(t_flist *list, t_lsopt opt, int tab[7])
{
	if (!list)
		return ;
	if ((opt.f_print && !S_ISDIR(list->mode)) || opt.d_print)
	{
		get_long_info(list);
		get_width(list, tab);
		tab[6] += list->nb_blocks;
	}
	if (list->left)
		get_additional_part(list->left, opt, tab);
	if (list->right)
		get_additional_part(list->right, opt, tab);
}

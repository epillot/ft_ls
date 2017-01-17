/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_and_tot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:09:22 by epillot           #+#    #+#             */
/*   Updated: 2017/01/17 18:09:23 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_number_size(intmax_t nb)
{
	int ret;

	ret = 1;
	while (nb >= 10)
	{
		nb /= 10;
		ret++;
	}
	return (ret);
}

static void	get_width(t_flist *list, int tab[7])
{
	int	size;

	if ((size = get_number_size(list->nb_link)) > tab[0])
		tab[0] = size;
	if ((size = ft_strlen(list->usr_id)) > tab[1])
		tab[1] = size;
	if ((size = ft_strlen(list->grp_id)) > tab[2])
		tab[2] = size;
	if (S_ISCHR(list->mode))
	{
		if ((size = get_number_size(major(list->rdev))) > tab[3])
			tab[3] = size;
		if ((size = get_number_size(minor(list->rdev))) > tab[4])
			tab[4] = size;
	}
	else
		if ((size = get_number_size(list->size)) > tab[5]) 
			tab[5] = size;
}

void		get_width_and_tot(t_flist *list, t_lsopt opt, int tab[7])
{
	if (!list)
		return ;
	if ((opt.f_print && !S_ISDIR(list->mode)) || opt.d_print)
	{
		get_width(list, tab);
		tab[6] += list->nb_blocks;
		if (tab[3] != 0 && tab[4] != 0)
		{
			if (tab[5] > tab[3] + tab[4] + 2)
				tab[3] = tab[5] - tab[4] - 2;
			else
				tab[5] = tab[3] + tab[4] + 2;
		}
	}
	if (list->left)
		get_width_and_tot(list->left, opt, tab);
	if (list->right)
		get_width_and_tot(list->right, opt, tab);
}

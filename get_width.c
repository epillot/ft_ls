/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:27:17 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 18:28:32 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_number_size(uintmax_t nb)
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

static void	get_width_first_part(t_flist *list, int tab[6])
{
	int nb0;
	int nb1;
	int nb2;

	if (!list)
		return ;
	nb0 = get_number_size(list->nb_link) + 1;
	nb1 = ft_strlen(list->usr_id) + 1;
	nb2 = ft_strlen(list->grp_id) + 1;
	if (nb0 > tab[0])
		tab[0] = nb0;
	if (nb1 > tab[1])
		tab[1] = nb1;
	if (nb2 > tab[2])
		tab[2] = nb2;
	if (list->left)
		get_width_first_part(list->left, tab);
	if (list->right)
		get_width_first_part(list->right, tab);
}

static void	get_width_last_part(t_flist *list, int tab[6])
{
	int nb3;
	int nb4;
	int nb5;

	if (!list)
		return ;
	nb3 = get_number_size(major(list->rdev)) + 1;
	nb4 = get_number_size(minor(list->rdev)) + 1;
	nb5 = get_number_size(list->size);
	if (nb3 > tab[3])
		tab[3] = nb3;
	if (nb4 > tab[4])
		tab[4] = nb4;
	if (nb5 > tab[5])
		tab[5] = nb5;
	if (tab[3] + tab[4] + 1 > tab[5])
		tab[5] = tab[3] + tab[4] + 1;
	else
		tab[3] = tab[5] - tab[4] - 1;
	if (list->left)
		get_width_last_part(list->left, tab);
	if (list->right)
		get_width_last_part(list->right, tab);
}

void		get_width(t_flist *list, int tab[6])
{
	get_width_first_part(list, tab);
	get_width_last_part(list, tab);
}

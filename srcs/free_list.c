/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 15:29:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/18 18:47:32 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_list(t_flist **list)
{
	if (*list)
	{
		if ((*list)->left)
			free_list(&(*list)->left);
		if ((*list)->right)
			free_list(&(*list)->right);
		free((*list)->name);
		free((*list)->path);
		if ((*list)->usr_id)
			free((*list)->usr_id);
		if ((*list)->grp_id)
			free((*list)->grp_id);
		if ((*list)->time)
			free((*list)->time);
		free(*list);
		*list = NULL;
	}
}

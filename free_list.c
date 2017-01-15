/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 15:29:07 by epillot           #+#    #+#             */
/*   Updated: 2017/01/13 15:34:35 by epillot          ###   ########.fr       */
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
		free((*list)->usr_id);
		free((*list)->grp_id);
		free((*list)->time);
		free(*list);
		*list = NULL;
	}
}

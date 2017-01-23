/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 15:21:24 by epillot           #+#    #+#             */
/*   Updated: 2017/01/20 18:18:41 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flist		*create_node(t_file file, t_stat buf, t_lsopt opt)
{
	t_flist		*output;

	if (!(output = (t_flist*)ft_memalloc(sizeof(t_flist))))
		return (NULL);
	output->uid = buf.st_uid;
	output->gid = buf.st_gid;
	output->mode = buf.st_mode;
	output->nb_link = buf.st_nlink;
	output->size = buf.st_size;
	if (!opt.u && !opt.c && !opt.uu)
		output->time_ref = buf.st_mtime;
	else if (!opt.uu)
		output->time_ref = (opt.u ? buf.st_atime : buf.st_ctime);
	else
		output->time_ref = buf.st_birthtime;
	output->nb_blocks = buf.st_blocks;
	output->rdev = buf.st_rdev;
	if (!(output->name = ft_strdup(file.name)))
		return (NULL);
	if (!(output->path = ft_strdup(file.path)))
		return (NULL);
	return (output);
}

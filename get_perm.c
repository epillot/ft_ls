/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_perm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:25:20 by epillot           #+#    #+#             */
/*   Updated: 2017/01/10 14:32:47 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_type(mode_t st_mode)
{
	if (S_ISDIR(st_mode))
		return ('d');
	if (S_ISCHR(st_mode))
		return ('c');
	if (S_ISBLK(st_mode))
		return ('b');
	if (S_ISFIFO(st_mode))
		return ('p');
	if (S_ISLNK(st_mode))
		return ('l');
	if (S_ISSOCK(st_mode))
		return ('s');
	else
		return ('-');
}

void		get_perm(mode_t st_mode, char perm[11])
{
	perm[10] = '\0';
	perm[0] = get_type(st_mode);
	perm[1] = (st_mode & S_IRUSR ? 'r' : '-');
	perm[2] = (st_mode & S_IWUSR ? 'w' : '-');
	perm[3] = (st_mode & S_IXUSR ? 'x' : '-');
	perm[4] = (st_mode & S_IRGRP ? 'r' : '-');
	perm[5] = (st_mode & S_IWGRP ? 'w' : '-');
	perm[6] = (st_mode & S_IXGRP ? 'x' : '-');
	perm[7] = (st_mode & S_IROTH ? 'r' : '-');
	perm[8] = (st_mode & S_IWOTH ? 'w' : '-');
	perm[9] = (st_mode & S_IXOTH ? 'x' : '-');
	if (st_mode & S_ISUID)
		perm[3] = (perm[3] == 'x' ? 's' : 'S');
	if (st_mode & S_ISGID)
		perm[6] = (perm[6] == 'x' ? 's' : 'S');
	if (st_mode & S_ISVTX)
		perm[9] = (perm[9] == 'x' ? 't' : 'T');
}

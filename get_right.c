/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 17:06:04 by epillot           #+#    #+#             */
/*   Updated: 2017/01/06 17:41:36 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_type(mode_t st_mode)
{
	st_mode = (st_mode & S_IFMT);
	if (S_ISREG(st_mode))
		return ('-');
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
	return (0);
}

void		get_right(mode_t st_mode, char right[11])
{
	right[10] = '\0';
	right[0] = get_type(st_mode);
	right[1] = (st_mode & S_IRUSR ? 'r' : '-');
	right[2] = (st_mode & S_IWUSR ? 'w' : '-');
	right[3] = (st_mode & S_IXUSR ? 'x' : '-');
	right[4] = (st_mode & S_IRGRP ? 'r' : '-');
	right[5] = (st_mode & S_IWGRP ? 'w' : '-');
	right[6] = (st_mode & S_IXGRP ? 'x' : '-');
	right[7] = (st_mode & S_IROTH ? 'r' : '-');
	right[8] = (st_mode & S_IWOTH ? 'w' : '-');
	right[9] = (st_mode & S_IXOTH ? 'x' : '-');
}

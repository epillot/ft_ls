/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:18:34 by epillot           #+#    #+#             */
/*   Updated: 2017/01/13 19:29:09 by epillot          ###   ########.fr       */
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

static void	get_perm(mode_t st_mode, char perm[11])
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

static char	*get_time(time_t mtime)
{
	time_t	actual_time;
	char	*s_time;
	char	*output;

	time(&actual_time);
	s_time = ctime(&mtime);
	if (!(output = ft_strsub(s_time, 4, 12)))
		return (NULL);
	if (actual_time - mtime >= 15811200)
		ft_strncpy(output + 7, s_time + 19, 5);
	return (output);
}

t_flist		*create_node(t_file file, t_stat buf)
{
	t_flist		*output;
	t_passwd	*uid;
	t_group		*gid;

	if (!(output = (t_flist*)ft_memalloc(sizeof(t_flist))))
		return (NULL);
	if (!(uid = getpwuid(buf.st_uid)))
		return (NULL);
	if (!(gid = getgrgid(buf.st_gid)))
		return (NULL);
	get_perm(buf.st_mode, output->perm);
	output->mode = buf.st_mode;
	output->nb_link = buf.st_nlink;
	ft_strncpy(output->usr_id, uid->pw_name, NAME_MAX + 1);
	ft_strncpy(output->grp_id, gid->gr_name, NAME_MAX + 1);
	output->size = buf.st_size;
	output->mtime = buf.st_mtime;
	output->nb_blocks = buf.st_blocks;
	output->rdev = buf.st_rdev;
	if (!(output->time = get_time(buf.st_mtime)))
		return (NULL);
	ft_strncpy(output->file.name, file.name, NAME_MAX + 1);
	ft_strncpy(output->file.path, file.path, PATH_MAX);
	return (output);
}

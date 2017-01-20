/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:18:01 by epillot           #+#    #+#             */
/*   Updated: 2017/01/20 17:25:10 by epillot          ###   ########.fr       */
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

static char	*get_time(time_t time_ref)
{
	time_t	actual;
	char	*s_time;
	char	*output;
	char	*tmp;

	time(&actual);
	s_time = ctime(&time_ref);
	if (!(output = ft_strsub(s_time, 4, 12)))
		return (NULL);
	if (actual - time_ref > 15811200 || actual - time_ref < -3600)
	{
		if (time_ref <= 253402297199)
			ft_strncpy(output + 7, s_time + 19, 5);
		else
		{
			tmp = output;
			if (!(output = ft_strnew(13)))
				return (NULL);
			ft_strncpy(output, tmp, 7);
			output[7] = ' ';
			ft_strncpy(output + 8, s_time + 24, 5);
			free(tmp);
		}
	}
	return (output);
}

void		get_long_info(t_flist *list)
{
	t_passwd	*uid;
	t_group		*gid;

	if (!(gid = getgrgid(list->gid)))
		ls_error(1, NULL);
	if (!(uid = getpwuid(list->uid)))
		ls_error(1, NULL);
	get_perm(list->mode, list->perm);
	if (!(list->usr_id = ft_strdup(uid->pw_name)))
		ls_error(1, NULL);
	if (!(list->grp_id = ft_strdup(gid->gr_name)))
		ls_error(1, NULL);
	if (!(list->time = get_time(list->time_ref)))
		ls_error(1, NULL);
}

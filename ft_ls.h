/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 15:53:35 by epillot           #+#    #+#             */
/*   Updated: 2017/01/11 19:06:58 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# include <sys/types.h>
# include <dirent.h>
# include "libft/libft.h"
# include <stdio.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>
# include <limits.h>

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct group	t_group;
typedef struct passwd	t_passwd;

typedef struct	s_lsopt
{
	int		l;
	int		rec;
	int		a;
	int		r;
	int		t;
}				t_lsopt;

typedef struct	s_flist
{
	char				perm[11];
	nlink_t				nb_link;
	char				*usr_id;
	char				*grp_id;
	off_t				size;
	time_t				mtime;
	char				*time;
	char				file_name[256];
	blkcnt_t			nb_blocks;
	dev_t				rdev;
	struct s_flist		*right;
	struct s_flist		*left;
}				t_flist;

int						get_option_ls(int ac, char **av, t_lsopt *opt);
t_flist					*create_elem(char *file, t_stat buf);
int						get_file_list2(char *file, t_stat buf, t_lsopt opt, t_flist **list);
void					get_width(t_flist *list, int tab[6]);
void					print_content(t_flist *list, t_lsopt opt, char *str, int tab[6]);
void					print_file(t_flist *list, char *str, t_lsopt opt);
void					print_dir(t_flist *list, t_lsopt opt);
int						get_file_list(char *file, t_lsopt opt, t_flist **list);

#endif

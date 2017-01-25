/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 15:53:35 by epillot           #+#    #+#             */
/*   Updated: 2017/01/25 15:57:11 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# include <sys/types.h>
# include <dirent.h>
# include "libft.h"
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
	int					l;
	int					rec;
	int					a;
	int					aa;
	int					r;
	int					t;
	int					d;
	int					p;
	int					f;
	int					u;
	int					uu;
	int					c;
	int					ss;
	int					d_print;
	int					printed;
	int					error;
}				t_lsopt;

typedef struct	s_file
{
	char				name[NAME_MAX + 1];
	char				path[PATH_MAX];
}				t_file;

typedef struct	s_flist
{
	char				*name;
	char				*path;
	char				perm[11];
	mode_t				mode;
	nlink_t				nb_link;
	uid_t				uid;
	gid_t				gid;
	char				*usr_id;
	char				*grp_id;
	off_t				size;
	time_t				time_ref;
	char				*time;
	blkcnt_t			nb_blocks;
	dev_t				rdev;
	struct s_flist		*right;
	struct s_flist		*left;
}				t_flist;

int				get_option_ls(int ac, char **av, t_lsopt *opt);
t_flist			*create_node(t_file file, t_stat buf, t_lsopt opt);
void			add_node(t_file file, t_stat buf, t_lsopt opt, t_flist **list);
void			get_additional_part(t_flist *list, t_lsopt opt, int tab[7]);
void			get_flist(char *name, char *path, t_lsopt *opt, t_flist **list);
void			get_long_info(t_flist *list, t_lsopt *opt);
void			print_files(t_flist *list, t_lsopt *opt, int dir);
void			print_dir(t_flist *list, t_lsopt *opt, int size, int nb);
void			ls_error(int errnum, char *str, t_lsopt *opt);
void			free_list(t_flist **list);

#endif

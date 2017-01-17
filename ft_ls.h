/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 15:53:35 by epillot           #+#    #+#             */
/*   Updated: 2017/01/17 18:19:51 by epillot          ###   ########.fr       */
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
	int					l;
	int					rec;
	int					a;
	int					r;
	int					t;
	int					f_print;
	int					d_print;
	int					printed;
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
	char				*usr_id;//[NAME_MAX + 1];
	char				*grp_id;//[NAME_MAX + 1];
	off_t				size;
	time_t				mtime;
	char				*time;
//	char				file_name[NAME_MAX + 1];
//	char				path[PATH_MAX];
	blkcnt_t			nb_blocks;
	dev_t				rdev;
	struct s_flist		*right;
	struct s_flist		*left;
}				t_flist;

int						get_option_ls(int ac, char **av, t_lsopt *opt);
t_flist					*create_node(t_file file, t_stat buf);
void					add_node(t_file file, t_stat buf, t_lsopt opt, t_flist **list);
void					get_width_and_tot(t_flist *list, t_lsopt opt, int tab[7]);
int						get_file_list(char *name, char *path, t_lsopt opt, t_flist **list);
void					print_content(t_flist *list, t_lsopt opt, int tab[7]);
void					print_file(t_flist *list, t_lsopt *opt, int dir);
void					print_dir(t_flist *list, t_lsopt *opt, int size, int nb);
void					print_dir_content(t_flist *list, t_lsopt *opt, int size);
void					ls_error(int errnum, char *str);
void					free_list(t_flist **list);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/26 04:47:15 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:54:05 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <errno.h>
# include <wchar.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>

# include "libft.h"
# include "colors.h"
# include "error.h"

typedef enum		e_which_sort
{
	A_TIME,
	M_TIME,
	C_TIME,
	S_SIZE,
}					t_which_sort;

typedef struct		s_params
{
	int				all;
	int				one;
	int				list;
	int				colors;
	int				param_a;
	int				param_p;
	int				reverse;
	int				no_user;
	int				no_group;
	int				recursive;
	int				human_read;
	unsigned short	term_width;
	t_colors		*colors_tab;
	int				time_to_sort;
	int				time_modification;
}					t_params;

typedef struct		s_file
{
	char			*filename;
	char			*path;
	struct stat		sb;
}					t_file;

typedef struct		s_env
{
	unsigned long	blks;
	int				max_lnk;
	int				max_usr;
	int				max_grp;
	int				max_siz;
	int				max_maj;
	int				max_min;
}					t_env;

/*
** main.c
*/
void				display_normal(t_dlist *dir_files, t_params *p);
void				if_forest_params(t_dlist **list, t_dlist *link,
	t_params *p, int total);
void				files_first_ladies(t_dlist *files, t_params *p);
void				get_linked_lists(t_dlist **dirs_to_open, t_params *p,
	int ac, char **av);

/*
** set_params.c
*/
int					set_params2(char c, t_params *params);
void				set_params(char c, t_params *params);
int					search_params(int ac, char **av, t_params *params);
void				link_point_dir(t_dlist **dirs, t_dlist **params_files,
	char *file);
t_dlist				*get_dirs_to_open(char **av, int ac, t_dlist **params_file,
	int i);

/*
** make_dlist_files.c
*/
char				*path_file(char *path, char *file, int er);
void				get_da_list(t_dlist **list, t_params *params, char *av);
void				insert_sort(char *str, t_dlist **list, char *path);

/*
** get_data.c
*/
char				get_filetype(mode_t st_mode);
char				*ret_last_time_modif(time_t epoch_time);
char				*ret_last_time_modif2(char *month, char *day, char *hour);
char				*ret_group_owner(gid_t st_gid);
char				*ret_user_owner(uid_t st_uid);

/*
** get_data2.c
*/
void				get_rights(t_file *d);
void				get_rights2(t_file *d);
int					extended_attribut(char *path, int mode);

/*
** colors.c
*/
char				*translate_partone(int oct, int mode);
char				*translate_parttwo(int oct, int mode);
void				translate_colors(t_colors *c);
void				choose_col(char type, t_colors *c);

/*
** colors2.c
*/
t_colors			*get_env_colors(void);
void				init_colors(t_colors *colors);
void				color_plz(t_file *d, t_colors *c);

/*
** recurs_n_sort.c
*/
time_t				choose_time_sort(t_file *file, int mode);
void				add_dirs_to_open(t_dlist *dir_files, t_dlist **dirs_to_open,
	t_params *p);
t_dlist				*sort_modif_time(t_dlist **list, int mode);
void				sort_params_dirs(t_dlist **list);

/*
** long_listingf.c
*/
void				print_total_blks(t_dlist *dirs_files, int m, t_env *e);
void				display_info(t_dlist *dir_files, t_params *p, int m);
void				print_size_format(t_file *d, t_env *e, t_params *p);
void				print_device_format(t_file *d, t_env *e);
void				first_part_of_print(t_file *d, t_env *e, t_params *p);

/*
** long_listingf2.c
*/
t_env				*init_env(void);
void				print_real_path_symlink(char *path);
void				maxlen_device(t_file *data, t_env *e);
t_env				*blksize_and_lenght(t_dlist *files, t_params *p);

/*
** misc.c
*/
void				del_struct(void *ptr, size_t size);
int					is_parent_or_cur(char *str);
void				init_struct(t_params *p);
void				ft_print_n_spaces(int nb);
void				ft_print_twostr(char *str, char *str2);

/*
** error.c
*/
void				error2(int er, char *str);
void				error(int er, char *str);

#endif

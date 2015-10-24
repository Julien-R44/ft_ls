/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_listingf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 01:12:07 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:57:25 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_total_blks(t_dlist *dir_files, int m, t_env *e)
{
	if (m == 1 && dir_files)
	{
		ft_putstr("total ");
		ft_putnbr(e->blks);
		ft_putchar('\n');
	}
}

void		display_info(t_dlist *dir_files, t_params *p, int m)
{
	t_dlist	*nav;
	t_file	*d;
	t_env	*e;

	nav = dir_files;
	e = blksize_and_lenght(dir_files, p);
	print_total_blks(dir_files, m, e);
	while (nav)
	{
		d = nav->content;
		first_part_of_print(d, e, p);
		if (S_ISDIR(d->sb.st_mode) && p->param_p == 1)
			d->filename = ft_strjoin(d->filename, "/");
		if (p->colors)
			color_plz(d, p->colors_tab);
		else
			ft_putstr(d->filename);
		if (S_ISLNK(d->sb.st_mode))
			print_real_path_symlink(d->path);
		ft_putchar('\n');
		nav = nav->next;
	}
}

void		print_device_format(t_file *d, t_env *e)
{
	int		lenght;

	lenght = ((e->max_grp + e->max_maj) -
		(ft_strlen(ret_group_owner(d->sb.st_gid)) +
			ft_intlen(major(d->sb.st_rdev))) + 2);
	ft_print_n_spaces(lenght);
	ft_putnbr(major(d->sb.st_rdev));
	ft_putstr(",");
	lenght = (e->max_min - ft_intlen(minor(d->sb.st_rdev)) + 1);
	ft_print_n_spaces(lenght);
	ft_putnbr(minor(d->sb.st_rdev));
}

void		print_size_format(t_file *d, t_env *e, t_params *p)
{
	int lenght;

	if (e->max_maj || e->max_min)
	{
		ft_print_n_spaces((e->max_grp + e->max_maj + e->max_min) -
			(ft_intlen(d->sb.st_size)));
	}
	else
	{
		lenght = ((e->max_grp + e->max_siz) -
			(ft_strlen(ret_group_owner(d->sb.st_gid)) +
				ft_intlen(d->sb.st_size)) + 2);
		if (p->no_group == 1)
			lenght += ft_strlen(ret_group_owner(d->sb.st_gid)) - 2;
		ft_print_n_spaces(lenght);
	}
	ft_putnbr(d->sb.st_size);
}

void		first_part_of_print(t_file *d, t_env *e, t_params *p)
{
	int		lenght;
	char	*date;
	char	*tmp;

	tmp = ret_user_owner(d->sb.st_uid);
	date = ret_last_time_modif(choose_time_sort(d, p->time_to_sort));
	ft_putchar(get_filetype(d->sb.st_mode));
	get_rights(d);
	ft_print_n_spaces(e->max_lnk - ft_intlen(d->sb.st_nlink) + 1);
	ft_putnbr(d->sb.st_nlink);
	ft_putchar(' ');
	if (p->no_user == 0)
	{
		ft_putstr(tmp);
		ft_print_n_spaces(e->max_usr - ft_strlen(tmp) + 2);
	}
	if (p->no_group == 0)
		ft_putstr(ret_group_owner(d->sb.st_gid));
	if (S_ISBLK(d->sb.st_mode) || S_ISCHR(d->sb.st_mode))
		print_device_format(d, e);
	else
		print_size_format(d, e, p);
	ft_print_twostr(" ", date);
	ft_putchar(' ');
	ft_strdel(&date);
}

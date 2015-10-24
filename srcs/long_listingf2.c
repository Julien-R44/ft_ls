/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_listingf2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 01:12:07 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:57:25 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define BUFF_SIZE 84

t_env		*init_env(void)
{
	t_env *e;

	if ((e = ft_memalloc(sizeof(t_env))) == NULL)
		return (NULL);
	e->blks = 0;
	e->max_lnk = 0;
	e->max_usr = 0;
	e->max_siz = 0;
	e->max_maj = 0;
	e->max_min = 0;
	return (e);
}

void		print_real_path_symlink(char *path)
{
	char	*buf;
	int		ret;

	buf = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE + 1);
	if (!buf)
		return ;
	if ((ret = readlink(path, buf, BUFF_SIZE)) == -1)
		error(-1, NULL);
	buf[BUFF_SIZE + 1] = '\0';
	ft_print_twostr(" -> ", buf);
	free(buf);
}

void		maxlen_device(t_file *data, t_env *e)
{
	int tmp;

	if (S_ISBLK(data->sb.st_mode) || S_ISCHR(data->sb.st_mode))
	{
		tmp = ft_intlen(major(data->sb.st_rdev));
		e->max_maj = (tmp > e->max_maj) ? tmp : e->max_maj;
		tmp = ft_intlen(minor(data->sb.st_rdev));
		e->max_min = (tmp > e->max_min) ? tmp : e->max_min;
	}
}

t_env		*blksize_and_lenght(t_dlist *files, t_params *p)
{
	t_env	*e;
	t_file	*data;
	int		tmp;

	e = init_env();
	while (files)
	{
		data = files->content;
		e->blks += data->sb.st_blocks;
		tmp = ft_intlen(data->sb.st_nlink);
		e->max_lnk = (tmp > e->max_lnk) ? tmp : e->max_lnk;
		tmp = ft_strlen(ret_user_owner(data->sb.st_uid));
		e->max_usr = (tmp > e->max_usr) ? tmp : e->max_usr;
		tmp = ft_strlen(ret_group_owner(data->sb.st_gid));
		e->max_grp = (tmp > e->max_grp) ? tmp : e->max_grp;
		tmp = ft_intlen(data->sb.st_size);
		e->max_siz = (tmp > e->max_siz) ? tmp : e->max_siz;
		maxlen_device(data, e);
		files = files->next;
	}
	if (p->no_group == 1)
		e->max_grp = 0;
	if (p->no_user == 1)
		e->max_usr = 0;
	return (e);
}

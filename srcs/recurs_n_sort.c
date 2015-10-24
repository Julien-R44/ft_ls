/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs_n_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 05:06:07 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/04 02:46:42 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_dirs_to_open(t_dlist *dir_files, t_dlist **dir2open, t_params *p)
{
	t_file	*d;
	t_dlist	*nav;
	t_dlist	*tmp;
	char	*newpath;

	nav = dir_files;
	tmp = NULL;
	while (nav)
	{
		d = nav->content;
		if (get_filetype(d->sb.st_mode) == 'd'
			&& is_parent_or_cur(d->filename) == 0)
		{
			newpath = path_file((char*)(*dir2open)->content, d->filename, 1);
			ft_dlstadd_end(&tmp, ft_dlstnew(newpath, ft_strlen(newpath) + 1));
		}
		nav = nav->next;
	}
	ft_dlst_insert(dir2open, tmp);
}

time_t	choose_time_sort(t_file *file, int mode)
{
	if (mode == A_TIME)
		return (file->sb.st_atime);
	if (mode == M_TIME)
		return (file->sb.st_mtime);
	if (mode == C_TIME)
		return (file->sb.st_ctime);
	if (mode == S_SIZE)
		return (file->sb.st_size);
}

void	sort_modif_time2(t_dlist **list, t_dlist *link, int m)
{
	int		len;
	t_dlist *nav;

	len = ft_dlstlen(*list);
	nav = ft_dlstlast(*list);
	while (len > 0)
	{
		if (choose_time_sort(nav->content, m)
			>= choose_time_sort(link->content, m))
		{
			while (nav && choose_time_sort(nav->content, m) ==
				choose_time_sort(link->content, m) && ft_strcmp(
					((t_file *)nav->content)->filename,
					((t_file *)link->content)->filename) > 0)
			{
				len--;
				nav = nav->before;
			}
			break ;
		}
		nav = nav->before;
		len--;
	}
	ft_dlstadd_i(list, ft_dlstnew(link->content, sizeof(t_file)), len);
}

t_dlist	*sort_modif_time(t_dlist **list, int mode)
{
	t_dlist *newlist;
	t_dlist *nav;

	nav = *list;
	newlist = NULL;
	while (nav)
	{
		sort_modif_time2(&newlist, nav, mode);
		nav = nav->next;
	}
	nav = newlist;
	return (newlist);
}

void	sort_params_dirs(t_dlist **list)
{
	t_dlist	*ins;
	char	*elem;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = ft_dlstlen(*list);
	while (i < len)
	{
		j = i;
		ins = ft_dlstati(*list, i + 1);
		elem = ins->content;
		while (j > 0 && ft_strcmp(ins->before->content, elem) > 0)
		{
			ft_swap_contents(&ins, &ins->before);
			ins = ins->before;
			j--;
		}
		i++;
	}
}

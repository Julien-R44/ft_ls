/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_dlist_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 00:18:24 by y0ja              #+#    #+#             */
/*   Updated: 2014/12/31 09:33:54 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

typedef struct dirent	t_dirent;

char		*path_file(char *path, char *file, int er)
{
	int				i;
	char			*str;

	str = NULL;
	i = ft_strlen(path);
	if (path[i] != '/')
	{
		if (er == 1 && ft_strequ(path, "../") == 1)
			str = ft_strdup(path);
		else
			str = ft_strjoin(path, "/");
	}
	path = ft_strjoin(str, file);
	ft_strdel(&str);
	return (path);
}

void		insert_sort(char *da_file, t_dlist **files, char *path)
{
	int				len;
	t_dlist			*nav;
	t_file			data;

	len = ft_dlstlen(*files);
	nav = ft_dlstlast(*files);
	data.filename = ft_strdup(da_file);
	if (path == NULL)
		data.path = data.filename;
	else
		data.path = path_file(path, da_file, 0);
	if (lstat(data.path, &data.sb) == -1)
		error(BAD_PATH, data.path);
	while (len > 0)
	{
		if (ft_strcmp(((t_file *)nav->content)->filename, da_file) < 0)
			break ;
		nav = nav->before;
		len--;
	}
	ft_dlstadd_i(files, ft_dlstnew(&data, sizeof(t_file)), len);
}

void		get_da_list(t_dlist **files, t_params *params, char *dir2open)
{
	DIR			*dir;
	t_dirent	*dirent;

	if ((dir = opendir(dir2open)) == NULL)
	{
		error(BAD_PATH_NO_EXIT, dir2open);
		return ;
	}
	while ((dirent = readdir(dir)) != NULL)
	{
		if (params->param_a == 0 && params->all == 0
			&& ft_strncmp(dirent->d_name, ".", 1) == 0)
			;
		else
		{
			if (params->param_a == 1
				&& is_parent_or_cur(dirent->d_name) == 1 && params->all == 0)
				;
			else
				insert_sort(dirent->d_name, files, dir2open);
		}
	}
	if (closedir(dir) == -1)
		error(-1, NULL);
}

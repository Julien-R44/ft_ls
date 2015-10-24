/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/26 04:47:32 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 06:05:39 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		set_params2(char c, t_params *params)
{
	int i;

	i = 0;
	if (c == 'l' || c == 'g' || c == 'o')
	{
		if (c == 'g')
			params->no_group = 1;
		else if (c == 'o')
			params->no_user = 1;
		params->list = 1;
		i++;
	}
	else if (c == 't' || c == 'u' || c == 'c' || c == 'S')
	{
		if (c == 'u')
			params->time_to_sort = A_TIME;
		else if (c == 'c')
			params->time_to_sort = C_TIME;
		else if (c == 'S')
			params->time_to_sort = S_SIZE;
		params->time_modification = 1;
		i++;
	}
	return (i);
}

void	set_params(char c, t_params *params)
{
	if (c == 'R')
		params->recursive = 1;
	else if (c == 'a')
		params->all = 1;
	else if (c == 'r')
		params->reverse = 1;
	else if (c == '1')
		params->one = 1;
	else if (c == 'G')
		params->colors = 1;
	else if (c == 'p')
		params->param_p = 1;
	else if (c == 'A')
		params->param_a = 1;
	else if (c == 'h')
		params->human_read = 1;
	else
	{
		if (set_params2(c, params) == 0)
			error(BAD_OPT, &c);
	}
}

int		search_params(int ac, char **av, t_params *params)
{
	int		i;
	int		j;

	j = 1;
	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--") || ft_strequ(av[i], "-"))
		{
			if (ft_strequ(av[i], "--"))
				i++;
			return (i);
		}
		while (av[i][j])
		{
			set_params(av[i][j], params);
			j++;
		}
		j = 1;
		i++;
	}
	return (i);
}

void	link_point_dir(t_dlist **dirs, t_dlist **params_files, char *file)
{
	struct stat	sb;
	char		*str;
	int			len;

	len = ft_strlen(file);
	if (file[len - 1] != '/')
		str = ft_strjoin(file, "/");
	if (lstat(str, &sb) == -1)
	{
		ft_dlstadd_end(params_files, ft_dlstnew(file, ft_strlen(file) + 1));
		return ;
	}
	if (S_ISDIR(sb.st_mode) && extended_attribut(str, 0) == 0)
		ft_dlstadd_end(dirs, ft_dlstnew(str, ft_strlen(str) + 1));
	else
		ft_dlstadd_end(params_files, ft_dlstnew(file, ft_strlen(file) + 1));
}

t_dlist	*get_dirs_to_open(char **av, int ac, t_dlist **params_files, int i)
{
	t_dlist		*dirs;
	struct stat	sb;
	int			j;

	j = i;
	dirs = NULL;
	while (i < ac)
	{
		if (lstat(av[i], &sb) == -1)
			error(BAD_PATH_NO_EXIT, av[i]);
		else
		{
			if (S_ISLNK(sb.st_mode))
				link_point_dir(&dirs, params_files, av[i]);
			else if (S_ISDIR(sb.st_mode))
				ft_dlstadd_end(&dirs, ft_dlstnew(av[i], ft_strlen(av[i]) + 1));
			else
				ft_dlstadd_end(params_files, ft_dlstnew(av[i],
					ft_strlen(av[i]) + 1));
		}
		i++;
	}
	if (dirs == NULL && *params_files == NULL && j == i)
		ft_dlstadd_end(&dirs, ft_dlstnew(".", sizeof(char) * 2));
	return (dirs);
}

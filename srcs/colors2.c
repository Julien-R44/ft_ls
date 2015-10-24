/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 05:04:54 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/03 22:49:58 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		color_plz(t_file *d, t_colors *c)
{
	if (get_filetype(d->sb.st_mode) == 'd')
		choose_col(DIREC, c);
	else if (get_filetype(d->sb.st_mode) == 'l')
		choose_col(SYM, c);
	else if (get_filetype(d->sb.st_mode) == 's')
		choose_col(SOC, c);
	else if (get_filetype(d->sb.st_mode) == 'p')
		choose_col(PIP, c);
	else if (get_filetype(d->sb.st_mode) == '-')
	{
		if (S_IXUSR & d->sb.st_mode)
		{
			if (S_ISUID & d->sb.st_mode)
				choose_col(EXEC_SETUID, c);
			else if (S_ISGID & d->sb.st_mode)
				choose_col(EXEC_SETGID, c);
			else
				choose_col(EXE, c);
		}
	}
	else if (get_filetype(d->sb.st_mode) == 'b')
		choose_col(BDEV, c);
	else if (get_filetype(d->sb.st_mode) == 'c')
		choose_col(CDEV, c);
	ft_print_twostr(d->filename, RESET);
}

void		init_colors(t_colors *colors)
{
	int i;

	i = 0;
	while (i <= 11)
	{
		colors[i].foreground = 'x';
		colors[i].background = 'x';
		i++;
	}
}

t_colors	*get_env_colors(void)
{
	t_colors		*colors;
	char			*ret;
	int				i;
	int				j;

	i = 0;
	j = 0;
	colors = (t_colors *)ft_memalloc(sizeof(t_colors) * 11 + 1);
	if (!colors)
		return (NULL);
	init_colors(colors);
	ret = getenv("LSCOLORS");
	while (ret[i])
	{
		colors[j].foreground = ret[i];
		colors[j].background = ret[i + 1];
		i += 2;
		j++;
	}
	if (i != 22)
		error(INVALID_LSCOLORS, ret);
	return (colors);
}

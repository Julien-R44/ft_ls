/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:55:27 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:55:39 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		extended_attribut(char *path, int mode)
{
	int ret;

	ret = 0;
	ret = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (mode == 1)
	{
		if (ret > 0)
			ft_putchar('@');
		else
			ft_putchar(' ');
	}
	else
	{
		if (ret >= 0 && path[0] == '/')
			return (1);
	}
	return (0);
}

void	get_rights2(t_file *d)
{
	(d->sb.st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(d->sb.st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	if ((d->sb.st_mode & S_ISVTX)
		&& (!(d->sb.st_mode & S_IWOTH)) && (!(d->sb.st_mode & S_IROTH)))
		ft_putchar('T');
	else if (d->sb.st_mode & S_ISVTX)
		ft_putchar('t');
	else
		(d->sb.st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	extended_attribut(d->path, 1);
}

void	get_rights(t_file *d)
{
	(d->sb.st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(d->sb.st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	if ((d->sb.st_mode & S_ISUID) &&
		(!(d->sb.st_mode & S_IWUSR)) && (!(d->sb.st_mode & S_IRUSR)))
		ft_putchar('S');
	else if (d->sb.st_mode & S_ISUID)
		ft_putchar('s');
	else
		(d->sb.st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(d->sb.st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(d->sb.st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	if ((d->sb.st_mode & S_ISGID)
		&& (!(d->sb.st_mode & S_IWGRP)) && (!(d->sb.st_mode & S_IRGRP)))
		ft_putchar('S');
	else if (d->sb.st_mode & S_ISGID)
		ft_putchar('s');
	else
		(d->sb.st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	get_rights2(d);
}

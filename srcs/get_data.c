/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:55:27 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:55:39 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	get_filetype(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	return (0);
}

char	*ret_last_time_modif2(char *month, char *day, char *hour)
{
	char	*res;
	int		lenght;

	lenght = ((ft_strlen(month) + 2) + (ft_strlen(day) + 1) +
		(ft_strlen(hour) + 1));
	res = (char *)ft_memalloc(sizeof(char) * lenght + 1);
	if (!res)
		error(-1, NULL);
	ft_strcpy(res, month);
	ft_strcat(res, day);
	ft_strcat(res, " ");
	ft_strcat(res, hour);
	ft_strdel(&month);
	ft_strdel(&day);
	ft_strdel(&hour);
	return (res);
}

char	*ret_last_time_modif(time_t epoch_time)
{
	char	*date;
	char	*hour;
	char	*month;
	char	*day;

	if ((date = ctime(&epoch_time)) == NULL)
		error(-1, NULL);
	month = ft_strsub(date, 4, 4);
	day = ft_strsub(date, 8, 2);
	if ((time(NULL) - epoch_time) >= (31556926 / 2) || epoch_time > time(NULL))
		hour = ft_strsub(date, 19, 5);
	else
		hour = ft_strsub(date, 11, 5);
	return (ret_last_time_modif2(month, day, hour));
}

char	*ret_group_owner(gid_t st_gid)
{
	struct group	*gb;

	gb = getgrgid(st_gid);
	if (gb == NULL)
		return (ft_itoa(st_gid));
	return (gb->gr_name);
}

char	*ret_user_owner(uid_t st_uid)
{
	struct passwd	*pb;

	pb = getpwuid(st_uid);
	if (pb == NULL)
		return (ft_itoa(st_uid));
	return (pb->pw_name);
}

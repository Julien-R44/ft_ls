/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 03:55:27 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:55:39 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error2(int er, char *str)
{
	ft_putstr_fd("error: ", 2);
	perror(str);
}

void	error(int er, char *str)
{
	if (er == -1)
		error2(er, str);
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		if (er == BAD_OPT)
		{
			ft_putstr_fd("invalid option -- '", 2);
			ft_putchar_fd(str[0], 2);
			ft_putstr_fd("'\nusage: ft_ls [-alRhrtucGogpA1] [file ...]\n", 2);
			exit(-1);
		}
		ft_putstr_fd(str, 2);
		if (errno == 13)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (er == BAD_PATH || er == BAD_PATH_NO_EXIT)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (er == INVALID_LSCOLORS)
			ft_putstr_fd(": Invalid LSCOLORS var. Default colors set.", 2);
	}
	if (er != BAD_PATH_NO_EXIT && er != INVALID_LSCOLORS)
		exit(-1);
}

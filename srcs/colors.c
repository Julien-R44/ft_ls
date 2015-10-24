/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 05:04:54 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/03 22:49:58 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ret_back_or_fore(char *fore, char *back, int mode)
{
	if (mode == 1)
		return (fore);
	return (back);
}

char		*translate_partone(int oct, int mode)
{
	if (oct == 'x')
		return (DEFAULT);
	else if (oct == 'a')
		return (ret_back_or_fore(BLACK, BLACK_B, mode));
	else if (oct == 'b')
		return (ret_back_or_fore(RED, RED_B, mode));
	else if (oct == 'c')
		return (ret_back_or_fore(GREEN, GREEN_B, mode));
	else if (oct == 'd')
		return (ret_back_or_fore(BROWN, BROWN_B, mode));
	else if (oct == 'e')
		return (ret_back_or_fore(BLUE, BLUE_B, mode));
	else if (oct == 'f')
		return (ret_back_or_fore(MAGENTA, MAGENTA_B, mode));
	else if (oct == 'g')
		return (ret_back_or_fore(CYAN, CYAN_B, mode));
	else if (oct == 'h')
		return (ret_back_or_fore(LIGHT_GREY, LIGHT_GREY_B, mode));
	return (translate_parttwo(oct, mode));
}

char		*translate_parttwo(int oct, int mode)
{
	if (oct == 'A')
		return (ret_back_or_fore(BOLD_BLACK, BOLD_BLACK_B, mode));
	else if (oct == 'B')
		return (ret_back_or_fore(BOLD_RED, BOLD_RED_B, mode));
	else if (oct == 'C')
		return (ret_back_or_fore(BOLD_GREEN, BOLD_GREEN_B, mode));
	else if (oct == 'D')
		return (ret_back_or_fore(BOLD_BROWN, BOLD_BROWN_B, mode));
	else if (oct == 'E')
		return (ret_back_or_fore(BOLD_BLUE, BOLD_BLUE_B, mode));
	else if (oct == 'F')
		return (ret_back_or_fore(BOLD_MAGENTA, BOLD_MAGENTA_B, mode));
	else if (oct == 'G')
		return (ret_back_or_fore(BOLD_CYAN, BOLD_CYAN_B, mode));
	else if (oct == 'H')
		return (ret_back_or_fore(BOLD_LIGHT_GREY, BOLD_LIGHT_GREY_B, mode));
	ft_putstr("ERROR LS COLORS, EXIT...");
	exit(-1);
}

void		translate_colors(t_colors *c)
{
	char *back;

	ft_putstr(translate_partone(c->foreground, 1));
	if (c->background != 'x')
		ft_putstr(translate_partone(c->background, 2));
}

void		choose_col(char type, t_colors *c)
{
	translate_colors(&c[type]);
}

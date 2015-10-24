/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/26 04:47:15 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:54:05 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/*
** Foreground
*/

# define RED 				"\e[31m"
# define BLUE 				"\e[34m"
# define CYAN  				"\e[36m"
# define BLACK 				"\e[30m"
# define GREEN  			"\e[32m"
# define BROWN				"\e[0;33m"
# define DEFAULT 			"\e[39m"
# define MAGENTA 			"\e[35m"
# define BOLD_RED  			"\e[1;31m"
# define BOLD_BLUE  		"\e[1;34m"
# define BOLD_CYAN  		"\e[1;36m"
# define LIGHT_GREY 		"\e[37m"
# define BOLD_BLACK 		"\e[1;30m"
# define BOLD_GREEN  		"\e[1;32m"
# define BOLD_BROWN			"\e[0;1;33m"
# define BOLD_DEFAULT 		"\e[1;39m"
# define BOLD_MAGENTA 		"\e[1;35m"
# define BOLD_LIGHT_GREY 	"\e[1;37m"

/*
** Background
*/

# define RED_B  			"\e[41m"
# define BLUE_B 			"\e[44m"
# define CYAN_B 			"\e[46m"
# define BLACK_B			"\e[40m"
# define GREEN_B 			"\e[42m"
# define BROWN_B			"\e[0;43m"
# define DEFAULT_B 			"\e[49m"
# define MAGENTA_B 			"\e[45m"
# define BOLD_RED_B 		"\e[1;41m"
# define BOLD_BLUE_B 		"\e[1;44m"
# define BOLD_CYAN_B 		"\e[1;46m"
# define LIGHT_GREY_B		"\e[47m"
# define BOLD_BLACK_B		"\e[1;40m"
# define BOLD_GREEN_B  		"\e[1;42m"
# define BOLD_BROWN_B		"\e[0;1;43m"
# define BOLD_DEFAULT_B 	"\e[1;49m"
# define BOLD_MAGENTA_B 	"\e[1;45m"
# define BOLD_LIGHT_GREY_B	"\e[1;47m"

# define RESET 				"\033[0m"

typedef struct	s_colors
{
	int			foreground;
	int			background;
}				t_colors;

typedef enum	e_typecolors
{
	DIREC = 0,
	SYM,
	SOC,
	PIP,
	EXE,
	BDEV,
	CDEV,
	EXEC_SETUID,
	EXEC_SETGID,
	DIR_WRIT_ALLOWED_STICKYBIT,
	DIR_WRIT_ALLOWD_WITHOUT_STICKYBIT,
}				t_typecolors;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/26 04:47:15 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/15 05:54:05 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_errors
{
	BAD_OPT = 0,
	BAD_PATH,
	BAD_PATH_NO_EXIT,
	INVALID_LSCOLORS,
}				t_error;

#endif

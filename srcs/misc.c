/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 02:56:46 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/04 13:41:31 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_struct(void *ptr, size_t size)
{
	t_file *d;

	d = (t_file *)ptr;
	free(d->filename);
	free(d->path);
}

int		is_parent_or_cur(char *str)
{
	if (ft_strcmp(str, "..") == 0 || ft_strcmp(str, ".") == 0)
		return (1);
	return (0);
}

void	init_struct(t_params *p)
{
	p->human_read = 0;
	p->no_group = 0;
	p->no_user = 0;
	p->term_width = 0;
	p->param_a = 0;
	p->param_p = 0;
	p->colors = 0;
	p->list = 0;
	p->recursive = 0;
	p->all = 0;
	p->reverse = 0;
	p->time_modification = 0;
	p->time_to_sort = M_TIME;
	p->one = 0;
}

void	ft_print_n_spaces(int nb)
{
	while (nb--)
		ft_putchar(' ');
}

void	ft_print_twostr(char *str, char *str2)
{
	ft_putstr(str);
	ft_putstr(str2);
}

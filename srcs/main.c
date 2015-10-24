/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 02:44:53 by y0ja              #+#    #+#             */
/*   Updated: 2015/01/07 18:12:24 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_normal(t_dlist *dir_files, t_params *p)
{
	t_dlist	*nav;
	t_file	*d;

	nav = dir_files;
	while (nav)
	{
		d = nav->content;
		if (S_ISDIR(d->sb.st_mode) && p->param_p == 1)
			d->filename = ft_strjoin(d->filename, "/");
		if (p->colors)
			color_plz(d, p->colors_tab);
		else
			ft_putstr(d->filename);
		ft_putchar('\n');
		nav = nav->next;
	}
}

void	if_forest_params(t_dlist **list, t_dlist *link, t_params *p, int total)
{
	t_dlist *new_list;

	new_list = NULL;
	if (p->time_modification)
		*list = sort_modif_time(list, p->time_to_sort);
	if (p->reverse)
		ft_dlstrev(list);
	if (p->recursive && total == 1)
		add_dirs_to_open(*list, &link, p);
	if (p->list)
		display_info(*list, p, total);
	else
		display_normal(*list, p);
}

void	files_first_ladies(t_dlist *files, t_params *p)
{
	t_dlist *sorted_files;
	t_dlist *nav;

	if (!files)
		return ;
	nav = files;
	sorted_files = NULL;
	while (nav)
	{
		insert_sort(nav->content, &sorted_files, NULL);
		nav = nav->next;
	}
	if_forest_params(&sorted_files, NULL, p, 0);
}

void	get_linked_lists(t_dlist **dirs_to_open, t_params *p, int ac, char **av)
{
	t_dlist		*params_files;

	params_files = NULL;
	*dirs_to_open = get_dirs_to_open(av, ac, &params_files,
		search_params(ac, av, p));
	if (p->colors)
		p->colors_tab = get_env_colors();
	files_first_ladies(params_files, p);
	if (*dirs_to_open && params_files)
		ft_putchar('\n');
	if (ft_dlstlen(*dirs_to_open) > 1)
		sort_params_dirs(dirs_to_open);
	if (params_files)
		ft_dlstdel(&params_files, NULL);
}

int		main(int ac, char **av)
{
	t_params	p;
	t_dlist		*dirs_to_open;
	t_dlist		*nav;
	t_dlist		*dir_files;
	t_colors	*colors;

	dir_files = NULL;
	init_struct(&p);
	get_linked_lists(&dirs_to_open, &p, ac, av);
	nav = dirs_to_open;
	while (nav)
	{
		if (nav->before != NULL || nav->next != NULL)
			ft_print_twostr(nav->content, ":\n");
		get_da_list(&dir_files, &p, nav->content);
		if_forest_params(&dir_files, nav, &p, 1);
		ft_dlstdel(&dir_files, del_struct);
		if (nav->next)
			ft_putchar('\n');
		nav = nav->next;
	}
	ft_dlstdel(&nav, NULL);
	if (p.colors)
		free(p.colors_tab);
	return (0);
}

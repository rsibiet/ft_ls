/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:58:08 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/19 18:53:26 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recall_rd_files(DIR *rep, t_data d, int i, char ***dir)
{
	ft_putchar('\n');
	ft_putstr(dir[1][i]);
	ft_putendl(":");
	if ((rep = opendir(dir[1][i])) == NULL)
		print_error2(dir[0][i], &d);
	d.doc = ft_strdup(dir[1][i]);
	if (d.space[4] == 0)
		rd_files(rep, &d, i, 0);
}

void	ls_finish_to_del(t_data *d, DIR *rep, char ***dir, int i)
{
	if (d->opt[0] == 0 || rep == NULL)
	{
		while (i++ < d->nb_f)
		{
			ft_strdel(&dir[0][i - 1]);
			ft_strdel(&dir[1][i - 1]);
		}
	}
}

void	ls_r_recursive(t_data *d, char ***dir, int i)
{
	DIR		*rep;

	rep = NULL;
	i = d->nb_f;
	if (d->opt[0] == 1)
		ls_rta_final_recurs(d, dir, i, rep);
	ls_finish_to_del(d, rep, dir, 0);
}

void	ls_recursive(t_data *d, char ***dir)
{
	DIR		*rep;

	rep = NULL;
	if (d->opt[0] == 1)
		ls_ta_final_recurs(d, dir, 0, rep);
	ls_finish_to_del(d, rep, dir, 0);
}

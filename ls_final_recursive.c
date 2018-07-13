/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_final_recursive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 13:39:12 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/20 18:57:28 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_ta_final_recurs(t_data *d, char ***dir, int i, DIR *rep)
{
	t_stat	s;

	while (i < d->nb_f)
	{
		while (i < d->nb_f && dir[0][i][0] == '.' && (dir[0][i][1] == '.' ||
			dir[0][i][1] == '\0'))
			i++;
		if (i < d->nb_f && !(dir[0][i][0] == '.' && (dir[0][i][1] == '.' ||
			dir[0][i][1] == '\0')))
		{
			if (lstat(dir[1][i], &s) == -1)
				print_error2(d->av[d->d], d);
			if (S_ISDIR(s.st_mode))
			{
				d->space[4] = 0;
				recall_rd_files(rep, *d, i, dir);
				ft_strdel(&dir[0][i]);
				ft_strdel(&dir[1][i]);
			}
		}
		i++;
	}
}

void	ls_rta_final_recurs(t_data *d, char ***dir, int i, DIR *rep)
{
	t_stat	s;

	while (i-- > 0)
	{
		while (i >= 0 && dir[0][i][0] == '.' && (dir[0][i][1] == '.' ||
			dir[0][i][1] == '\0'))
			i--;
		if (i >= 0 && !(dir[0][i][0] == '.' && (dir[0][i][1] == '.' ||
			dir[0][i][1] == '\0')))
		{
			if (lstat(dir[1][i], &s) == -1)
				print_error2(d->av[d->d], d);
			if (S_ISDIR(s.st_mode))
			{
				d->space[4] = 0;
				recall_rd_files(rep, *d, i, dir);
				ft_strdel(&dir[0][i]);
				ft_strdel(&dir[1][i]);
			}
		}
	}
}

void	final_take_data(t_data *d, char ***dir, int i)
{
	t_stat	s;
	int		tp;

	tp = 1;
	if (d->j == -1)
		tp = 0;
	d->space[2] = 0;
	d->space[3] = 0;
	if ((dir[2] = (char **)malloc(sizeof(char *) * d->nb_f)) == NULL)
		print_error();
	while (i < d->nb_f)
	{
		if (lstat(dir[tp][i], &s) == -1)
		{
			print_error2(d->av[d->d], d);
			dir[2][i] = ft_strdup("////////");
		}
		else
			dir[2][i] = ft_strdup(ctime(&s.st_mtime));
		i++;
	}
}

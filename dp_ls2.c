/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:47:28 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/21 12:11:37 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	calc_tfile(t_data *d, char ***dir, t_age *a, int i)
{
	long	delta;

	delta = 0;
	while (i++ < d->nb_f)
	{
		a->ch = ft_strsplit(a->cd[i - 1][3], ':');
		compt_month(a, i - 1);
		a->t_d[i - 1] -= (ft_atoi(a->ch[2]) + ft_atoi(a->ch[1]) * 60 +
			ft_atoi(a->ch[0]) * 60 * 60);
		a->n = 0;
		while ((a->n)++ <= 4)
			ft_strdel(&a->cd[i - 1][a->n - 1]);
		if (d->opt[2] == 1)
			delta = (d->sec - ((a->tp - 1970) * 31536000 + (((a->tp - 1)
			- 1970) / 4 - 1) * 86400 - 3600 - a->t_d[i - 1]));
		if (delta > 15768000 || delta < -3600)
			dir[2][i - 1][15] = 'Q';
		if (d->opt[2] == 0 && d->opt[4] == 0)
			ft_strdel(&dir[2][i - 1]);
		ft_strdel(&a->ch[0]);
		ft_strdel(&a->ch[1]);
		ft_strdel(&a->ch[2]);
	}
}

/*
** a.tp = annee du fichier le plus recent + 1
** d->sec = time(NULL)
** tp entre date du fichier et 1970 = ((a.tp - 1) - 1970) * 365 * 24 * 60 * 60 +
** (365*24*60*60 - a.t_d[i])
*/

void	def_older_file(t_data *d, char ***dir, int i)
{
	t_age	a;

	if ((a.t_d = (long *)malloc(sizeof(long) * d->nb_f)) == NULL ||
		(a.cd = (char ***)malloc(sizeof(char **) * d->nb_f)) == NULL)
		print_error();
	if (ft_strcmp("////////", dir[2][0]) != 0)
	{
		a.cd[0] = ft_strsplit(dir[2][0], ' ');
		a.tp = ft_atoi(a.cd[0][4]);
	}
	while (i++ < d->nb_f)
	{
		if (ft_strcmp("////////", dir[2][i - 1]) != 0)
		{
			a.cd[i - 1] = ft_strsplit(dir[2][i - 1], ' ');
			if ((a.n = ft_atoi(a.cd[i - 1][4])) > a.tp - 1)
				a.tp = a.n + 1;
		}
	}
	calc_tfile1(d, dir, &a, 0);
	calc_tfile(d, dir, &a, 0);
	a.tp = 0;
	a.n = 0;
	if (d->opt[4] == 1)
		sort_tfiles(dir, &a, 1);
}

void	take_data(t_data *d, char ***dir, int i)
{
	char	*tp;

	d->space[2] = 0;
	d->space[3] = 0;
	d->space[5] = 0;
	if ((dir[1] = (char **)malloc(sizeof(char *) * d->nb_f)) == NULL)
		print_error();
	while (i < d->nb_f)
	{
		if (d->doc == NULL)
			tp = ft_strjoin(d->av[d->d], "/");
		else
			tp = ft_strjoin(d->doc, "/");
		dir[1][i] = ft_strjoin(tp, dir[0][i]);
		ft_strdel(&tp);
		i++;
	}
	if (d->opt[4] == 1 || d->opt[2] == 1)
	{
		final_take_data(d, dir, 0);
		def_older_file(d, dir, 0);
	}
	if (d->opt[2] == 1)
		malloc_to_add_data(d, dir, 0);
}

void	check_opt(t_data *d)
{
	t_stat	s;

	if (d->opt[3] == 0)
		ft_ls(d, 0, &s);
	else
		ft_lsr(d, d->ac - 1, &s);
}

void	dp_ls(t_data *d, char ***dir, int i)
{
	if (d->opt[2] == 1 && d->j != -1)
		dp_total_nb_blocs(d, dir, 0);
	if (d->opt[3] == 0)
	{
		while (i < d->nb_f)
		{
			if (d->opt[2] == 0)
				ft_putendl(dir[0][i]);
			else
				dp_lls(d, dir, &i, 1);
			i++;
		}
	}
	else
	{
		i = d->nb_f;
		while (i-- > 0)
		{
			if (d->opt[2] == 0)
				ft_putendl(dir[0][i]);
			else
				dp_lls(d, dir, &i, 1);
		}
	}
	last_free_and_recursive(d, dir);
}

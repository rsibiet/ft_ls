/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 14:53:47 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/20 19:11:32 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	compt_spaces(t_data *d, char ***dir, int *i, t_stat *s)
{
	int		tp;

	if (s->st_size != 0)
	{
		d->n[1][*i - 1] = s->st_size;
		d->n[2][*i - 1] = -1;
	}
	else
	{
		if (s->st_rdev != 0)
			ft_itoa_hex(d, s->st_rdev, 0, i);
		else
		{
			d->n[1][*i - 1] = 0;
			d->n[2][*i - 1] = 0;
		}
		tp = d->n[2][*i - 1] * 10;
		while ((tp = tp / 10) > 9)
			(d->sp_tp)++;
		d->sp_tp > d->space[5] ? d->space[5] = d->sp_tp : 0;
		d->sp_tp = 0;
	}
	compt_spaces2(d, dir, i);
}

void	add_data(t_data *d, char ***dir, int *i, t_stat *s)
{
	t_pwd	*pwd;
	t_gid	*gid;
	int		tp;

	d->n[0][*i - 1] = s->st_nlink;
	if ((pwd = getpwuid(s->st_uid)) == NULL)
		print_error2(d->av[d->d], d);
	dir[3][*i - 1] = strdup(pwd->pw_name);
	if ((gid = getgrgid(s->st_gid)) == NULL)
		print_error2(d->av[d->d], d);
	dir[4][*i - 1] = strdup(gid->gr_name);
	d->sp_tp = 0;
	tp = d->n[0][*i - 1] * 10;
	while ((tp = tp / 10) > 9)
		(d->sp_tp)++;
	d->sp_tp > d->space[0] ? d->space[0] = d->sp_tp : 0;
	d->sp_tp = 0;
	while (dir[4][*i - 1][d->sp_tp] != '\0')
		(d->sp_tp)++;
	d->sp_tp > d->space[2] ? d->space[2] = d->sp_tp : 0;
	d->sp_tp = 0;
	compt_spaces(d, dir, i, s);
}

void	malloc_to_add_data(t_data *d, char ***dir, int i)
{
	t_stat	s;
	int		tp;

	tp = 1;
	if (d->j == -1)
		tp = 0;
	d->space[0] = 0;
	d->space[1] = 0;
	if ((d->n = (int **)malloc(sizeof(int *) * 3)) == NULL ||
	(dir[3] = (char **)malloc(sizeof(char *) * d->nb_f)) == NULL ||
	(dir[4] = (char **)malloc(sizeof(char *) * d->nb_f)) == NULL)
		print_error();
	if ((d->n[0] = (int *)malloc(sizeof(int) * d->nb_f)) == NULL ||
		(d->n[1] = (int *)malloc(sizeof(int) * d->nb_f)) == NULL ||
		(d->n[2] = (int *)malloc(sizeof(int) * d->nb_f)) == NULL)
		print_error();
	while (i++ < d->nb_f)
	{
		if (lstat(dir[tp][i - 1], &s) == -1)
			print_error2(d->av[d->d], d);
		if (d->space[4] == 0)
			add_data(d, dir, &i, &s);
		d->space[4] = 0;
		d->sp_tp = 0;
	}
}

void	compt_month(t_age *a, int i)
{
	if (a->cd[i][1][0] == 'F')
		a->t_d[i] -= 2678400;
	else if (a->cd[i][1][0] == 'M' && a->cd[i][1][1] == 'a' &&
		a->cd[i][1][2] == 'r')
		a->t_d[i] -= 5097600;
	else if (a->cd[i][1][0] == 'A' && (a->cd[i][1][1] == 'p' ||
		a->cd[i][1][1] == 'v'))
		a->t_d[i] -= 7776000;
	else if (a->cd[i][1][0] == 'M' && a->cd[i][1][2] != 'r')
		a->t_d[i] -= 10368000;
	else if (a->cd[i][1][0] == 'J' && a->cd[i][1][1] == 'u')
		a->t_d[i] -= 13046400;
	else if (a->cd[i][1][0] == 'J' && a->cd[i][1][2] == 'l')
		a->t_d[i] -= 15638400;
	else if (a->cd[i][1][1] == 'o' || a->cd[i][1][1] == 'u')
		a->t_d[i] -= 18316800;
	else if (a->cd[i][1][0] == 'S')
		a->t_d[i] -= 20995200;
	else if (a->cd[i][1][0] == 'O')
		a->t_d[i] -= 23587200;
	else if (a->cd[i][1][0] == 'N')
		a->t_d[i] -= 26265600;
	else if (a->cd[i][1][0] == 'D')
		a->t_d[i] -= 28857600;
}

void	sort_tfiles(char ***dir, t_age *a, int i)
{
	char	*c;

	c = NULL;
	while (dir[0][i][0] != '\0')
	{
		while (i > 0 && a->t_d[i - 1] > a->t_d[i])
		{
			sub_sort_tfiles(dir, i, c, a);
			i--;
		}
		i++;
	}
	sort_tfiles_ascii(dir, a, 1, c);
}

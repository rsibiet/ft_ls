/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_to_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 15:18:29 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/20 18:48:20 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	final_sort_av(t_data *d, int i, int *tp, char *c)
{
	int	j;

	j = 0;
	while (i < *tp)
	{
		while (d->av[i - 1][j] != '\0' && d->av[i][j] != '\0' &&
			d->av[i - 1][j] == d->av[i][j])
			j++;
		while (i > 0 && ((d->av[i - 1][j] != '\0' && d->av[i][j] != '\0' &&
			d->av[i - 1][j] > d->av[i][j]) || (d->av[i][j] == '\0' &&
			d->av[i - 1][j] != '\0')))
		{
			c = ft_strdup(d->av[i - 1]);
			sub_sort_av(d, &i, &j, c);
		}
		j = 0;
		i++;
	}
}

void	sort_tfiles_ascii(char ***dir, t_age *a, int i, char *c)
{
	int		j;

	j = 0;
	while (dir[0][i][0] != '\0')
	{
		while (dir[0][i - 1][j] == dir[0][i][j] &&
				dir[0][i - 1][j] != '\0' && dir[0][i][j] != '\0')
			j++;
		while (i > 0 && a->t_d[i - 1] == a->t_d[i] &&
				(dir[0][i - 1][j] > dir[0][i][j] || (dir[0][i][j] == '\0'
				&& dir[0][i - 1][j] != '\0')))
		{
			sub_sort_tfiles(dir, i, c, a);
			j = 0;
			i--;
			while (i > 0 && dir[0][i - 1][j] == dir[0][i][j] &&
					dir[0][i - 1][j] != '\0' && dir[0][i][j] != '\0')
				j++;
		}
		j = 0;
		i++;
	}
}

void	sub_sort_tfiles(char ***dir, int i, char *c, t_age *a)
{
	c = ft_strdup(dir[0][i - 1]);
	ft_strdel(&dir[0][i - 1]);
	dir[0][i - 1] = ft_strdup(dir[0][i]);
	ft_strdel(&dir[0][i]);
	dir[0][i] = ft_strdup(c);
	ft_strdel(&c);
	c = ft_strdup(dir[1][i - 1]);
	ft_strdel(&dir[1][i - 1]);
	dir[1][i - 1] = ft_strdup(dir[1][i]);
	ft_strdel(&dir[1][i]);
	dir[1][i] = ft_strdup(c);
	ft_strdel(&c);
	c = ft_strdup(dir[2][i - 1]);
	ft_strdel(&dir[2][i - 1]);
	dir[2][i - 1] = ft_strdup(dir[2][i]);
	ft_strdel(&dir[2][i]);
	dir[2][i] = ft_strdup(c);
	ft_strdel(&c);
	a->tp = a->t_d[i - 1];
	a->t_d[i - 1] = a->t_d[i];
	a->t_d[i] = a->tp;
}

void	sub_sort_av(t_data *d, int *i, int *j, char *c)
{
	while (d->av[*i - 1][*j] != '\0' && d->av[*i][*j] != '\0' &&
			d->av[*i - 1][*j] == d->av[*i][*j])
		(*j)++;
	ft_strdel(&d->av[*i - 1]);
	d->av[*i - 1] = ft_strdup(d->av[*i]);
	ft_strdel(&d->av[*i]);
	d->av[*i] = ft_strdup(c);
	(*i)--;
	(*j) = 0;
}

void	sub_sort_files(char ***dir, int *i, int *j, char *c)
{
	ft_strdel(&dir[0][*i - 1]);
	dir[0][*i - 1] = ft_strdup(dir[0][*i]);
	ft_strdel(&dir[0][*i]);
	dir[0][*i] = ft_strdup(c);
	ft_strdel(&c);
	(*i)--;
	(*j) = 0;
	while (*i > 0 && dir[0][*i - 1][*j] == dir[0][*i][*j] &&
			dir[0][*i - 1][*j] != '\0' && dir[0][*i][*j] != '\0')
		(*j)++;
}

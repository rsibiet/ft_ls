/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:23:38 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/25 17:12:02 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_av(t_data *d, int i, int j, int tp)
{
	char	*c;
	t_stat	s;

	if (lstat(d->av[0], &s) == -1)
		print_error2(d->av[0], d);
	if (!(S_ISDIR(s.st_mode)))
		tp++;
	while (i < d->ac)
	{
		sort_just_files(d, &tp, &i, &s);
		while (d->av[i - 1][j] != '\0' && d->av[i][j] != '\0' &&
			d->av[i - 1][j] == d->av[i][j])
			j++;
		while (i > tp && ((d->av[i - 1][j] != '\0' && d->av[i][j] != '\0' &&
			d->av[i - 1][j] > d->av[i][j]) || (d->av[i][j] == '\0' &&
			d->av[i - 1][j] != '\0')))
		{
			c = ft_strdup(d->av[i]);
			sub_sort_av(d, &i, &j, c);
		}
		i++;
		j = 0;
	}
	final_sort_av(d, 1, &tp, c);
	check_opt(d);
}

char	***malloc_dir(t_data *d, DIR *rep, int *i)
{
	t_dir	*file;
	char	***dir;

	file = readdir(rep);
	while (file != NULL)
	{
		if (d->opt[1] != 0 || file->d_name[0] != '.')
			(*i)++;
		file = readdir(rep);
	}
	if (*i == 0)
		return (NULL);
	if (closedir(rep) == -1)
		return (NULL);
	if ((dir = (char ***)malloc(sizeof(char **) * d->j)) == NULL)
		print_error();
	if ((dir[0] = (char **)malloc(sizeof(char *) * (*i + 1))) == NULL)
		print_error();
	dir[0][*i] = ft_strnew(0);
	d->nb_f = *i;
	return (dir);
}

void	rd_files(DIR *rep, t_data *d, int j, int i)
{
	char	***dir;

	d->opt[4] == 1 ? d->j = 3 : 0;
	d->opt[2] == 1 ? d->j = 5 : 0;
	if ((dir = malloc_dir(d, rep, &i)) == NULL && i != 0)
		print_error2(d->av[j], d);
	else if (dir == NULL && i == 0)
		return ;
	if (d->doc == NULL)
		rep = opendir(d->av[j]);
	else
		rep = opendir(d->doc);
	if (rep == NULL)
		print_error2(d->av[j], d);
	d->d = j;
	i--;
	test_dir(dir, d, rep, i);
	sort_files(d, dir, 1, 0);
}

void	ft_lsr(t_data *d, int i, t_stat *s)
{
	DIR		*rep;

	while (i-- >= 0)
	{
		if (lstat(d->av[i + 1], s) == -1)
			print_error2(d->av[i + 1], d);
		if (S_ISDIR(s->st_mode))
		{
			if ((rep = opendir(d->av[i + 1])) == NULL)
				print_error2(d->av[i + 1], d);
			if (d->space[4] != -1)
				dp_avr_name(rep, d, i);
			else
				d->space[4] = 0;
		}
		else
			one_file(d, d->av[i + 1], i + 1);
		ft_strdel(&d->av[i + 1]);
	}
	free(d->av);
	d->av = NULL;
}

void	ft_ls(t_data *d, int i, t_stat *s)
{
	DIR		*rep;

	while (i++ < d->ac)
	{
		if (lstat(d->av[i - 1], s) == -1)
			print_error2(d->av[i - 1], d);
		if (S_ISDIR(s->st_mode))
		{
			if ((rep = opendir(d->av[i - 1])) == NULL)
				print_error2(d->av[i - 1], d);
			if (d->space[4] != -1)
				dp_av_name(rep, d, i);
			else
				d->space[4] = 0;
		}
		else
			one_file(d, d->av[i - 1], i - 1);
		ft_strdel(&d->av[i - 1]);
	}
	free(d->av);
	d->av = NULL;
}

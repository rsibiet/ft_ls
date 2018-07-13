/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_space_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 18:16:01 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/25 17:12:47 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	test_dir(char ***dir, t_data *d, DIR *rep, int i)
{
	t_dir	*file;

	while (i >= 0)
	{
		file = readdir(rep);
		if (d->opt[1] != 0 || file->d_name[0] != '.')
		{
			dir[0][i] = ft_strdup(file->d_name);
			i--;
		}
	}
	if (closedir(rep) == -1)
		print_error2(d->av[d->d], d);
}

void	dp_av_name(DIR *rep, t_data *d, int i)
{
	if (i != 1)
		ft_putchar('\n');
	if (d->ac != 1)
		ft_putstr(d->av[i - 1]);
	if (d->ac != 1)
		ft_putendl(":");
	rd_files(rep, d, i - 1, 0);
}

void	dp_avr_name(DIR *rep, t_data *d, int i)
{
	if (i != d->ac - 2)
		ft_putchar('\n');
	if (d->ac != 1)
		ft_putstr(d->av[i + 1]);
	if (d->ac != 1)
		ft_putendl(":");
	rd_files(rep, d, i + 1, 0);
}

void	free_if_lopt(t_data *d, char ***dir)
{
	free(d->n[0]);
	free(d->n[1]);
	free(d->n[2]);
	d->n[0] = NULL;
	d->n[1] = NULL;
	d->n[2] = NULL;
	free(d->n);
	d->n = NULL;
	ft_strdel(dir[3]);
	ft_strdel(dir[4]);
}

void	dp_space_five(t_data *d, int *i)
{
	int		sp;

	sp = d->space[5];
	d->sp_tp = d->n[2][*i] * 10;
	while ((d->sp_tp = d->sp_tp / 10) > 9)
		sp--;
	while (sp-- > 0)
		ft_putchar(' ');
	d->sp_tp = 0;
}

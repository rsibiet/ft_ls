/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_spaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:43:52 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/20 18:16:44 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	dp_date(char ***dir, int *i, int j)
{
	if (dir[2][*i][15] != 'Q')
	{
		while (dir[2][*i][j++ - 3] != ':')
			ft_putchar(dir[2][*i][j - 1]);
	}
	else
	{
		while (j++ < 11)
			ft_putchar(dir[2][*i][j - 1]);
		j = 19;
		ft_putchar(' ');
		while (j++ < 23)
			ft_putchar(dir[2][*i][j]);
	}
}

void	dp_space_four(t_data *d, char ***dir, int *i)
{
	int		sp;

	while (dir[4][*i][d->sp_tp] != '\0')
		(d->sp_tp)++;
	sp = d->space[2] - d->sp_tp;
	while (sp-- > 0)
		ft_putchar(' ');
	d->sp_tp = 0;
}

void	dp_space_three(t_data *d, int *i)
{
	int		sp;

	sp = d->space[3];
	ft_putstr("  ");
	d->sp_tp = d->n[1][*i] * 10;
	while ((d->sp_tp = d->sp_tp / 10) > 9)
		sp--;
	while (sp-- > 0)
		ft_putchar(' ');
	d->sp_tp = 0;
}

void	dp_space_two(t_data *d, char ***dir, int *i)
{
	int		sp;

	ft_putstr("  ");
	while (dir[3][*i][d->sp_tp] != '\0')
		(d->sp_tp)++;
	sp = d->space[1] - d->sp_tp;
	while (sp-- > 0)
		ft_putchar(' ');
	d->sp_tp = 0;
}

void	dp_space_one(t_data *d, int *i)
{
	int		sp;

	sp = d->space[0];
	d->sp_tp = d->n[0][*i] * 10;
	while ((d->sp_tp = d->sp_tp / 10) > 9)
		sp--;
	while (sp-- > 0)
		ft_putchar(' ');
	d->sp_tp = 0;
}

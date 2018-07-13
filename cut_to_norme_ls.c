/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_to_norme_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 18:50:56 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/20 19:12:17 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	compt_spaces2(t_data *d, char ***dir, int *i)
{
	int		tp;

	tp = d->n[1][*i - 1] * 10;
	while ((tp = tp / 10) > 9)
		(d->sp_tp)++;
	d->sp_tp > d->space[3] ? d->space[3] = d->sp_tp : 0;
	d->sp_tp = 0;
	while (dir[3][*i - 1][d->sp_tp] != '\0')
		(d->sp_tp)++;
	d->sp_tp > d->space[1] ? d->space[1] = d->sp_tp : 0;
}

void	calc_tfile1(t_data *d, char ***dir, t_age *a, int i)
{
	while (i++ < d->nb_f)
	{
		if (ft_strcmp("////////", dir[2][i - 1]) != 0)
			a->t_d[i - 1] = ((a->tp - ft_atoi(a->cd[i - 1][4]))
			* 31536000) - (ft_atoi(a->cd[i - 1][2]) * 86400);
	}
	if (d->opt[2] == 1)
		d->sec = time(NULL);
}

void	dp_lls2(t_data *d, int *i, char ***dir)
{
	if (d->n[2][*i] != -1)
		ft_putchar(' ');
	dp_space_three(d, i);
	dp_space_four(d, dir, i);
	ft_putnbr(d->n[1][*i]);
	if (d->n[2][*i] != -1)
	{
		ft_putstr(", ");
		dp_space_five(d, i);
		ft_putnbr(d->n[2][*i]);
	}
	ft_putchar(' ');
	dp_date(dir, i, 4);
	ft_putchar(' ');
	ft_putstr(dir[0][*i]);
}

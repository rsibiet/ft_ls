/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:29:13 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/30 15:50:57 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_just_files(t_data *d, int *tp, int *i, t_stat *s)
{
	char	*c;

	if (lstat(d->av[*i], s) == -1)
		print_error2(d->av[*i], d);
	if (!(S_ISDIR(s->st_mode)))
	{
		if (*i != *tp)
		{
			c = ft_strdup(d->av[*tp]);
			ft_strdel(&d->av[*tp]);
			d->av[*tp] = ft_strdup(d->av[*i]);
			ft_strdel(&d->av[*i]);
			d->av[*i] = ft_strdup(c);
		}
		(*tp)++;
	}
}

void	one_file(t_data *d, char *c, int j)
{
	char	***dir;

	d->opt[4] == 1 ? d->j = 3 : 0;
	d->opt[2] == 1 ? d->j = 5 : 0;
	if ((dir = (char ***)malloc(sizeof(char **) * d->j)) == NULL)
		print_error();
	if ((dir[0] = (char **)malloc(sizeof(char *) * 2)) == NULL)
		print_error();
	dir[0][1] = ft_strnew(0);
	d->nb_f = 1;
	d->d = j;
	d->j = -1;
	dir[0][0] = ft_strdup(c);
	take_data(d, dir, 0);
	dp_ls(d, dir, 0);
}

void	print_error2(char *c, t_data *d)
{
	if (d->space[4] == 0)
	{
		ft_putstr("ft_ls: ");
		if (d->doc == NULL)
			ft_putstr(c);
		else
			ft_putstr(d->doc);
		d->space[4] = -1;
		ft_putstr(": ");
		perror("");
	}
	else
		exit(EXIT_FAILURE);
}

void	print_error(void)
{
	ft_putstr("ft_ls: ");
	perror("");
	exit(EXIT_FAILURE);
}

void	pt_illegal_opt(char opt)
{
	ft_putstr("ft_ls : illegal option -- ");
	ft_putchar(opt);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [-Ralrt] [file ...]");
	exit(EXIT_FAILURE);
}

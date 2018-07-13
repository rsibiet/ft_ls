/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 11:10:52 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/19 18:40:50 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_opt(char **av, int *i, int *j, t_data *d)
{
	if (av[*i][*j] == '-' && av[*i][*j + 1] == '\0')
		return (-2);
	else if (av[*i][*j] == 'R')
		d->opt[0] = 1;
	else if (av[*i][*j] == 'a')
		d->opt[1] = 1;
	else if (av[*i][*j] == 'l')
		d->opt[2] = 1;
	else if (av[*i][*j] == 'r')
		d->opt[3] = 1;
	else if (av[*i][*j] == 't')
		d->opt[4] = 1;
	else
		return (av[*i][*j]);
	(*j)++;
	return (-1);
}

char	def_opt(int ac, char **av, t_data *d, int i)
{
	int	j;
	int ret;

	j = 1;
	ret = 0;
	while (i < ac && av[i][0] == '-')
	{
		while (av[i][j] != '\0')
		{
			if ((ret = ls_opt(av, &i, &j, d)) == -2)
			{
				cut_opt(ac, av, d, i + 1);
				return (0);
			}
			else if (ret == av[i][j])
				return (av[i][j]);
		}
		j = 1;
		i++;
	}
	cut_opt(ac, av, d, i);
	return (0);
}

void	sort_files(t_data *d, char ***dir, int i, int j)
{
	char	*c;

	if (d->opt[4] == 0)
	{
		while (dir[0][i][0] != '\0')
		{
			while (dir[0][i - 1][j] == dir[0][i][j] &&
				dir[0][i - 1][j] != '\0' && dir[0][i][j] != '\0')
				j++;
			while (i > 0 && (dir[0][i - 1][j] > dir[0][i][j] ||
				(dir[0][i][j] == '\0' && dir[0][i - 1][j] != '\0')))
			{
				c = ft_strdup(dir[0][i - 1]);
				sub_sort_files(dir, &i, &j, c);
			}
			j = 0;
			i++;
		}
	}
	take_data(d, dir, 0);
	dp_ls(d, dir, 0);
}

void	cut_opt(int ac, char **av, t_data *d, int j)
{
	d->j = 0;
	if (j == ac || (j == ac - 1 && av[j][0] == '-'))
	{
		d->ac = 1;
		d->j = 1;
	}
	else
		d->ac = ac - j;
	if ((d->av = (char **)malloc(sizeof(char *) * (d->ac))) == NULL)
		print_error();
	d->i = 0;
	if (d->j == 1)
		d->av[0] = ft_strdup(".");
	while (j < ac)
	{
		d->av[d->i] = ft_strdup(av[j]);
		j++;
		(d->i)++;
	}
}

int		main(int ac, char **av)
{
	DIR		*rep;
	t_data	d;

	d.space[4] = 0;
	d.i = -1;
	d.doc = NULL;
	while (d.i++ < 4)
		d.opt[d.i] = 0;
	rep = NULL;
	if ((d.i = def_opt(ac, av, &d, 1)) != 0)
		pt_illegal_opt(d.i);
	else if (d.j == 1)
	{
		if ((rep = opendir(".")) == NULL)
			print_error2(".", NULL);
		if (d.space[4] != -1)
			rd_files(rep, &d, 0, 0);
	}
	else
	{
		d.j = 1;
		sort_av(&d, 1, 0, 0);
	}
	return (0);
}

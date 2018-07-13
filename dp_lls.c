/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp_lls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 15:38:30 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/20 18:56:05 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	last_free_and_recursive(t_data *d, char ***dir)
{
	d->space[4] = 0;
	d->j = 1;
	if (d->opt[2] == 1)
		free_if_lopt(d, dir);
	if (d->opt[2] == 1 || d->opt[4] == 1)
		ft_strdel(dir[2]);
	if (d->opt[3] == 0)
		ls_recursive(d, dir);
	else
		ls_r_recursive(d, dir, 0);
	if (d->doc != NULL)
		ft_strdel(&d->doc);
	ft_strdel(dir[1]);
	ft_strdel(dir[0]);
	free(dir);
	dir = NULL;
}

void	dp_mode(t_stat *s)
{
	if (S_ISLNK(s->st_mode))
		ft_putchar('l');
	else if (S_ISCHR(s->st_mode))
		ft_putchar('c');
	else if (S_ISBLK(s->st_mode))
		ft_putchar('b');
	else if (S_ISFIFO(s->st_mode))
		ft_putchar('p');
	else if (S_ISSOCK(s->st_mode))
		ft_putchar('s');
	else
		ft_putchar((S_ISDIR(s->st_mode)) ? 'd' : '-');
	ft_putchar((s->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((s->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((s->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((s->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((s->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((s->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((s->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((s->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((s->st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}

void	dp_slink(char ***dir, int *i)
{
	int		size;
	int		nchar;
	char	*buff;

	size = 64;
	ft_putstr(" -> ");
	if ((buff = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		print_error();
	while ((nchar = readlink(dir[1][*i], buff, size)) < 0)
	{
		ft_strdel(&buff);
		size *= 2;
		if ((buff = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
			print_error();
	}
	ft_putendl(buff);
}

void	dp_lls(t_data *d, char ***dir, int *i, int tp)
{
	t_stat	s;

	if (d->j == -1)
		tp = 0;
	if (ft_strcmp(dir[2][*i], "////////") != 0)
	{
		if (lstat(dir[tp][*i], &s) == -1)
			print_error2(d->av[d->d], d);
		dp_mode(&s);
		dp_space_one(d, i);
		ft_putnbr(d->n[0][*i]);
		ft_putchar(' ');
		ft_putstr(dir[3][*i]);
		dp_space_two(d, dir, i);
		ft_putstr(dir[4][*i]);
		dp_lls2(d, i, dir);
		if (S_ISLNK(s.st_mode))
			dp_slink(dir, i);
		else
			ft_putchar('\n');
	}
	ft_strdel(&dir[2][*i]);
	ft_strdel(&dir[3][*i]);
	ft_strdel(&dir[4][*i]);
}

void	dp_total_nb_blocs(t_data *d, char ***dir, int i)
{
	t_stat			s;
	unsigned long	nb;

	nb = 0;
	while (i < d->nb_f)
	{
		if (lstat(dir[1][i], &s) == -1)
			print_error2(d->av[d->d], d);
		nb += s.st_blocks;
		i++;
	}
	ft_putstr("total ");
	ft_putnbr_ul(nb);
	ft_putchar('\n');
}

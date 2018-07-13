/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_special_device.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:02:20 by rsibiet           #+#    #+#             */
/*   Updated: 2016/01/20 19:09:42 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		atoi_hex_to_ten(char *c, int i, int nb)
{
	while (c[i] != '\0')
	{
		if (c[i] >= '0' && c[i] <= '9')
			nb = nb * 16 + c[i] - '0';
		else
			nb = nb * 16 + c[i] - 'A' + 10;
		i++;
	}
	return (nb);
}

void	min_maj_special_device(t_data *d, char *c, int j, int *i)
{
	char	*one;
	char	*two;
	int		tp;
	int		k;

	k = ft_strlen(c) - 6;
	tp = k;
	while (c[tp] == '0')
		tp++;
	if (c[tp] == '\0')
		tp--;
	two = ft_strnew(7 - (tp - k));
	one = ft_strnew(k + 1);
	while (c[tp] != '\0')
		two[j++] = c[tp++];
	two[j] = '\0';
	tp = 0;
	while (tp++ < k)
		one[tp - 1] = c[tp - 1];
	one[tp - 1] = '\0';
	d->n[1][*i - 1] = atoi_hex_to_ten(one, 0, 0);
	d->n[2][*i - 1] = atoi_hex_to_ten(two, 0, 0);
}

void	ft_itoa_hex(t_data *d, int nb, int j, int *i)
{
	char	*c;
	int		tp;

	tp = nb;
	while (tp > 15)
	{
		j++;
		tp /= 16;
	}
	c = ft_strnew(j + 1);
	while (j >= 0)
	{
		if (nb % 16 < 10)
			c[j] = nb % 16 + '0';
		else
			c[j] = nb % 16 + 'A' - 10;
		nb = nb / 16;
		j--;
	}
	min_maj_special_device(d, c, 0, i);
}

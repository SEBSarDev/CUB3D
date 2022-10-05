/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:25:46 by ssar              #+#    #+#             */
/*   Updated: 2021/04/02 09:10:55 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	deborde_gauche(t_all *all, double *stock, double *d, int *count)
{
	double	before;
	double	after;
	double	a;
	int		i;

	i = all->infos.x - 1;
	before = (double)all->perso.angle + atan((d[1] - (0.0 * d[2])) / d[0]);
	after = (double)all->perso.angle
				+ atan((d[1] - ((double)all->infos.x * d[2])) / d[0]);
	a = (double)all->perso.angle
				+ atan((d[1] - ((double)(i + 1) * d[2])) / d[0]);
	if (before - *stock >= 3.14)
	{
		*stock += X2PI;
		if (before > X2PI && a < PI2)
			a += X2PI;
	}
	if (a - *stock > 3.14)
		a -= X2PI;
	while ((before + (after - a)) < *stock && ++i < all->infos.x * 2)
	{
		a = (double)all->perso.angle + atan((d[1] - (double)i * d[2]) / d[0]);
		def_angle_bis(&a, stock, &before);
		(*count)--;
	}
}

int		get_count(t_all *all, int j, double *d, double *as)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (++i < all->infos.x)
	{
		as[0] = (double)all->perso.angle
				+ atan((d[1] - ((double)i * d[2])) / d[0]);
		as[1] = all->infos.sprite[j][3];
		def_angle(all, &as[0], &as[1], j);
		if (as[0] > as[1])
			count++;
		else if (as[0] <= as[1])
			break ;
	}
	return (count);
}

void	deborde_droite(t_all *all, double *d, double *as, int *count)
{
	int i;

	i = all->infos.x;
	while (as[0] > as[1] && i < all->infos.x * 2)
	{
		as[0] = (double)all->perso.angle
				+ atan((d[1] - ((double)i * d[2])) / d[0]);
		if (as[0] > X2PI)
			as[0] -= X2PI;
		if (as[0] < 0)
			as[0] += X2PI;
		if ((as[0] >= X3PI2 && as[0] <= X2PI)
						&& (as[1] >= 0.0
						&& as[1] <= PI2))
			as[1] += X2PI;
		if ((as[0] >= 0.0 && as[0] <= PI2)
						&& (as[1] >= X3PI2
						&& as[1] <= X2PI))
			as[1] -= X2PI;
		(*count)++;
		i++;
	}
}

void	get_colonne(t_all *all, double *d)
{
	int		j;
	double	as[2];
	int		count;

	j = 0;
	while (all->infos.sprite[j + 1])
	{
		if (all->infos.sprite[j][2] <= (double)all->infos.case_size / 5.0)
		{
			j++;
			continue ;
		}
		count = get_count(all, j, d, as);
		if (count == 0)
			deborde_gauche(all, &as[1], d, &count);
		if (count == all->infos.x)
			deborde_droite(all, d, as, &count);
		all->infos.sprite[j][3] = (double)count;
		j++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:36:28 by ssar              #+#    #+#             */
/*   Updated: 2021/04/05 12:30:51 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	check_donne(t_all *all, int *x, int *y)
{
	if (*x < 0)
		*x = 0;
	if (*x > all->infos.map_x)
		*x = all->infos.map_x;
	if (*y < 0)
		*y = 0;
	if (*y > all->infos.map_y)
		*y = all->infos.map_y;
}

void	impact_spr_so(t_all *all, int x, int y, int size)
{
	int yx[2];

	if (y >= 0 && x - 1 >= 0 && y < all->infos.map_y && x < all->infos.map_x)
	{
		if (all->infos.map[(y / size)][((x - 1) / size)] == '2')
		{
			yx[0] = x - 1;
			yx[1] = y;
			all->infos.sprite_y = stock_sprite(all, yx, all->infos.sprite_y);
		}
	}
	if (y - 1 >= 0 && x - 1 >= 0
					&& y < all->infos.map_y && x < all->infos.map_x)
	{
		if (all->infos.map[((y - 1) / size)][((x - 1) / size)] == '2')
		{
			yx[0] = x - 1;
			yx[1] = y - 1;
			all->infos.sprite_y = stock_sprite(all, yx, all->infos.sprite_y);
		}
	}
}

void	impact_spr(t_all *all, int x, int y)
{
	int size;
	int yx[2];

	size = all->infos.case_size;
	check_donne(all, &x, &y);
	if (y >= 0 && x >= 0 && y < all->infos.map_y && x < all->infos.map_x)
	{
		if (all->infos.map[(y / size)][(x / size)] == '2')
		{
			yx[0] = x;
			yx[1] = y;
			all->infos.sprite_y = stock_sprite(all, yx, all->infos.sprite_y);
		}
	}
	if (y - 1 >= 0 && x >= 0 && y < all->infos.map_y && x < all->infos.map_x)
	{
		if (all->infos.map[((y - 1) / size)][(x / size)] == '2')
		{
			yx[0] = x;
			yx[1] = y - 1;
			all->infos.sprite_y = stock_sprite(all, yx, all->infos.sprite_y);
		}
	}
	impact_spr_so(all, x, y, size);
}

void	impact_wall(t_all *all, int x, int y, int *stop)
{
	int size;

	check_donne(all, &x, &y);
	size = all->infos.case_size;
	if (all->infos.map[(y / size)][(x / size)] == '1'
		|| x < 1 || y < 1 || x > all->infos.map_x || y > all->infos.map_y)
		*stop = 1;
	if (y - 1 >= 0)
	{
		if (all->infos.map[((y - 1) / size)][(x / size)] == '1'
			|| x < 1 || y < 1 || x > all->infos.map_x || y > all->infos.map_y)
			*stop = 1;
	}
	if (x - 1 >= 0)
	{
		if (all->infos.map[(y / size)][((x - 1) / size)] == '1'
			|| x < 1 || y < 1 || x > all->infos.map_x || y > all->infos.map_y)
			*stop = 1;
	}
	if (y - 1 >= 0 && x - 1 >= 0)
	{
		if (all->infos.map[((y - 1) / size)][((x - 1) / size)] == '1'
			|| x < 1 || y < 1 || x > all->infos.map_x || y > all->infos.map_y)
			*stop = 1;
	}
}

void	check_distance(t_all *all, double angle, t_xy *xy, int size)
{
	int yx[4];

	yx[3] = 0;
	yx[2] = 0;
	while (yx[3] == 0)
	{
		yx[0] = all->perso.center_x + (yx[2] * cos(angle));
		yx[1] = all->perso.center_y - (yx[2] * sin(angle));
		while (yx[0] % size != 0 && yx[1] % size != 0
				&& yx[0] >= 0 && yx[1] >= 0
				&& yx[0] < all->infos.map_x && yx[1] < all->infos.map_y)
		{
			(yx[2])++;
			yx[0] = all->perso.center_x + (yx[2] * cos(angle));
			yx[1] = all->perso.center_y - (yx[2] * sin(angle));
		}
		impact_spr(all, yx[0], yx[1]);
		impact_wall(all, yx[0], yx[1], &yx[3]);
		(yx[2])++;
	}
	xy->x = yx[0];
	xy->y = yx[1];
	check_donne(all, &xy->x, &xy->y);
}

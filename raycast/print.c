/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:54:23 by ssar              #+#    #+#             */
/*   Updated: 2021/04/09 22:22:21 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	print_spr(t_all *all, int *yx, int o, int *line)
{
	if (all->infos.save == 1)
	{
		if (line[o] != -1)
			all->infos.bmp[yx[1]][yx[0]] = line[o];
	}
	else
		my_mlx_pixel_put(&all->img, yx[0], yx[1], line[o]);
}

void	print_up(t_all *all, double *height, int *data, t_textur t)
{
	int		y;
	int		moitie;
	int		i;
	int		j;
	double	div;

	i = (height[1] / 2) + 1;
	y = all->infos.y / 2;
	moitie = floor(height[0] / 2.0) + 1;
	div = (double)t.y / height[1];
	while (--moitie > 0)
	{
		i--;
		j = (int)(floor((double)i * div));
		if (j < t.y && j >= 0 && y < all->infos.y && data[0] < all->infos.x
			&& data[1] < t.x && data[1] >= 0 && data[0] >= 0 && y >= 0)
		{
			if (all->infos.save == 1)
				all->infos.bmp[y][data[0]] = t.texture[j][data[1]];
			else
				my_mlx_pixel_put(&all->img, data[0], y, t.texture[j][data[1]]);
		}
		y--;
	}
	print_ceil(all, data, y);
}

void	print_down(t_all *all, double *height, int *data, t_textur t)
{
	int		y;
	int		moitie;
	int		i;
	int		j;
	double	div;

	div = (double)t.y / height[1];
	i = (height[1] / 2) - 1;
	y = all->infos.y / 2;
	moitie = floor(height[0] / 2.0) - 1;
	while (++moitie < height[0])
	{
		i++;
		j = (int)(floor((double)i * div));
		if (j < t.y && j >= 0 && y < all->infos.y && data[0] < all->infos.x
			&& data[1] < t.x && data[1] >= 0 && data[0] >= 0 && y >= 0)
		{
			if (all->infos.save == 1)
				all->infos.bmp[y][data[0]] = t.texture[j][data[1]];
			else
				my_mlx_pixel_put(&all->img, data[0], y, t.texture[j][data[1]]);
		}
		y++;
	}
	print_floor(all, data, y);
}

void	init_print_w(t_all *all, double *height, int *data, t_textur texture)
{
	print_up(all, height, data, texture);
	print_down(all, height, data, texture);
}

void	print_wall(t_all *all, float dist, int x, t_xy *xy)
{
	double	height[2];
	double	size;
	int		data[3];

	data[0] = x;
	data[1] = (int)(xy->hit) % all->infos.case_size;
	size = (double)all->infos.case_size;
	if (dist <= 0.0)
		dist = 1;
	height[0] = size * ((double)all->infos.y / (double)dist);
	height[1] = height[0];
	if (height[0] > all->infos.y || height[0] < 0)
		height[0] = (double)all->infos.y;
	if (xy->mur == 1)
		init_print_w(all, height, data, all->infos.nord);
	else if (xy->mur == 2)
		init_print_w(all, height, data, all->infos.est);
	else if (xy->mur == 3)
		init_print_w(all, height, data, all->infos.sud);
	else
		init_print_w(all, height, data, all->infos.ouest);
}

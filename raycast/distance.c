/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:08:13 by ssar              #+#    #+#             */
/*   Updated: 2021/04/05 19:13:46 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	init_sprite(t_all *all, double ***sprite)
{
	*sprite = (double **)malloc(sizeof(double *) * 2);
	if (!(*sprite))
		ft_error(all, NULL, NULL, strerror(errno));
	(*sprite)[0] = (double *)malloc(sizeof(double) * 5);
	if (!*(sprite)[0])
		ft_error(all, (char **)sprite, NULL, strerror(errno));
	(*sprite)[0][0] = 0.1;
	(*sprite)[0][1] = 0.1;
	(*sprite)[0][2] = 0.1;
	(*sprite)[0][3] = 0.1;
	(*sprite)[0][4] = '\0';
	(*sprite)[1] = 0;
}

void	get_distance(t_all *all, double angle, int i)
{
	t_xy	xy;
	double	fish_angle;
	float	dist;
	int		x;
	int		y;

	fish_angle = fabs(angle - all->perso.angle);
	check_distance(all, angle, &xy, all->infos.case_size);
	x = fabs((double)all->perso.center_x - (double)xy.x);
	y = fabs((double)all->perso.center_y - (double)xy.y);
	dist = sqrtf((float)x * (float)x + (float)y * (float)y);
	fill_sprite(all, all->infos.sprite_y, fish_angle);
	xy.angle = angle;
	xy.mur = which_texture(all, xy);
	if (xy.y % all->infos.case_size == 0)
		xy.hit = xy.x;
	else
		xy.hit = xy.y;
	dist = dist * cos(fish_angle);
	all->infos.distances[i] = (double)dist;
	print_wall(all, dist, i, &xy);
}

double	get_dist(t_all *all, double angle)
{
	t_xy	xy;
	float	dist;
	int		x;
	int		y;

	init_sprite(all, &all->infos.sprite);
	init_sprite(all, &all->infos.sprite_y);
	check_distance(all, angle, &xy, all->infos.case_size);
	x = fabs((double)all->perso.center_x - (double)xy.x);
	y = fabs((double)all->perso.center_y - (double)xy.y);
	dist = sqrtf((float)x * (float)x + (float)y * (float)y);
	ft_free_tab_int((int **)all->infos.sprite_y);
	ft_free_tab_int((int **)all->infos.sprite);
	return ((double)dist);
}

void	each_ray(t_all *all, double *data, int *i)
{
	double	angle;

	init_sprite(all, &all->infos.sprite_y);
	angle = (double)all->perso.angle
			+ atan((data[1] - ((double)(*i) * data[2])) / data[0]);
	if (angle < 0)
		angle += (double)X2PI;
	if (angle > X2PI)
		angle -= (double)X2PI;
	get_distance(all, angle, *i);
	(*i)++;
	ft_free_tab_int((int **)all->infos.sprite_y);
}

void	rayon(t_all *all)
{
	int		i;
	double	data[3];

	i = 0;
	data[0] = get_dist(all, all->perso.angle);
	data[1] = data[0] * tan(0.523599);
	data[2] = (data[1] * 2.0) / (double)all->infos.x;
	init_sprite(all, &all->infos.sprite);
	while (i < all->infos.x)
		each_ray(all, data, &i);
	get_sort_sprite(all);
	print_sprite(all, data[0], data[1], data[2]);
	ft_free_tab_int((int **)all->infos.sprite);
	if (all->infos.save == 1)
		return ;
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->img.img, 0, 0);
}

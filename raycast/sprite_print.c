/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:29:00 by ssar              #+#    #+#             */
/*   Updated: 2021/04/04 20:36:21 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	def_angle(t_all *all, double *angle, double *stock, int j)
{
	if (*angle > X2PI)
		*angle -= X2PI;
	if (*angle < 0)
		*angle += X2PI;
	if ((*angle >= X3PI2 && *angle <= X2PI)
					&& (all->infos.sprite[j][3] >= 0.0
					&& all->infos.sprite[j][3] <= PI2))
		*stock += X2PI;
	if ((*angle >= 0.0 && *angle <= PI2)
					&& (all->infos.sprite[j][3] >= X3PI2
					&& all->infos.sprite[j][3] <= X2PI))
		*stock -= X2PI;
}

void	def_angle_bis(double *angle, double *stock, double *before)
{
	if (*angle > X2PI)
		*angle -= X2PI;
	if (*angle < 0)
		*angle += X2PI;
	if (*before - *stock >= 3.14)
	{
		*stock += X2PI;
		if (*before > X2PI && *angle < PI2)
			*angle += X2PI;
	}
	if (*angle - *stock > 3.14)
		*angle -= X2PI;
}

void	print_sprite_ter(t_all *all, int i, int *line, int *yx)
{
	int		o;
	double	height;

	height = (double)all->infos.case_size
			* ((double)all->infos.y / all->infos.sprite[i][2]);
	o = 0;
	while (o < height)
	{
		if (line[o] == all->infos.objet.texture[0][0])
		{
			o++;
			(yx[1])++;
			continue ;
		}
		if (yx[1] >= 0 && yx[1] < all->infos.y && yx[0] >= 0
				&& yx[0] < all->infos.x
				&& (all->infos.sprite[i][2] < (int)all->infos.distances[yx[0]]
				|| (int)all->infos.distances[yx[0]] < 0))
			print_spr(all, yx, o, line);
		o++;
		(yx[1])++;
	}
}

void	print_sprite_bis(t_all *all, int i, t_textur temp)
{
	int		yx[2];
	int		*line;
	int		u;
	int		j;
	double	height;

	height = (double)all->infos.case_size
			* ((double)all->infos.y / all->infos.sprite[i][2]);
	yx[0] = all->infos.sprite[i][3];
	u = (int)(round((double)all->infos.objet.x
			* (height / (double)all->infos.objet.y)));
	temp.texture = resize(all, &temp, (int)u);
	yx[0] = yx[0] - (temp.x / 2);
	j = 0;
	while (j < temp.x)
	{
		yx[1] = (int)(round(((double)all->infos.y / 2.0) - height / 2.0));
		line = resize_spr(all, (int)(ceil(height)), (int)j, &temp);
		print_sprite_ter(all, i, line, yx);
		(yx[0])++;
		j++;
		free(line);
	}
	ft_free_tab_int(temp.texture);
}

void	print_sprite(t_all *all, double dist, double segment, double div)
{
	int			i;
	t_textur	temp;
	double		d[3];

	i = 0;
	d[0] = dist;
	d[1] = segment;
	d[2] = div;
	get_colonne(all, d);
	while (all->infos.sprite[i + 1])
	{
		if (all->infos.sprite[i][2] <= (double)all->infos.case_size / 5.0
			|| all->infos.sprite[i][3] == 0.0
			|| all->infos.sprite[i][3] == (double)all->infos.x)
		{
			i++;
			continue ;
		}
		temp = copy_text(all, all->infos.objet);
		print_sprite_bis(all, i, temp);
		i++;
	}
}

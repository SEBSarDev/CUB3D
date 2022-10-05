/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deplacement_2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 19:27:05 by ssar              #+#    #+#             */
/*   Updated: 2021/04/05 11:56:06 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	ft_deplacement(t_all *all, int c, int *p)
{
	if ((char)c == 'w' || (char)c == 'W')
	{
		all->perso.center_x = p[0];
		all->perso.center_y = p[1];
	}
	if ((char)c == 's' || (char)c == 'S')
	{
		all->perso.center_x = p[0] + ((p[2] - p[0]) * 2);
		all->perso.center_y = p[1] + ((p[3] - p[1]) * 2);
	}
	if ((char)c == 'a' || (char)c == 'A')
	{
		all->perso.center_x = p[0] + ((p[2] - p[0]) - (p[3] - p[1]));
		all->perso.center_y = p[1] + ((p[3] - p[1]) + (p[2] - p[0]));
	}
	if ((char)c == 'd' || (char)c == 'D')
	{
		all->perso.center_x = p[0] + ((p[2] - p[0]) + (p[3] - p[1]));
		all->perso.center_y = p[1] + ((p[3] - p[1]) - (p[2] - p[0]));
	}
}

void	move_2d(t_all *all, int c)
{
	int past[4];

	past[0] = all->perso.ori_x;
	past[1] = all->perso.ori_y;
	past[2] = all->perso.center_x;
	past[3] = all->perso.center_y;
	ft_deplacement(all, c, past);
	all->perso.ori_x = past[0] + (all->perso.center_x - past[2]);
	all->perso.ori_y = past[1] + (all->perso.center_y - past[3]);
	if (check_perso_in_map(all) == 0)
	{
		all->perso.center_x = past[2];
		all->perso.center_y = past[3];
		all->perso.ori_x = past[0];
		all->perso.ori_y = past[1];
	}
	rayon(all);
}

void	ft_rotate(t_all *all, int c)
{
	if (c == 65363)
	{
		all->perso.angle -= 0.1;
		if (all->perso.angle < 0)
			all->perso.angle += 2 * PI;
		all->perso.ori_x = all->perso.center_x
				+ (all->infos.case_size / 4) * cos(all->perso.angle);
		all->perso.ori_y = all->perso.center_y
				- (all->infos.case_size / 4) * sin(all->perso.angle);
	}
	if (c == 65361)
	{
		all->perso.angle += 0.1;
		if (all->perso.angle > 2 * PI)
			all->perso.angle -= 2 * PI;
		all->perso.ori_x = all->perso.center_x
			+ (all->infos.case_size / 4) * cos(all->perso.angle);
		all->perso.ori_y = all->perso.center_y
			- (all->infos.case_size / 4) * sin(all->perso.angle);
	}
}

void	rotate_2d(t_all *all, int c)
{
	int stock_y;
	int stock_x;

	stock_y = all->perso.ori_y;
	stock_x = all->perso.ori_x;
	ft_rotate(all, c);
	if (check_perso_in_map(all) == 0)
	{
		all->perso.ori_x = stock_x;
		all->perso.ori_y = stock_y;
	}
	rayon(all);
}

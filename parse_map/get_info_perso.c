/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_perso.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:07:05 by ssar              #+#    #+#             */
/*   Updated: 2021/04/08 22:23:33 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

void	init_orientation(char c, t_info infos, t_perso *perso)
{
	if (c == 'S')
	{
		perso->ori_x = perso->center_x;
		perso->ori_y = perso->center_y + (infos.case_size / 4);
		perso->angle = X3PI2;
	}
	if (c == 'N')
	{
		perso->ori_x = perso->center_x;
		perso->ori_y = perso->center_y - (infos.case_size / 4);
		perso->angle = PI2;
	}
	if (c == 'E')
	{
		perso->ori_x = perso->center_x + (infos.case_size / 4);
		perso->ori_y = perso->center_y;
		perso->angle = 0;
	}
	if (c == 'W')
	{
		perso->ori_x = perso->center_x - (infos.case_size / 4);
		perso->ori_y = perso->center_y;
		perso->angle = PI;
	}
}

void	init_mov(t_perso *perso)
{
	perso->w = 0;
	perso->a = 0;
	perso->s = 0;
	perso->d = 0;
	perso->dr = 0;
	perso->g = 0;
}

t_perso	init_perso(t_info infos)
{
	int		y;
	int		x;
	int		pos;
	t_perso	perso;

	y = 0;
	pos = 0;
	while (infos.map[y] && pos == 0)
	{
		x = 0;
		while (infos.map[y][x] && pos == 0)
		{
			if (ft_in("NSWE", infos.map[y][x]) != -1)
				pos = 1;
			x++;
		}
		y++;
	}
	x--;
	y--;
	perso.center_x = (x * infos.case_size) + (infos.case_size / 2);
	perso.center_y = (y * infos.case_size) + (infos.case_size / 2);
	init_orientation(infos.map[y][x], infos, &perso);
	init_mov(&perso);
	return (perso);
}

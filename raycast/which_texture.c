/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:03:06 by ssar              #+#    #+#             */
/*   Updated: 2021/04/04 21:02:08 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	check_modulo(t_all *all, t_xy xy, int size, int si)
{
	if (check_border(all, xy, si) != 0)
		return (check_border(all, xy, si));
	if ((all->infos.map[((xy.y - 1) / size)][((xy.x - si) / size)] == '1'
	|| all->infos.map[((xy.y - 1) / size)][((xy.x + si) / size)] == '1')
	&& (all->infos.map[((xy.y + si) / size)][((xy.x - 1) / size)] != '1'
	&& all->infos.map[((xy.y - si) / size)][((xy.x - 1) / size)] == '1'))
		return (1);
	if ((all->infos.map[(xy.y / size)][((xy.x - si) / size)] == '1'
	|| all->infos.map[(xy.y / size)][((xy.x + si) / size)] == '1')
	&& (all->infos.map[((xy.y - si) / size)][(xy.x / size)] != '1'
	&& all->infos.map[((xy.y + si) / size)][(xy.x / size)] == '1'))
		return (3);
	if ((all->infos.map[((xy.y - si) / size)][((xy.x - 1) / size)] == '1'
	|| all->infos.map[((xy.y + si) / size)][((xy.x - 1) / size)] == '1')
	&& (all->infos.map[(xy.y / size)][((xy.x + si) / size)] != '1'
	&& all->infos.map[(xy.y / size)][((xy.x - si) / size)] == '1'))
		return (4);
	if ((all->infos.map[((xy.y - si) / size)][(xy.x / size)] == '1'
	|| all->infos.map[((xy.y + si) / size)][(xy.x / size)] == '1')
	&& (all->infos.map[(xy.y / size)][((xy.x - si) / size)] != '1'
	&& all->infos.map[(xy.y / size)][((xy.x + si) / size)] == '1'))
		return (2);
	return (0);
}

int	check_first_corner(t_all *all, t_xy xy, int size)
{
	if (check_border(all, xy, 1) != 0)
		return (check_border(all, xy, 1));
	if (all->infos.map[((xy.y - 1) / size)][((xy.x) / size)] != '1'
	&& all->infos.map[((xy.y + 1) / size)][((xy.x) / size)] == '1'
	&& all->infos.map[((xy.y) / size)][((xy.x + 1) / size)] == '1'
	&& all->infos.map[((xy.y) / size)][((xy.x - 1) / size)] != '1')
	{
		if ((xy.x - all->perso.center_x) >= 0
			&& xy.y - all->perso.center_y <= 0)
			return (2);
		else
			return (3);
	}
	if (all->infos.map[((xy.y - 1) / size)][((xy.x - 1) / size)] != '1'
	&& all->infos.map[((xy.y + 1) / size)][((xy.x - 1) / size)] == '1'
	&& all->infos.map[((xy.y) / size)][((xy.x + 1) / size)] != '1'
	&& all->infos.map[((xy.y) / size)][((xy.x - 1) / size)] == '1')
	{
		if ((xy.x - all->perso.center_x) <= 0
			&& xy.y - all->perso.center_y <= 0)
			return (4);
		else
			return (3);
	}
	return (0);
}

int	check_snd_corner(t_all *all, t_xy xy, int size)
{
	if (check_border(all, xy, 1) != 0)
		return (check_border(all, xy, 1));
	if (all->infos.map[((xy.y - 1) / size)][((xy.x - 1) / size)] == '1'
	&& all->infos.map[((xy.y + 1) / size)][((xy.x - 1) / size)] != '1'
	&& all->infos.map[((xy.y - 1) / size)][((xy.x + 1) / size)] != '1'
	&& all->infos.map[((xy.y - 1) / size)][((xy.x - 1) / size)] == '1')
	{
		if ((xy.x - all->perso.center_x) >= 0
			&& xy.y - all->perso.center_y <= 0)
			return (1);
		else
			return (4);
	}
	if (all->infos.map[((xy.y - 1) / size)][((xy.x) / size)] == '1'
	&& all->infos.map[((xy.y + 1) / size)][((xy.x) / size)] != '1'
	&& all->infos.map[((xy.y - 1) / size)][((xy.x + 1) / size)] == '1'
	&& all->infos.map[((xy.y - 1) / size)][((xy.x - 1) / size)] != '1')
	{
		if ((xy.x - all->perso.center_x) >= 0
			&& xy.y - all->perso.center_y >= 0)
			return (2);
		else
			return (1);
	}
	return (0);
}

int	check_general(t_all *all, t_xy xy, int size)
{
	if (xy.y % size == 0 && xy.x % size != 0)
	{
		if ((xy.y - all->perso.center_y) < 0)
			return (1);
		else
			return (3);
	}
	if (xy.x % size == 0 && xy.y % size != 0)
	{
		if ((xy.x - all->perso.center_x) < 0)
			return (4);
		else
			return (2);
	}
	return (0);
}

int	which_texture(t_all *all, t_xy xy)
{
	int size;
	int a;
	int si;

	a = 0;
	size = all->infos.case_size;
	si = all->infos.case_size / 2;
	a = check_general(all, xy, size);
	if (a != 0)
		return (a);
	a = check_first_corner(all, xy, size);
	if (a != 0)
		return (a);
	a = check_snd_corner(all, xy, size);
	if (a != 0)
		return (a);
	a = check_modulo(all, xy, size, si);
	if (a != 0)
		return (a);
	return (2);
}

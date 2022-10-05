/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:04:25 by ssar              #+#    #+#             */
/*   Updated: 2021/04/08 22:54:57 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	check_perso_in_map(t_all *all)
{
	int pos[8];
	int cen[2];

	cen[0] = all->perso.center_x / all->infos.case_size;
	cen[1] = all->perso.center_y / all->infos.case_size;
	pos[0] = all->perso.center_x / all->infos.case_size;
	pos[1] = (all->perso.center_y - 2) / all->infos.case_size;
	pos[2] = (all->perso.center_x + 1) / all->infos.case_size;
	pos[3] = all->perso.center_y / all->infos.case_size;
	pos[4] = all->perso.center_x / all->infos.case_size;
	pos[5] = (all->perso.center_y + 1) / all->infos.case_size;
	pos[6] = (all->perso.center_x - 2) / all->infos.case_size;
	pos[7] = all->perso.center_y / all->infos.case_size;
	if (all->infos.map[cen[1]][cen[0]] == '1'
		|| all->infos.map[pos[1]][pos[0]] == '1'
		|| all->infos.map[pos[3]][pos[2]] == '1'
		|| all->infos.map[pos[5]][pos[4]] == '1'
		|| all->infos.map[pos[7]][pos[6]] == '1')
		return (0);
	return (1);
}

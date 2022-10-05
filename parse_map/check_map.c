/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:51:38 by ssar              #+#    #+#             */
/*   Updated: 2021/04/04 20:52:16 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

int		check_each_char(char **map, int perso)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_in("012NSEW ", map[y][x]) == -1)
				return (-1);
			if (ft_in("NSEW", map[y][x]) != -1)
			{
				if (perso == 1)
					return (-1);
				perso = 1;
			}
			if (check_carte_fermee(map, x, y) == -1)
				return (-1);
		}
	}
	if (perso == 0)
		return (-1);
	return (1);
}

int		ft_is_it_last(char **map, int y)
{
	int	x;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != ' ' && map[y][x] != '\n')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int		is_void(char **map)
{
	int	y;
	int	x;
	int	vide;

	y = 0;
	while (map[y])
	{
		x = 0;
		vide = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				vide = 1;
			x++;
		}
		if (ft_is_it_last(map, y) == 0 && vide == 0)
			return (-1);
		y++;
	}
	return (1);
}

void	get_new_map(char ***map)
{
	int i;
	int j;

	i = 0;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			if ((*map)[i][j] == ' ')
				(*map)[i][j] = '1';
			j++;
		}
		i++;
	}
}

int		check_map(t_all *all, t_info infos)
{
	int	perso;

	perso = 0;
	if (how_many_line(infos.map) <= 2)
		ft_error(all, NULL, NULL, "Invalid map");
	if (is_void(infos.map) == -1)
		ft_error(all, NULL, NULL, "Something after the map");
	if (check_each_char(infos.map, perso) == -1)
		ft_error(all, NULL, NULL, "Invalid map");
	get_new_map(&all->infos.map);
	return (1);
}

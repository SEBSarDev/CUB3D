/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:58:08 by ssar              #+#    #+#             */
/*   Updated: 2021/03/30 16:02:45 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

int	before(char *str, int pos)
{
	int	is_one;

	is_one = 0;
	while (pos >= 0)
	{
		if (str[pos] == ' ' && is_one == 0)
			return (-1);
		if (str[pos] == '1')
			is_one = 1;
		pos--;
	}
	if (is_one == 0)
		return (0);
	return (1);
}

int	after(char *str, int pos)
{
	int	is_one;

	is_one = 0;
	while (str[pos])
	{
		if (str[pos] == ' ' && is_one == 0)
			return (-1);
		if (str[pos] == '1')
			is_one = 1;
		pos++;
	}
	if (is_one == 0)
		return (-1);
	return (1);
}

int	under(char **map, int y, int x)
{
	int	is_one;

	is_one = 0;
	while (map[y])
	{
		if (map[y][x] == ' ' && is_one == 0)
			return (-1);
		if (map[y][x] == '1')
			is_one = 1;
		y++;
	}
	if (is_one == 0)
		return (-1);
	return (1);
}

int	upper(char **map, int y, int x)
{
	int	is_one;

	is_one = 0;
	while (y >= 0)
	{
		if (map[y][x] == ' ' && is_one == 0)
			return (-1);
		if (map[y][x] == '1')
			is_one = 1;
		y--;
	}
	if (is_one == 0)
		return (-1);
	return (1);
}

int	check_carte_fermee(char **map, int x, int y)
{
	if (ft_in("02NSWE", map[y][x]) != -1)
	{
		if (before(map[y], x) == 1 && after(map[y], x) == 1
			&& under(map, y, x) == 1 && upper(map, y, x) == 1)
			return (1);
		return (-1);
	}
	return (1);
}

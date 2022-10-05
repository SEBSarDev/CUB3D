/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 16:38:21 by ssar              #+#    #+#             */
/*   Updated: 2021/04/09 22:20:08 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

int	how_many_line(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

int	last_num(char *str)
{
	int	i;

	i = ft_len(str) - 1;
	while (str[i] && ft_in("012NSEW", str[i]) == -1)
		i--;
	return (i);
}

int	ok(t_all *all)
{
	rayon(all);
	return (1);
}

int	point_cub(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'b')
		return (0);
	if (str[i - 2] != 'u')
		return (0);
	if (str[i - 3] != 'c')
		return (0);
	if (str[i - 4] != '.')
		return (0);
	return (1);
}

int	ft_comp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i] && s1[i])
	{
		if (s2[i] != s1[i])
			return (0);
		i++;
	}
	if (s2[i])
		return (0);
	if (s1[i])
		return (0);
	return (1);
}

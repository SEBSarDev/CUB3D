/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_res_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:34:13 by ssar              #+#    #+#             */
/*   Updated: 2021/04/07 15:36:58 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

int		get_last_line(char **map)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				count++;
				while (map[y][x + 1])
					x++;
			}
			x++;
		}
		y++;
	}
	return (count);
}

void	color_fc(t_all *all, char *str, int *floor_ceil)
{
	int	i;
	int r;
	int g;
	int b;

	i = 0;
	while (ft_in("0123456789", str[i]) == -1 && str[i])
		i++;
	r = ft_atoi(&str[i]);
	while (ft_in("0123456789", str[i]) >= 0 && str[i])
		i++;
	while (ft_in("0123456789", str[i]) == -1 && str[i])
		i++;
	g = ft_atoi(&str[i]);
	while (ft_in("0123456789", str[i]) >= 0 && str[i])
		i++;
	while (ft_in("0123456789", str[i]) == -1 && str[i])
		i++;
	b = ft_atoi(&str[i]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		ft_error(all, NULL, NULL, "Colors must be >= 0 and <= 255");
	*floor_ceil = r << 16 | g << 8 | b;
}

void	get_colors(t_all *all, char *str, t_info *infos)
{
	int	i;

	i = 0;
	while (!(str[i] == 'F' || str[i] == 'C'))
		i++;
	if (str[i] == 'F')
	{
		if (infos->erreur_parse[2] == 1)
			ft_error(all, NULL, NULL, "Floor defined several times");
		color_fc(all, &str[i], &infos->sol);
		infos->erreur_parse[2] = 1;
	}
	else
	{
		if (infos->erreur_parse[3] == 1)
			ft_error(all, NULL, NULL, "Ceil defined several times");
		color_fc(all, &str[i], &infos->plafond);
		infos->erreur_parse[3] = 1;
	}
}

void	get_resolution(t_all *all, char *str, t_info *infos, void *mlx_ptr)
{
	int	i;
	int	y;
	int	x;

	if (infos->erreur_parse[1] == 1)
		ft_error(all, NULL, NULL, "Resolution is define twice");
	i = 0;
	mlx_get_screen_size(mlx_ptr, &x, &y);
	while (str[i] != 'R')
		i++;
	i++;
	while (str[i] == ' ')
		i++;
	infos->x = ft_atoi(&str[i]);
	while (ft_in("0123456789", str[i]) >= 0)
		i++;
	infos->y = ft_atoi(&str[i]);
	infos->real_y = infos->y;
	infos->real_x = infos->x;
	if (infos->x > x || infos->y > y)
	{
		infos->x = x;
		infos->y = y;
	}
	infos->erreur_parse[1] = 1;
}

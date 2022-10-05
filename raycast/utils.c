/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 09:27:27 by ssar              #+#    #+#             */
/*   Updated: 2021/04/05 11:55:24 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int		ft_free_tab_int_size(double **tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (i);
}

int		get_last_line_int(double **map)
{
	int y;
	int count;

	y = 0;
	count = 0;
	while (map[y] != 0)
	{
		count++;
		y++;
	}
	return (count);
}

double	**copy_tab(t_all *all, int x, int y, double **tab)
{
	int		i;
	int		j;
	double	**stock;

	i = -1;
	stock = (double **)malloc(sizeof(double *) * (y + 1));
	if (!stock)
		ft_error(all, (char **)tab, NULL, strerror(errno));
	while (++i < y)
	{
		stock[i] = (double *)malloc(sizeof(double) * (x + 1));
		if (!stock[i])
		{
			ft_free_tab_int((int **)tab);
			ft_error(all, (char **)stock, NULL, strerror(errno));
		}
		j = -1;
		while (++j < x)
			stock[i][j] = tab[i][j];
		stock[i][x] = '\0';
	}
	stock[y] = 0;
	return (stock);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;
	int		bpp;

	bpp = data->bits_per_pixel;
	dest = data->addr + (y * data->line_length + x * (bpp / 8));
	*(unsigned int *)dest = color;
}

int		check_border(t_all *all, t_xy xy, int d)
{
	check_donne(all, &xy.x, &xy.y);
	if (xy.y - d < 0)
		return (1);
	if (xy.x - d < 0)
		return (4);
	if (xy.y + d >= all->infos.map_y)
		return (3);
	if (xy.x + d >= all->infos.map_x)
		return (2);
	return (0);
}

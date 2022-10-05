/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:48:46 by ssar              #+#    #+#             */
/*   Updated: 2021/04/05 11:50:12 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	print_floor(t_all *all, int *data, int y)
{
	while (y < all->infos.y)
	{
		if (all->infos.save == 1)
			all->infos.bmp[y][data[0]] = all->infos.sol;
		else
			my_mlx_pixel_put(&all->img, data[0], y, all->infos.sol);
		y++;
	}
}

void	print_ceil(t_all *all, int *data, int y)
{
	while (y > 0)
	{
		if (all->infos.save == 1)
			all->infos.bmp[y][data[0]] = all->infos.plafond;
		else
			my_mlx_pixel_put(&all->img, data[0], y, all->infos.plafond);
		y--;
	}
}

void	fill_resize_bis(double *height, double *stock, t_textur *t, int **line)
{
	int		i;
	int		u;
	int		j;
	int		hit;
	double	div;

	div = stock[0];
	hit = (int)stock[1];
	i = (height[1] / 2) - 1;
	u = (height[0] / 2) - 1;
	while (++u < height[0])
	{
		i++;
		j = (int)(floor((double)i * div));
		(*line)[u] = t->texture[j][hit];
	}
	i = (height[1] / 2) + 1;
	u = (height[0] / 2) + 1;
	while (--u >= 0)
	{
		i--;
		j = (int)(floor((double)i * div));
		(*line)[u] = t->texture[j][hit];
	}
}

int		*fill_resize(t_all *all, double *height, t_xy *xy, t_textur *text)
{
	int		*line;
	double	div;
	int		hit;
	double	stock[2];

	hit = (int)(xy->hit) % all->infos.case_size;
	if (height[0] <= 0 || height[0] > 3000)
		height[0] = all->infos.x;
	line = (int *)malloc(sizeof(int) * ((int)height[0] + 1));
	if (!line)
		ft_error(all, NULL, NULL, strerror(errno));
	line[(int)height[0]] = '\0';
	div = (double)text->y / height[1];
	stock[0] = div;
	stock[1] = (double)hit;
	fill_resize_bis(height, stock, text, &line);
	return (line);
}

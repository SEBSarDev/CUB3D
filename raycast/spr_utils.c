/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 13:18:47 by ssar              #+#    #+#             */
/*   Updated: 2021/04/08 22:29:54 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void		swap_val(double *s1, double *s2)
{
	double stock0;
	double stock1;
	double stock2;
	double stock3;

	stock0 = s1[0];
	stock1 = s1[1];
	stock2 = s1[2];
	stock3 = s1[3];
	s1[0] = s2[0];
	s1[1] = s2[1];
	s1[2] = s2[2];
	s1[3] = s2[3];
	s2[0] = stock0;
	s2[1] = stock1;
	s2[2] = stock2;
	s2[3] = stock3;
}

void		get_sort_sprite(t_all *all)
{
	int		i;

	i = 0;
	while (all->infos.sprite[i + 1])
	{
		if (all->infos.sprite[i][2] < all->infos.sprite[i + 1][2])
		{
			swap_val(all->infos.sprite[i], all->infos.sprite[i + 1]);
			i = -1;
		}
		i++;
	}
}

t_textur	copy_text(t_all *all, t_textur sprite)
{
	int			ij[2];
	t_textur	stock;

	ij[0] = -1;
	stock.x = sprite.x;
	stock.y = sprite.y;
	stock.temp = (int **)malloc(sizeof(int *) * (sprite.y + 1));
	if (stock.temp == NULL)
		ft_error(all, NULL, NULL, strerror(errno));
	while (++(ij[0]) < sprite.y)
	{
		stock.temp[ij[0]] = (int *)malloc(sizeof(int) * (sprite.x + 1));
		if (stock.temp[ij[0]] == NULL)
			ft_error(all, (char **)stock.temp, NULL, strerror(errno));
	}
	ij[0] = -1;
	while (++(ij[0]) < sprite.y)
	{
		ij[1] = -1;
		while (++(ij[1]) < sprite.x)
			stock.temp[ij[0]][ij[1]] = sprite.texture[ij[0]][ij[1]];
		stock.temp[ij[0]][ij[1]] = '\0';
	}
	stock.temp[ij[0]] = 0;
	return (stock);
}

int			*resize_spr(t_all *all, int height, int u, t_textur *text)
{
	int *line;
	int i;
	int j;

	line = (int *)malloc(sizeof(int) * (height + 1));
	if (!line)
		ft_error(all, NULL, (char *)line, strerror(errno));
	line[height] = '\0';
	i = (height / 2) - 1;
	while (++i < height)
	{
		j = (int)(floor((double)i * ((double)text->y / (double)height)));
		line[i] = text->texture[j][u];
		if (line[i] == 0 && all->infos.save == 1)
			line[i] = -1;
	}
	i = (height / 2) + 1;
	while (--i >= 0)
	{
		j = (int)(floor((double)i * ((double)text->y / (double)height)));
		line[i] = text->texture[j][u];
		if (line[i] == 0 && all->infos.save == 1)
			line[i] = -1;
	}
	return (line);
}

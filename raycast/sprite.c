/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:26:03 by ssar              #+#    #+#             */
/*   Updated: 2021/03/30 18:06:52 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void	ft_add_sprite(t_all *all, int k, double *src, double fish)
{
	all->infos.sprite[k][0] = src[0];
	all->infos.sprite[k][1] = src[1];
	all->infos.sprite[k][2] = src[2] * cos(fish);
	all->infos.sprite[k][3] = src[3];
	all->infos.sprite[k][4] = '\0';
}

void	ft_tri(t_all *all, double **src, double fish, int *k)
{
	int stop;
	int i;
	int j;
	int s;

	s = all->infos.case_size;
	i = 0;
	while (src[++i])
	{
		stop = 0;
		j = -1;
		while (all->infos.stock_sprite[++j] && stop == 0)
		{
			if ((int)(floor(all->infos.stock_sprite[j][0]
					/ s)) == (int)(floor(src[i][0] / s))
					&& (int)(floor(all->infos.stock_sprite[j][1]
					/ s)) == (int)(floor(src[i][1] / s)))
				stop = 1;
		}
		if (stop == 0)
		{
			ft_add_sprite(all, *k, src[i], fish);
			(*k)++;
		}
	}
}

void	ft_reprise_spr(t_all *all, int i)
{
	all->infos.sprite[i][0] = all->infos.stock_sprite[i][0];
	all->infos.sprite[i][1] = all->infos.stock_sprite[i][1];
	all->infos.sprite[i][2] = all->infos.stock_sprite[i][2];
	all->infos.sprite[i][3] = all->infos.stock_sprite[i][3];
	all->infos.sprite[i][4] = '\0';
}

int		create_temp_spr(t_all *all, int size)
{
	int i;

	all->infos.sprite = (double **)malloc(sizeof(double *) * (size + 1));
	if (!all->infos.sprite)
		ft_error(all, (char **)all->infos.stock_sprite, NULL, strerror(errno));
	i = -1;
	while (++i < size)
	{
		all->infos.sprite[i] = (double *)malloc(sizeof(double) * 5);
		if (!all->infos.sprite[i])
		{
			ft_free_tab_int((int **)all->infos.stock_sprite);
			ft_error(all, (char **)all->infos.sprite, NULL, strerror(errno));
		}
	}
	i = -1;
	while (all->infos.stock_sprite[++i])
		ft_reprise_spr(all, i);
	return (i);
}

void	fill_sprite(t_all *all, double **src, double fish)
{
	int size;
	int k;
	int last;

	last = get_last_line_int(all->infos.sprite);
	size = get_last_line_int(all->infos.sprite) + get_last_line_int(src);
	all->infos.stock_sprite = copy_tab(all, 4, last, all->infos.sprite);
	ft_free_tab_int((int **)all->infos.sprite);
	k = create_temp_spr(all, size);
	ft_tri(all, src, fish, &k);
	ft_free_tab_int((int **)all->infos.stock_sprite);
	all->infos.stock_sprite = copy_tab(all, 4, k, all->infos.sprite);
	ft_free_tab_int_size(all->infos.sprite, size);
	last = get_last_line_int(all->infos.stock_sprite);
	all->infos.sprite = copy_tab(all, 4, last, all->infos.stock_sprite);
	ft_free_tab_int((int **)all->infos.stock_sprite);
}

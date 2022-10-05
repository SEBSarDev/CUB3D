/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_spr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:51:49 by ssar              #+#    #+#             */
/*   Updated: 2021/04/07 13:00:24 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

double	**create_stock(t_all *all, double **s)
{
	double	**tab;
	int		i;
	int		last;

	last = get_last_line_int(s);
	tab = (double **)malloc(sizeof(double *) * (last + 2));
	if (!tab)
		ft_error(all, NULL, NULL, strerror(errno));
	i = -1;
	while (++i < last + 1)
	{
		tab[i] = (double *)malloc(sizeof(double) * 5);
		if (!tab[i])
			ft_error(all, (char **)tab, NULL, strerror(errno));
	}
	i = -1;
	while (++i < last)
	{
		tab[i][0] = s[i][0];
		tab[i][1] = s[i][1];
		tab[i][2] = s[i][2];
		tab[i][3] = s[i][3];
		tab[i][4] = '\0';
	}
	return (tab);
}

void	fill_spr(t_all *all, int *yx, double ***new, int last)
{
	int size;

	size = (double)all->infos.case_size;
	(*new)[last][0] = size * floor((double)yx[0] / size) + size / 2.0;
	(*new)[last][1] = size * floor((double)yx[1] / size) + size / 2.0;
	(*new)[last][2] = sqrt((((double)all->perso.center_x - (*new)[last][0])
						* ((double)all->perso.center_x - (*new)[last][0]))
						+ (((double)all->perso.center_y - (*new)[last][1])
						* ((double)all->perso.center_y - (*new)[last][1])));
	yx[0] = (*new)[last][0] - all->perso.center_x;
	yx[1] = all->perso.center_y - (*new)[last][1];
	(*new)[last][3] = acos((double)yx[0]
			/ sqrt((double)yx[0]
			* (double)yx[0] + ((double)yx[1] * (double)yx[1])));
	if (yx[1] < 0)
		(*new)[last][3] = (PI - (*new)[last][3]) + PI;
	if ((*new)[last][3] < 0)
		(*new)[last][3] += X2PI;
	if ((*new)[last][3] > X2PI)
		(*new)[last][3] -= X2PI;
	(*new)[last][4] = '\0';
	(*new)[last + 1] = 0;
}

double	**stock_sprite(t_all *all, int *yx, double **s)
{
	int		i;
	double	**new;
	int		last;
	int		size;

	size = all->infos.case_size;
	last = get_last_line_int(s);
	i = 1;
	while (s[i])
	{
		if (yx[0] / size == (int)s[i][0] / size
			&& yx[1] / size == (int)s[i][1] / size)
			return (s);
		i++;
	}
	new = create_stock(all, s);
	fill_spr(all, yx, &new, last);
	ft_free_tab_int((int **)s);
	return (new);
}

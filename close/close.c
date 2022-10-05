/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 11:10:56 by ssar              #+#    #+#             */
/*   Updated: 2021/04/09 22:17:02 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/close.h"

void	free_infos(t_all *all)
{
	if (all->infos.erreur_parse[9] == 1)
		ft_free_tab(all->infos.map);
	if (all->infos.erreur_parse[4] == 1)
		ft_free_tab_int(all->infos.nord.temp);
	if (all->infos.erreur_parse[7] == 1)
		ft_free_tab_int(all->infos.sud.temp);
	if (all->infos.erreur_parse[6] == 1)
		ft_free_tab_int(all->infos.est.temp);
	if (all->infos.erreur_parse[5] == 1)
		ft_free_tab_int(all->infos.ouest.temp);
	if (all->infos.erreur_parse[12] == 1)
		ft_free_tab_int(all->infos.nord.texture);
	if (all->infos.erreur_parse[13] == 1)
		ft_free_tab_int(all->infos.sud.texture);
	if (all->infos.erreur_parse[14] == 1)
		ft_free_tab_int(all->infos.est.texture);
	if (all->infos.erreur_parse[15] == 1)
		ft_free_tab_int(all->infos.ouest.texture);
	if (all->infos.erreur_parse[8] == 1)
		ft_free_tab_int(all->infos.objet.texture);
	if (all->infos.erreur_parse[10] == 1)
		free(all->infos.distances);
	mlx_destroy_display(all->vars.mlx);
	free(all->vars.mlx);
}

int		free_close(t_all *all)
{
	mlx_loop_end(all->vars.mlx);
	mlx_destroy_window(all->vars.mlx, all->vars.win);
	mlx_destroy_image(all->vars.mlx, all->img.img);
	return (0);
}

int		key_release(int c, t_all *all)
{
	if (c == 65307)
		free_close(all);
	else if (c == 65361)
		all->perso.g = 0;
	else if (c == 65363)
		all->perso.dr = 0;
	else if (c == 'w' || c == 'W')
		all->perso.w = 0;
	else if (c == 'a' || c == 'A')
		all->perso.a = 0;
	else if (c == 's' || c == 'S')
		all->perso.s = 0;
	else if (c == 'd' || c == 'D')
		all->perso.d = 0;
	return (0);
}

int		key_press(int c, t_all *all)
{
	if (c == 'w' || c == 'W')
		all->perso.w = 1;
	else if (c == 'a' || c == 'A')
		all->perso.a = 1;
	else if (c == 's' || c == 'S')
		all->perso.s = 1;
	else if (c == 'd' || c == 'D')
		all->perso.d = 1;
	else if (c == 65361)
		all->perso.g = 1;
	else if (c == 65363)
		all->perso.dr = 1;
	return (0);
}

int		check_loop(t_all *all)
{
	if (all->perso.w == 1)
		move_2d(all, 'w');
	else if (all->perso.a == 1)
		move_2d(all, 'a');
	else if (all->perso.s == 1)
		move_2d(all, 's');
	else if (all->perso.d == 1)
		move_2d(all, 'd');
	else if (all->perso.dr == 1)
		rotate_2d(all, 65363);
	else if (all->perso.g == 1)
		rotate_2d(all, 65361);
	return (0);
}

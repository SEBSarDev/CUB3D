/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erreur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:34:42 by ssar              #+#    #+#             */
/*   Updated: 2021/04/07 15:37:45 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/close.h"

void	ft_error(t_all *all, char **tab, char *line, char *print)
{
	int i;

	i = -1;
	if (tab != NULL)
		ft_free_tab(tab);
	if (line != NULL)
		free(line);
	if (all->infos.erreur_parse[11] == 1)
	{
		mlx_loop_end(all->vars.mlx);
		mlx_destroy_window(all->vars.mlx, all->vars.win);
		mlx_destroy_image(all->vars.mlx, all->img.img);
	}
	free_infos(all);
	write(1, "Error\n", 6);
	while (print[++i])
		write(1, &print[i], 1);
	write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}

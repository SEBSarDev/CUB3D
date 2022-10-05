/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:57:36 by ssar              #+#    #+#             */
/*   Updated: 2021/04/08 22:24:08 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

int		**fill_res(int **new_text, double div, int size, t_textur *text)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < text->y)
	{
		j = 0;
		while (j < size)
		{
			k = (int)(floor((double)j * div));
			new_text[i][j] = text->temp[i][k];
			j++;
		}
		new_text[i][j] = '\0';
		i++;
	}
	new_text[i] = 0;
	text->x = size;
	ft_free_tab_int(text->temp);
	return (new_text);
}

int		**resize(t_all *all, t_textur *text, int size)
{
	int		**new_text;
	int		i;
	double	div;

	i = 0;
	new_text = (int **)malloc(sizeof(int *) * (text->y + 1));
	if (new_text == NULL)
		ft_error(all, NULL, NULL, strerror(errno));
	while (i < text->y)
	{
		new_text[i] = (int *)malloc(sizeof(int) * (size + 1));
		if (new_text[i] == NULL)
			ft_error(all, (char **)new_text, NULL, strerror(errno));
		i++;
	}
	div = (double)text->x / (double)size;
	return (fill_res(new_text, div, size, text));
}

t_info	resize_text_via_map(t_all *all, t_info *infos)
{
	if (all->infos.erreur_parse[4] == 1)
	{
		infos->nord.texture = resize(all, &infos->nord, infos->case_size);
		all->infos.erreur_parse[4] = 0;
		all->infos.erreur_parse[12] = 1;
	}
	if (all->infos.erreur_parse[7] == 1)
	{
		infos->sud.texture = resize(all, &infos->sud, infos->case_size);
		all->infos.erreur_parse[7] = 0;
		all->infos.erreur_parse[13] = 1;
	}
	if (all->infos.erreur_parse[6] == 1)
	{
		infos->est.texture = resize(all, &infos->est, infos->case_size);
		all->infos.erreur_parse[6] = 0;
		all->infos.erreur_parse[14] = 1;
	}
	if (all->infos.erreur_parse[5] == 1)
	{
		infos->ouest.texture = resize(all, &infos->ouest, infos->case_size);
		all->infos.erreur_parse[5] = 0;
		all->infos.erreur_parse[15] = 1;
	}
	return (*infos);
}

t_info	get_size_map(t_all *all, t_info *infos)
{
	if (infos->nord.x >= infos->est.x && infos->nord.x >= infos->sud.x
			&& infos->nord.x >= infos->ouest.x)
		infos->case_size = infos->nord.x;
	else if (infos->sud.x >= infos->est.x && infos->sud.x >= infos->nord.x
			&& infos->sud.x >= infos->ouest.x)
		infos->case_size = infos->sud.x;
	else if (infos->est.x >= infos->nord.x && infos->est.x >= infos->sud.x
			&& infos->est.x >= infos->ouest.x)
		infos->case_size = infos->est.x;
	else if (infos->ouest.x >= infos->est.x && infos->ouest.x >= infos->sud.x
			&& infos->ouest.x >= infos->nord.x)
		infos->case_size = infos->ouest.x;
	else
		infos->case_size = 64;
	infos->map_x = ft_len(infos->map[0]) * infos->case_size;
	infos->map_y = get_last_line(infos->map) * infos->case_size;
	return (resize_text_via_map(all, &all->infos));
}

t_info	ft_read_info(t_all *all, int fd, void *mlx)
{
	char	*line;
	char	c;
	int		a;

	while ((a = get_next_line(fd, &line)) > 0)
	{
		c = ft_which_line(line);
		if (c == 'R')
			get_resolution(all, line, &all->infos, mlx);
		if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			get_paths(all, line, &all->infos, mlx);
		if (c == 'F' || c == 'C')
			get_colors(all, line, &all->infos);
		if (c == '0' || c == '1')
			get_map(all, &line, &all->infos, fd);
		free(line);
	}
	if (a == -1)
		ft_error(all, NULL, line, strerror(errno));
	free(line);
	return (get_size_map(all, &all->infos));
}

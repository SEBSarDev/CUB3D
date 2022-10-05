/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:32:54 by ssar              #+#    #+#             */
/*   Updated: 2021/04/08 22:22:02 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

char	*alloue_path(t_all *all, char *line)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	len = 0;
	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	while (line[i] == ' ' && line[i])
		i++;
	j = i;
	while (!(line[i] > 8 && line[i] < 14) && line[i])
	{
		len++;
		i++;
	}
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		ft_error(all, NULL, NULL, strerror(errno));
	i = 0;
	while (line[j] && line[j] != ' ')
		str[i++] = line[j++];
	str[i] = '\0';
	return (str);
}

int		**get_texture_colors(t_all *all, int x, int y, t_data texture)
{
	int	ij[2];
	int	k;
	int	**stock;

	ij[0] = -1;
	k = -1;
	stock = (int **)malloc(sizeof(int *) * (y + 1));
	if (stock == NULL)
		ft_error(all, NULL, NULL, strerror(errno));
	while (++(ij[0]) < y)
	{
		stock[ij[0]] = (int *)malloc(sizeof(int) * (x + 1));
		if (stock[ij[0]] == NULL)
			ft_error(all, (char **)stock, NULL, strerror(errno));
	}
	ij[0] = -1;
	while (++(ij[0]) < y)
	{
		ij[1] = -1;
		while (++(ij[1]) < x)
			stock[ij[0]][ij[1]] = ((int*)texture.addr)[++k];
		stock[ij[0]][ij[1]] = '\0';
	}
	stock[ij[0]] = 0;
	return (stock);
}

int		**get_texture(t_all *all, t_textur *size, char *str, void *mlx)
{
	t_data	texture;
	int		x;
	int		y;
	int		**stock;

	texture.img = mlx_xpm_file_to_image(mlx, str, &x, &y);
	size->x = x;
	size->y = y;
	size->stock_hit = 0;
	if (texture.img == NULL)
		ft_error(all, NULL, NULL, "XPM error file");
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
			&texture.line_length, &texture.endian);
	stock = get_texture_colors(all, x, y, texture);
	mlx_destroy_image(mlx, texture.img);
	return (stock);
}

void	def_textures(t_all *all, char *path, void *mlx, char c)
{
	if (c == 'N')
	{
		if (all->infos.erreur_parse[4] == 1)
			ft_error(all, NULL, NULL, "North texture defines several times");
		all->infos.nord.temp = get_texture(all, &all->infos.nord, path, mlx);
		all->infos.erreur_parse[4] = 1;
	}
	if (c == 'W')
	{
		if (all->infos.erreur_parse[5] == 1)
			ft_error(all, NULL, NULL, "West texture defines several times");
		all->infos.ouest.temp = get_texture(all, &all->infos.ouest, path, mlx);
		all->infos.erreur_parse[5] = 1;
	}
	if (c == 'E')
	{
		if (all->infos.erreur_parse[6] == 1)
			ft_error(all, NULL, NULL, "East texture defines several times");
		all->infos.est.temp = get_texture(all, &all->infos.est, path, mlx);
		all->infos.erreur_parse[6] = 1;
	}
}

void	get_paths(t_all *all, char *str, t_info *infos, void *mlx)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_in("NWES", str[i]) == -1)
		i++;
	path = alloue_path(all, &str[i]);
	def_textures(all, path, mlx, str[i]);
	if (str[i] == 'S' && str[i + 1] == 'O')
	{
		if (infos->erreur_parse[7] == 1)
			ft_error(all, NULL, NULL, "South texture defines several times");
		infos->sud.temp = get_texture(all, &infos->sud, path, mlx);
		infos->erreur_parse[7] = 1;
	}
	if (str[i] == 'S' && str[i + 1] == ' ')
	{
		if (infos->erreur_parse[8] == 1)
			ft_error(all, NULL, NULL, "Sprite texture defines several times");
		infos->objet.texture = get_texture(all, &infos->objet, path, mlx);
		infos->erreur_parse[8] = 1;
	}
	free(path);
}

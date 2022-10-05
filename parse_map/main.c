/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:36:02 by ssar              #+#    #+#             */
/*   Updated: 2021/04/09 22:21:36 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"
#include "../includes/close.h"
#include "../includes/raycast.h"

void	check_format(t_all *all, int argc, char *argv[])
{
	if (argc < 2 || argc > 3)
		ft_error(all, NULL, NULL, "Wrong number of arguments");
	if (argc == 3 && ft_comp(argv[2], "--save") != 1)
		ft_error(all, NULL, NULL, "Incorrect second argument");
	if (argc == 2 && point_cub(argv[1]) != 1)
		ft_error(all, NULL, NULL, "First argument not a .cub");
}

int		ft_save_image(t_all *all)
{
	int		x;
	int		y;
	void	*bpp;
	void	*ll;

	bpp = &all->img.bits_per_pixel;
	ll = &all->img.line_length;
	x = all->infos.real_x;
	y = all->infos.real_y;
	all->infos.x = all->infos.real_x;
	all->infos.y = all->infos.real_y;
	stock_dist_sprite(all, &all->infos);
	all->img.img = mlx_new_image(all->vars.mlx, x, y);
	all->img.addr = mlx_get_data_addr(all->img.img, bpp, ll, &all->img.endian);
	all->infos.bmp = init_stock_bmp(all, all->infos.x, all->infos.y);
	all->infos.erreur_parse[11] = 1;
	all->infos.save = 1;
	rayon(all);
	bmp_reverse(all);
	bitmap_save(all);
	mlx_destroy_image(all->vars.mlx, all->img.img);
	free_infos(all);
	ft_free_tab_int(all->infos.bmp);
	return (0);
}

int		res(t_all *all)
{
	if (all->perso.w == 0 && all->perso.a == 0 && all->perso.s == 0
		&& all->perso.d == 0 && all->perso.dr == 0 && all->perso.g == 0)
		rayon(all);
	return (1);
}

int		ft_run(t_all *all)
{
	int		x;
	int		y;
	void	*bpp;
	void	*ll;

	bpp = &all->img.bits_per_pixel;
	ll = &all->img.line_length;
	x = all->infos.x;
	y = all->infos.y;
	stock_dist_sprite(all, &all->infos);
	all->infos.save = 0;
	all->vars.win = mlx_new_window(all->vars.mlx, x, y, "cub3d");
	all->img.img = mlx_new_image(all->vars.mlx, all->infos.x, all->infos.y);
	all->img.addr = mlx_get_data_addr(all->img.img, bpp, ll, &all->img.endian);
	all->infos.erreur_parse[11] = 1;
	rayon(all);
	mlx_hook(all->vars.win, 33, 1L << 2, free_close, all);
	mlx_hook(all->vars.win, 14, 1L << 2, res, all);
	mlx_hook(all->vars.win, 9, 1L << 21, ok, all);
	mlx_hook(all->vars.win, 2, 1L << 0, key_press, all);
	mlx_hook(all->vars.win, 3, 1L << 1, key_release, all);
	mlx_loop_hook(all->vars.mlx, check_loop, all);
	mlx_loop(all->vars.mlx);
	free_infos(all);
	return (0);
}

int		main(int argc, char *argv[])
{
	int		fd;
	t_all	all;
	int		i;

	i = -1;
	while (++i < 16)
		all.infos.erreur_parse[i] = 0;
	all.vars.mlx = mlx_init();
	check_format(&all, argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error(&all, NULL, NULL, strerror(errno));
	ft_read_info(&all, fd, all.vars.mlx);
	all.perso = init_perso(all.infos);
	close(fd);
	if (all.infos.erreur_parse[1] == 0 || all.infos.erreur_parse[2] == 0
		|| all.infos.erreur_parse[3] == 0 || all.infos.erreur_parse[8] == 0
		|| all.infos.erreur_parse[9] == 0 || all.infos.erreur_parse[12] == 0
		|| all.infos.erreur_parse[13] == 0 || all.infos.erreur_parse[14] == 0
		|| all.infos.erreur_parse[15] == 0)
		ft_error(&all, NULL, NULL, "Invalid configuration");
	if (argc == 3 && ft_comp(argv[2], "--save") == 1)
		return (ft_save_image(&all));
	else
		return (ft_run(&all));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:14:37 by ssar              #+#    #+#             */
/*   Updated: 2021/04/09 22:21:16 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H

# define CUB_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# define PI 3.14159265359
# define PI2 1.57079632
# define X3PI2 4.71238898
# define X2PI 6.283185307
# include "../mlx_linux/mlx.h"

typedef struct	s_textur
{
	int x;
	int y;
	int **temp;
	int **texture;
	int stock_hit;
	int prec;
}				t_textur;

typedef struct	s_info
{
	int			map_y;
	int			map_x;
	int			x;
	int			y;
	t_textur	nord;
	t_textur	sud;
	t_textur	ouest;
	t_textur	est;
	t_textur	objet;
	int			sol;
	int			plafond;
	char		**map;
	int			case_size;
	int			erreur_parse[16];
	int			hit;
	double		**sprite_x;
	double		**sprite_y;
	double		**sprite;
	double		**stock_sprite;
	double		*distances;
	int			real_y;
	int			real_x;
	int			save;
	int			**bmp;
}				t_info;

typedef struct	s_xy
{
	int		x;
	int		y;
	double	angle;
	int		mur;
	double	stock_y;
	double	stock_x;
	double	hit;
	int		ray_y;
	int		ray_x;
}				t_xy;

typedef struct	s_sprite
{
	int		x;
	int		y;
	int		hit;
	double	distance;
}				t_sprite;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_perso
{
	float	center_x;
	float	center_y;
	float	ori_x;
	float	ori_y;
	float	angle;
	int		dr;
	int		g;
	int		a;
	int		s;
	int		w;
	int		d;
}				t_perso;

typedef struct	s_all
{
	t_vars	vars;
	t_info	infos;
	t_data	img;
	t_data	carte;
	t_perso	perso;
}				t_all;

int				ft_free_tab_int(int **tab);
int				**resize(t_all *all, t_textur *text, int size);
int				ft_len_int(int *str);
int				ft_in(char *str, char c);
int				ft_len(char *str);
char			**ft_free_tab(char **tab);
int				ft_atoi(char *str);
void			move_2d(t_all *all, int c);
int				get_last_line(char **map);
void			rotate_2d(t_all *all, int c);
void			rayon(t_all *all);
int				largest_line(char **temp);
int				bitmap_save(t_all *all);
int				**init_stock_bmp(t_all *all, int x, int y);
void			bmp_reverse(t_all *all);
void			ft_error(t_all *all, char **tab, char *line, char *print);
int				key_release(int c, t_all *all);
int				key_press(int c, t_all *all);
int				check_loop(t_all *all);
void			check_donne(t_all *all, int *x, int *y);
int				check_border(t_all *all, t_xy xy, int d);
int				ok(t_all *all);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:03:36 by ssar              #+#    #+#             */
/*   Updated: 2021/04/05 13:09:00 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "cub.h"

int			get_2d(t_all *all);
void		get_colonne(t_all *all, double *d);
float		check_horizontal(t_all *all, double angle, t_xy *xy);
float		check_vertical(t_all *all, double angle, t_xy *xy);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		color_perso(t_all *all);
void		print_wall(t_all *all, float dist, int x, t_xy *xy);
int			ray_right(t_all *all, double angle, t_xy *xy, float *b);
int			ray_left(t_all *all, double angle, t_xy *xy, float *b);
int			ray_down(t_all *all, double angle, t_xy *xy, float *a);
int			ray_up(t_all *all, double angle, t_xy *xy, float *a);
int			check_perso_in_map(t_all *all);
double		**stock_sprite(t_all *all, int *yx, double **stok);
void		fill_sprite(t_all *all, double **src, double fish);
double		**copy_tab(t_all *all, int x, int y, double **tab);
int			get_last_line_int(double **map);
int			ft_free_tab_int_size(double **tab, int size);
void		get_sort_sprite(t_all *all);
void		print_spr(t_all *all, int *yx, int o, int *line);
void		print_sprite(t_all *all, double dist, double seg, double div);
void		def_angle_bis(double *a, double *s, double *bef);
void		def_angle(t_all *all, double *angle, double *stock, int j);
t_textur	copy_text(t_all *all, t_textur sprite);
int			*resize_spr(t_all *all, int height, int u, t_textur *text);
int			which_texture(t_all *all, t_xy xy);
float		check(t_all *all, double angle, t_xy *xy, int size);
void		check_distance(t_all *all, double angle, t_xy *xy, int size);
void		print_ceil(t_all *all, int *data, int y);
void		print_floor(t_all *all, int *data, int y);

#endif

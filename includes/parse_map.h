/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:44:34 by ssar              #+#    #+#             */
/*   Updated: 2021/03/30 17:53:09 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_H

# define PARSE_MAP_H
# include "cub.h"

t_perso	init_perso(t_info infos);
void	get_colors(t_all *all, char *str, t_info *infos);
void	get_map(t_all *all, char **line, t_info *infos, int fd);
char	**ft_copy_tab(t_all *all, char **temp, int i, int k);
void	get_paths(t_all *all, char *str, t_info *infos, void *mlx);
void	get_resolution(t_all *all, char *str, t_info *infosi, void *mlx);
char	*ft_concate(char *s1, char *s2);
int		ft_compare(char *str, char c);
void	ft_move(char *str, int *size);
char	*ft_dup(char **dest, char *src);
int		ft_free_new(char *new_line);
int		ft_temp_is_n(char **new_line, char *temp, int *size);
int		ft_end_of_line(int fd, char **line, char *new_line);
int		get_next_line(int fd, char **line);
t_info	ft_read_info(t_all *all, int fd, void *mlx);
int		check_map(t_all *all, t_info infos);
int		how_many_line(char **map);
int		last_num(char *str);
int		check_carte_fermee(char **map, int x, int y);
int		**get_texture(t_all *all, t_textur *text, char *str, void *mlx);
int		point_cub(char *str);
int		ft_comp(char *s1, char *s2);
char	ft_which_line(char *str);
void	stock_dist_sprite(t_all *all, t_info *infos);

#endif

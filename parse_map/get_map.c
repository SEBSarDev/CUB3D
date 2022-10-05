/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:35:38 by ssar              #+#    #+#             */
/*   Updated: 2021/04/05 13:23:26 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

void	stock_dist_sprite(t_all *all, t_info *infos)
{
	if (infos->x > 20000)
		ft_error(all, NULL, NULL, "Size too big, can't malloc");
	infos->distances = (double *)malloc(sizeof(double) * (infos->x + 1));
	if (!infos->distances)
		ft_error(all, NULL, NULL, strerror(errno));
	infos->distances[infos->x] = '\0';
	infos->erreur_parse[10] = 1;
}

int		largest_line(char **temp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
			j++;
		if (j > k)
			k = j;
		i++;
	}
	return (k);
}

char	**ft_copy_tab(t_all *all, char **temp, int i, int k)
{
	char	**str;
	int		j;

	str = (char **)malloc(sizeof(char *) * (i + 1));
	if (!str)
		ft_error(all, temp, NULL, strerror(errno));
	i = -1;
	while (temp[++i])
	{
		j = -1;
		str[i] = (char *)malloc(sizeof(char) * k + 1);
		if (!str[i])
		{
			ft_free_tab(temp);
			ft_error(all, str, NULL, strerror(errno));
		}
		while (temp[i][++j])
			str[i][j] = temp[i][j];
		while (j < k)
			str[i][j++] = ' ';
		str[i][j] = '\0';
	}
	str[i] = 0;
	ft_free_tab(temp);
	return (str);
}

char	**get_get_map(t_all *all, char *line, char **temp, int len)
{
	char	**new_temp;
	int		k;
	int		i;
	int		j;

	j = -1;
	i = 0;
	k = largest_line(temp);
	if (k < ft_len(line))
		k = ft_len(line);
	new_temp = ft_copy_tab(all, temp, len, k);
	while (new_temp[i])
		i++;
	new_temp[i] = (char *)malloc(sizeof(char) * k + 1);
	if (!new_temp[i])
		ft_error(all, new_temp, NULL, strerror(errno));
	while (line[++j])
		new_temp[i][j] = line[j];
	while (j < k)
		new_temp[i][j++] = ' ';
	new_temp[i][j] = '\0';
	new_temp[i + 1] = 0;
	return (new_temp);
}

void	get_map(t_all *all, char **line, t_info *infos, int fd)
{
	int		i;
	char	**temp;

	i = 1;
	temp = (char **)malloc(sizeof(char *));
	if (!temp)
		ft_error(all, line, NULL, strerror(errno));
	temp[0] = 0;
	temp = get_get_map(all, *line, temp, i);
	free(*line);
	while (get_next_line(fd, line) > 0)
	{
		temp = get_get_map(all, *line, temp, ++i);
		free(*line);
	}
	infos->erreur_parse[9] = 1;
	infos->map = ft_copy_tab(all, temp, i, largest_line(temp));
	check_map(all, *infos);
}

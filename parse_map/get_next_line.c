/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:17:56 by ssar              #+#    #+#             */
/*   Updated: 2021/03/30 16:05:53 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse_map.h"

int	ft_free_new(char *new_line)
{
	free(new_line);
	return (-1);
}

int	ft_temp_is_n(char **new_line, char *temp, int *size)
{
	ft_move(temp, size);
	*new_line = ft_concate(*new_line, temp);
	if (!*new_line)
		return (-1);
	return (1);
}

int	ft_end_of_line(int fd, char **line, char *new_line)
{
	int			size;
	static char	temp[129] = "\0";

	if (ft_compare(temp, '\n') != 0)
	{
		if (!ft_temp_is_n(&new_line, temp, &size))
			return (ft_free_new(new_line));
	}
	while (ft_compare(temp, '\n') == 0)
	{
		size = read(fd, temp, 128);
		if (size == -1)
			return (ft_free_new(new_line));
		temp[size] = '\0';
		new_line = ft_concate(new_line, temp);
		if (!new_line)
			return (ft_free_new(new_line));
		if (size == 0)
			break ;
	}
	*line = ft_dup(line, new_line);
	if (!(*line))
		return (ft_free_new(new_line));
	free(new_line);
	return (size);
}

int	get_next_line(int fd, char **line)
{
	char	*new_line;
	int		result;

	if (fd < 0 || line == 0)
		return (-1);
	new_line = malloc(sizeof(char));
	if (!new_line)
		return (-1);
	new_line[0] = '\0';
	result = ft_end_of_line(fd, line, new_line);
	if (result == -1)
		return (-1);
	else if (result == 0)
		return (0);
	else
		return (1);
}

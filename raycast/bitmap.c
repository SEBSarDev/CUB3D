/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssar <ssar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:05:05 by ssar              #+#    #+#             */
/*   Updated: 2021/04/07 10:39:36 by ssar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int		**init_stock_bmp(t_all *all, int x, int y)
{
	int **stock;
	int i;

	i = 0;
	if ((x * y) * 4 > 400000000)
		ft_error(all, NULL, NULL, "Size too big, can't malloc");
	stock = (int **)malloc(sizeof(int *) * (y + 1));
	if (!stock)
		ft_error(all, NULL, NULL, strerror(errno));
	while (i < y)
	{
		stock[i] = (int *)malloc(sizeof(int) * (x + 1));
		if (!stock[i])
			ft_error(all, (char **)stock, NULL, strerror(errno));
		stock[i][x] = '\0';
		i++;
	}
	stock[i] = 0;
	return (stock);
}

void	bmp_reverse(t_all *all)
{
	int *temp;
	int i;
	int j;

	temp = (int *)malloc(sizeof(int) * (all->infos.x + 1));
	if (!temp)
		ft_error(all, NULL, NULL, strerror(errno));
	temp[all->infos.x] = '\0';
	i = -1;
	while (++i <= all->infos.y / 2)
	{
		j = -1;
		while (++j < all->infos.x)
			temp[j] = all->infos.bmp[i][j];
		j = -1;
		while ((all->infos.y - (1 + i)) >= 0 && ++j < all->infos.x)
			all->infos.bmp[i][j] = all->infos.bmp[all->infos.y - (1 + i)][j];
		j = -1;
		while (++j < all->infos.x)
			all->infos.bmp[all->infos.y - (1 + i)][j] = temp[j];
	}
	free(temp);
}

void	ft_entete(t_all *all, int fd)
{
	int print;
	int i;

	write(fd, "BM", 2);
	print = (all->infos.x * all->infos.y) * 4 + 54;
	write(fd, &print, 4);
	print = 0;
	write(fd, &print, 2);
	write(fd, &print, 2);
	print = 54;
	write(fd, &print, 4);
	print = 40;
	write(fd, &print, 4);
	write(fd, &all->infos.x, 4);
	write(fd, &all->infos.y, 4);
	print = 1;
	write(fd, &print, 2);
	write(fd, &all->img.bits_per_pixel, 2);
	print = 0;
	i = -1;
	while (++i < 6)
		write(fd, &print, 4);
}

int		bitmap_save(t_all *all)
{
	int	fd;
	int	i;
	int	j;

	fd = open("save_image.bmp", O_CREAT | O_RDWR, 00755);
	if (fd == -1)
		ft_error(all, NULL, NULL, strerror(errno));
	ft_entete(all, fd);
	i = 0;
	while (i < all->infos.y)
	{
		j = 0;
		while (j < all->infos.x)
		{
			write(fd, &(all->infos.bmp)[i][j], 4);
			j++;
		}
		i++;
	}
	close(fd);
	return (1);
}

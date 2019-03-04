/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:29:29 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 08:38:05 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		ft_read_first_time(int fd, int count)
{
	int		i;
	int		row;
	char	buf[100];
	int		size_map;

	size_map = 0;
	row = 0;
	i = -1;
	while ((count = read(fd, buf, 99)))
	{
		i = -1;
		while (buf[++i] != '\0')
		{
			if (!(48 <= buf[i] && buf[i] <= 57) &&
			((buf[i] != '\n')) && ((buf[i] != '\0')))
				return (0);
			else if ((buf[i + 1] == '\0' && count < 99) || (buf[i] == '\n'))
				row++;
			else if (size_map > 3000)
				return (0);
			size_map++;
		}
		ft_bzero(&buf, 99);
	}
	return (row);
}

void	ft_find_player_position(t_elem *s_pixel, int i, int j)
{
	s_pixel->is_player = 1;
	s_pixel->player->x_camera = (j << 6) + 22;
	s_pixel->player->y_camera = (i << 6) + 22;
	s_pixel->map->begin_x_camera = (j << 6) + 22;
	s_pixel->map->begin_y_camera = (i << 6) + 22;
}

int		ft_ft_validate1(t_elem *s_pixel)
{
	s_pixel->size_is_right = s_pixel->size_column;
	s_pixel->size_column = 0;
	if (!(s_pixel->size_row >= 3))
		return (0);
	s_pixel->size_row = 0;
	return (1);
}

int		ft_ft_validate2(t_elem *s_pixel)
{
	if (!(s_pixel->size_row >= 3))
		return (0);
	if (s_pixel->size_column != s_pixel->size_is_right)
		return (0);
	s_pixel->size_column = 0;
	s_pixel->size_row = 0;
	return (1);
}

void	ft_get_width_height(t_elem *s_pixel, int row)
{
	s_pixel->map->map_width = s_pixel->size_is_right << 6;
	s_pixel->map->map_height = row << 6;
}

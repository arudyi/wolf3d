/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:19:47 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 11:36:07 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_draw_walls(t_elem *s_pixel, int x)
{
	int		y;
	double	height;
	int		offset;
	double	step;
	int		tmp_y;

	tmp_y = 0;
	s_pixel->texture->x = x;
	if (s_pixel->walls->if_gor_line == 1)
		offset = s_pixel->walls->offset_x % 64;
	else
		offset = s_pixel->walls->offset_y % 64;
	s_pixel->i = -1;
	height = 64 / s_pixel->walls->len_vec * 1662;
	y = 480 - (height / 2);
	step = (height / 64);
	while (tmp_y <= y)
		ft_pixel_to_image(s_pixel, x, tmp_y++, 0x202020);
	while (++s_pixel->i < height - 10)
		if (!(x > 1920 || y > 960 || x < 0 || y++ < 0))
			ft_pixel_to_image(s_pixel, x, y, ft_get_texture(s_pixel, offset,
			step, (double)s_pixel->i));
	while (y < 960)
		ft_pixel_to_image(s_pixel, x, y++, 0x696969);
}

void	ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	if (!(x > 1919 || x < 0 || y > 959 || y < 0))
	{
		index = s_pixel->size_line * y + (x << 2);
		*(unsigned *)(s_pixel->begin_str + index) = color;
	}
}

int		ft_get_color_part(t_elem *s_pixel, int color)
{
	if (s_pixel->texture->mandatory_mode == 1)
	{
		if (s_pixel->walls->if_gor_line == 1 && CHECK1)
			color = 0xFFFFFF;
		else if (s_pixel->walls->if_gor_line == 1 && CHECK2)
			color = 0x00FFFF;
		else if (s_pixel->walls->if_gor_line == 0 && CHECK3)
			color = 0xFFFF00;
		else
			color = 0xFF00FF;
	}
	else
	{
		if (s_pixel->walls->if_gor_line == 1 && CHECK1)
			color = 0xFFFFFF;
		else if (s_pixel->walls->if_gor_line == 1 && CHECK2)
			color = 0x00FFFF;
		else if (s_pixel->walls->if_gor_line == 0 && CHECK3)
			color = 0xFFFF00;
		else
			color = 0xFF00FF;
	}
	return (color);
}

int		ft_get_texture_part(t_elem *s_pixel, int offset, double step, double y)
{
	int color;
	int index;

	if (s_pixel->texture->mandatory_mode == 1)
	{
		if (s_pixel->walls->if_gor_line == 1 && (0 <= s_pixel->player->dir &&
		s_pixel->player->dir <= 180))
			s_pixel->texture->texture_now = 0;
		else if (s_pixel->walls->if_gor_line == 1 && !(0 <= s_pixel->player->
		dir && s_pixel->player->dir <= 180))
			s_pixel->texture->texture_now = 1;
		else if (s_pixel->walls->if_gor_line == 0 && (90 <= s_pixel->player->
		dir && s_pixel->player->dir <= 270))
			s_pixel->texture->texture_now = 2;
		else
			s_pixel->texture->texture_now = 3;
	}
	y = (y / step);
	index = ((int)y << 8) + (offset << 2);
	color = *(unsigned *)(s_pixel->texture->begin_str_tex[s_pixel->texture->
	texture_now] + index);
	return (color);
}

int		ft_get_texture(t_elem *s_pixel, int offset, double step, double y)
{
	int color;

	if (s_pixel->texture->mandatory_mode == 1)
	{
		if (s_pixel->texture->texture_mode == 0)
			color = ft_get_color_part(s_pixel, 0);
		else
			color = ft_get_texture_part(s_pixel, offset, step, y);
	}
	else
	{
		if (s_pixel->texture->texture_mode == 0)
			color = ft_get_color_part(s_pixel, 0);
		else
			color = ft_get_texture_part(s_pixel, offset, step, y);
	}
	return (color);
}

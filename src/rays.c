/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:18:35 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/03 18:19:09 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void ft_check_gor1(t_elem *s_pixel, double ax, double ay, short int is_inside)
{
	s_pixel->walls->offset_x = ax;
	s_pixel->walls->dot_wall_x = (is_inside == 0) ? ax : -404;
	s_pixel->walls->dot_wall_y = (is_inside == 0) ? ay : -404;
}

void ft_check_gor(t_elem *s_pixel, double dir, double ax, double ay)
{
	short int	is_inside;
	double		xa;
	double		ya;

	is_inside = 1;
	ay = (0 <= dir && dir <= 180) ? ((int)s_pixel->player->y_camera >> 6 << 6) - 1 : ((int)s_pixel->player->y_camera >> 6 << 6) + 64;
	ax = (dir == 90 || dir == 270) ? (int)s_pixel->player->x_camera : (int)s_pixel->player->x_camera + ((int)s_pixel->player->y_camera - ay) / s_pixel->walls->angle_tg;
	ya = (0 <= dir && dir <= 180) ? -64. : 64.;
	xa = (dir == 90 || dir == 270) ? 0. : 64. / s_pixel->walls->angle_tg;
	if (xa != 0. && (180 <= dir && dir <= 360))
		xa = -xa;
	while (is_inside)
	{
		if (ax < 0 || ax > s_pixel->map->map_width - 1 || ay < 0 || ay > s_pixel->map->map_height - 1)
			break ;
		is_inside = (ft_is_wall(s_pixel, ax, ay) == 0) ? 0 : 1;
		if (is_inside == 0 && (ft_is_wall(s_pixel, ax, ay - 1) == 0 && ft_is_wall(s_pixel, ax, ay + 1) == 0))
				is_inside = 1;
		ax = (is_inside == 1) ? ax + xa : ax;
		ay = (is_inside == 1) ? ay + ya : ay;
	}
	ft_check_gor1(s_pixel, ax, ay, is_inside);
}

void ft_check_ver1(t_elem *s_pixel, double bx, double by, short int is_inside)
{
	s_pixel->walls->offset_y = by;
	s_pixel->walls->dot_wall_x = (is_inside == 0) ? bx : -404;
	s_pixel->walls->dot_wall_y = (is_inside == 0) ? by : -404;
}

void ft_check_ver(t_elem *s_pixel, double dir, double bx, double by)
{
	short int	is_inside;
	double		xa;
	double		ya;

	is_inside = 1;
	if (!(dir == 270 || dir == 90))
	{
		bx = (90 <= dir && dir <= 270) ? ((int)s_pixel->player->x_camera >> 6 << 6) - 1. : ((int)s_pixel->player->x_camera >> 6 << 6) + 64.;
		by = (dir == 90 || dir == 270) ? (int)s_pixel->player->y_camera : (int)s_pixel->player->y_camera + ((int)s_pixel->player->x_camera - bx) * s_pixel->walls->angle_tg;
		xa = (90 <= dir && dir <= 270) ? -64. : 64.;
		ya = (dir == 90 || dir == 270) ? 0. : 64. * s_pixel->walls->angle_tg;
		if (ya != 0. && !(90 <= dir && dir <= 270))
			ya = -ya;
		while (is_inside)
		{
			if (bx < 0 || bx > s_pixel->map->map_width - 1 || by < 0 || by > s_pixel->map->map_height - 1)
				break ;
			is_inside = (ft_is_wall(s_pixel, bx, by) == 0) ? 0 : 1;
			if (is_inside == 0 && (ft_is_wall(s_pixel, bx - 1, by) == 0 && ft_is_wall(s_pixel, bx + 1, by) == 0))
				is_inside = 1;
			bx = (is_inside == 1) ? bx + xa : bx;
			by = (is_inside == 1) ? by + ya : by;
		}
	}
	ft_check_ver1(s_pixel, bx, by, is_inside);
}
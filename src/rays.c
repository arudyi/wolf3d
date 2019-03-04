/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:18:35 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 11:56:09 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_check_gor1(t_elem *s_pixel, double ax, double ay, short int is_in)
{
	s_pixel->walls->offset_x = ax;
	s_pixel->walls->dot_wall_x = (is_in == 0) ? ax : -404;
	s_pixel->walls->dot_wall_y = (is_in == 0) ? ay : -404;
}

void	ft_check_gor(t_elem *s_pixel, double dir, double ax, double ay)
{
	short int	is_inside;
	double		xa;
	double		ya;

	is_inside = 1;
	ay = (0 <= dir && dir <= 180) ? C_GOR_AX1 : C_GOR_AX2;
	ax = (dir == 90 || dir == 270) ? C_G_Y1 : C_G_Y2 + ((C_G_Y3) / C_G_Y4);
	ya = (0 <= dir && dir <= 180) ? -64. : 64.;
	xa = (dir == 90 || dir == 270) ? 0. : 64. / s_pixel->walls->angle_tg;
	if (xa != 0. && (180 <= dir && dir <= 360))
		xa = -xa;
	while (is_inside)
	{
		if (ax < 0 || ax > s_pixel->map->map_width - 1 || ay < 0 || ay >
		s_pixel->map->map_height - 1)
			break ;
		is_inside = (ft_is_wall(s_pixel, ax, ay) == 0) ? 0 : 1;
		if (is_inside == 0 && (ft_is_wall(s_pixel, ax, ay - 1) == 0 &&
		ft_is_wall(s_pixel, ax, ay + 1) == 0))
			is_inside = 1;
		ax = (is_inside == 1) ? ax + xa : ax;
		ay = (is_inside == 1) ? ay + ya : ay;
	}
	ft_check_gor1(s_pixel, ax, ay, is_inside);
}

void	ft_check_ver1(t_elem *s_pixel, double bx, double by, short int is_in)
{
	s_pixel->walls->offset_y = by;
	s_pixel->walls->dot_wall_x = (is_in == 0) ? bx : -404;
	s_pixel->walls->dot_wall_y = (is_in == 0) ? by : -404;
}

void	ft_check_ver(t_elem *s_pixel, double dir, double bx, double by)
{
	short int	i;
	double		xa;
	double		ya;

	i = 1;
	if (!(dir == 270 || dir == 90))
	{
		bx = (90 <= dir && dir <= 270) ? C_VER_BX1 : C_VER_BX2;
		by = (dir == 90 || dir == 270) ? C_V_Y1 : C_V_Y2 + ((C_V_Y3) * C_V_Y4);
		xa = (90 <= dir && dir <= 270) ? -64. : 64.;
		ya = (dir == 90 || dir == 270) ? 0. : 64. * s_pixel->walls->angle_tg;
		if (ya != 0. && !(90 <= dir && dir <= 270))
			ya = -ya;
		while (i)
		{
			if (C_VER_IF1 || C_VER_IF2)
				break ;
			i = (ft_is_wall(s_pixel, bx, by) == 0) ? 0 : 1;
			if (i == 0 && (ft_is_wall(s_pixel, bx - 1, by) == 0 && C_VER_IF3))
				i = 1;
			bx = (i == 1) ? bx + xa : bx;
			by = (i == 1) ? by + ya : by;
		}
	}
	ft_check_ver1(s_pixel, bx, by, i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:23:07 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/03 18:29:29 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

double ft_get_angle_to_run1(double angle_tmp, double pov, double angle)
{
	if (0 <= pov && pov <= 90)
		angle = 90 - pov;
	else if (90 < pov && pov <= 180)
	{
		angle_tmp = 180 - pov;
		angle = 90 - angle_tmp;
	}
	else if (180 < pov && pov <= 270)
		angle = 270 - pov;
	else
	{
		angle_tmp = 360 - pov;
		angle = 90 - angle_tmp;
	}
	return (angle);
}

double ft_get_angle_to_run(double angle_tmp, double pov, short int gor, double angle)
{
	if (gor == 1)
	{
		if (0 <= pov && pov <= 90)
			angle = pov;
		else if (90 < pov && pov <= 180)
			angle = 180 - pov;
		else if (180 < pov && pov <= 270)
		{
			angle_tmp = 270 - pov;
			angle = 90 - angle_tmp;
		}
		else
			angle = 360 - pov;
	}
	else
		angle = ft_get_angle_to_run1(0.0, pov, 0.0);
	return (angle / 180 * 3.14);
}

int ft_is_wall(t_elem *s_pixel, int x, int y)
{
	if (x < 0 || y < 0 || x > s_pixel->map->map_width - 1 || y > s_pixel->map->map_height - 1)
		return (0);
	if (s_pixel->map->map_game_int[y >> 6][x >> 6] != 0)
		return (0); 
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pos1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:23:07 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 09:15:44 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_check_is_wall1(t_elem *s_pixel, int tmp_x, int tmp_y, double pov)
{
	s_pixel->player->x = s_pixel->player->x_camera;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? s_pixel->player->y_camera -
	(30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0))) : s_pixel->player->
	y_camera + (30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0)));
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->y_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? s_pixel->player->x_camera -
	(30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0))) : s_pixel->player->
	x_camera + (30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0)));
	s_pixel->player->y = s_pixel->player->y_camera;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->x_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? tmp_x - 20 : tmp_x + 20;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? tmp_y - 20 : tmp_y + 20;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->can_go_forward = 1;
}

void	ft_check_is_wall2(t_elem *s_pixel, int tmp_x, int tmp_y, double pov)
{
	s_pixel->player->x = s_pixel->player->x_camera;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? s_pixel->player->y_camera +
	(30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0))) : s_pixel->player->
	y_camera - (30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0)));
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->y_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? s_pixel->player->x_camera
	+ (30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0))) : s_pixel->player->
	x_camera - (30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0)));
	s_pixel->player->y = s_pixel->player->y_camera;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->x_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? tmp_x + 20 : tmp_x - 20;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? tmp_y + 20 : tmp_y - 20;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->can_go_forward = 1;
}

int		ft_check_is_wall(t_elem *s_pixel, int tmp_x, int tmp_y, short int m)
{
	double	pov;

	s_pixel->player->x_can_go = 0;
	s_pixel->player->y_can_go = 0;
	s_pixel->player->can_go_forward = 0;
	if (m == 1 || m == 2)
	{
		pov = s_pixel->player->pov;
		if (m == 1)
			ft_check_is_wall1(s_pixel, tmp_x, tmp_y, pov);
		else if (m == 2)
			ft_check_is_wall2(s_pixel, tmp_x, tmp_y, pov);
	}
	return (1);
}

void	ft_change_left_right1(t_elem *s_pixel, int tmp_x, int tmp_y, double n_a)
{
	int new_px;
	int new_py;

	n_a = 90 - s_pixel->player->pov;
	new_py = fabs(sin(n_a / 180 * 3.14) * 10.);
	new_px = fabs(cos(n_a / 180 * 3.14) * 10.);
	tmp_y = (90 < s_pixel->player->pov && s_pixel->player->pov < 270) ?
	s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
	tmp_x = (0 < s_pixel->player->pov && s_pixel->player->pov < 180) ?
	s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
	if (ft_is_wall(s_pixel, tmp_x, tmp_y))
	{
		s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > s_pixel->map->
		map_height - 70) ? s_pixel->player->y_camera : tmp_y;
		s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > s_pixel->map->
		map_width - 70) ? s_pixel->player->x_camera : tmp_x;
	}
}

void	ft_change_left_right(t_elem *s_pixel, int tmp_x, int tmp_y, double n_a)
{
	int new_px;
	int new_py;

	n_a = 90 - s_pixel->player->pov;
	new_py = fabs(sin(n_a / 180 * 3.14) * 10.);
	new_px = fabs(cos(n_a / 180 * 3.14) * 10.);
	if (s_pixel->key->go_right == 1)
	{
		tmp_y = (90 < s_pixel->player->pov && s_pixel->player->pov < 270) ?
		s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
		tmp_x = (0 < s_pixel->player->pov && s_pixel->player->pov < 180) ?
		s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
		if (ft_is_wall(s_pixel, tmp_x, tmp_y))
		{
			s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > s_pixel->map->
			map_height - 70) ? s_pixel->player->y_camera : tmp_y;
			s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > s_pixel->map->
			map_width - 70) ? s_pixel->player->x_camera : tmp_x;
		}
	}
	if (s_pixel->key->go_left == 1)
		ft_change_left_right1(s_pixel, 0, 0, 0.0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:23:07 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/03 18:27:57 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void ft_change_player_dest_up1(t_elem *s_pixel, int tmp_x, int tmp_y)
{
	if ((10 * ((double)tmp_x / 64. - (int)tmp_x / 64)) >= 5)
	{
		s_pixel->player->y_camera = tmp_y; 
		s_pixel->player->x_camera = s_pixel->player->x_camera;
	}
	else
	{
		s_pixel->player->y_camera = s_pixel->player->y_camera;
		s_pixel->player->x_camera = tmp_x;
	}
}

void ft_change_player_dest_up(t_elem *s_pixel, int tmp_x, int tmp_y, double pov)
{
	int new_px;
	int new_py;

	new_py = fabs(sin(pov / 180 * 3.14) * 15.);
	new_px = fabs(cos(pov / 180 * 3.14) * 15.);
	tmp_y = (0 < pov && pov < 180) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
	tmp_x = (90 < pov && pov < 270) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
	if (ft_is_wall(s_pixel, tmp_x, tmp_y) && ft_check_is_wall(s_pixel, tmp_x, tmp_y, 1) == 1)
	{
		if (s_pixel->player->can_go_forward == 0 && s_pixel->player->x_can_go == 1 && s_pixel->player->y_can_go == 1)
			ft_change_player_dest_up1(s_pixel, tmp_x, tmp_y);
		else
		{
			s_pixel->player->y_camera = (s_pixel->player->y_can_go == 1) ? tmp_y : s_pixel->player->y_camera;
			s_pixel->player->x_camera = (s_pixel->player->x_can_go == 1) ? tmp_x : s_pixel->player->x_camera;
		}
	}
}

void ft_change_player_dest_down1(t_elem *s_pixel, int tmp_x, int tmp_y)
{
	if ((10 * ((double)tmp_x / 64. - (int)tmp_x / 64)) >= 5)
	{
		s_pixel->player->y_camera = tmp_y; 
		s_pixel->player->x_camera = s_pixel->player->x_camera;
	}
	else
	{
		s_pixel->player->y_camera = s_pixel->player->y_camera;
		s_pixel->player->x_camera = tmp_x;
	}
}

void ft_change_player_dest_down(t_elem *s_pixel, int tmp_x, int tmp_y, double pov)
{
	int new_px;
	int new_py;

	new_py = fabs(sin(pov / 180 * 3.14) * 15.);
	new_px = fabs(cos(pov / 180 * 3.14) * 15.);
	tmp_y = (0 < pov && pov < 180) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
	tmp_x = (90 < pov && pov < 270) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
	if (ft_is_wall(s_pixel, tmp_x, tmp_y) && ft_check_is_wall(s_pixel, tmp_x, tmp_y, 2) == 1)
	{
		if (s_pixel->player->can_go_forward == 0 && s_pixel->player->x_can_go == 1 && s_pixel->player->y_can_go == 1)
			ft_change_player_dest_down1(s_pixel, tmp_x, tmp_y);
		else
		{
			s_pixel->player->y_camera = (s_pixel->player->y_can_go == 1) ? tmp_y : s_pixel->player->y_camera;
			s_pixel->player->x_camera = (s_pixel->player->x_can_go == 1) ? tmp_x : s_pixel->player->x_camera;
		}
	}
}

void ft_change_player_dest(t_elem *s_pixel, int tmp_x, int tmp_y, double pov)
{

	pov = (double)s_pixel->player->pov;
	if (s_pixel->key->go_up == 1 || s_pixel->key->go_down == 1)
	{
		if (s_pixel->key->go_up == 1)
			ft_change_player_dest_up(s_pixel, tmp_x, tmp_y, pov);
		else if (s_pixel->key->go_down == 1)
			ft_change_player_dest_down(s_pixel, tmp_x, tmp_y, pov);
	}
	if ((s_pixel->key->go_left == 1 || s_pixel->key->go_right == 1))
		ft_change_player_dest_left_right(s_pixel, 0, 0, 0.0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:21:46 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 11:29:19 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

double	ft_get_len_vec(t_elem *s_pixel, double wall_x, double wall_y)
{
	double len;
	double dir;

	dir = s_pixel->player->dir;
	if (dir == 0 || dir == 360 || dir == 180)
		len = fabs((s_pixel->player->x_camera - wall_x) /
		s_pixel->walls->angle_cos);
	else
		len = fabs((s_pixel->player->y_camera - wall_y) /
		s_pixel->walls->angle_sin);
	return (len);
}

void	ft_find_wall1(t_elem *s_pixel, double nbr1_x, double nbr1_y)
{
	s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y);
	s_pixel->walls->if_gor_line = 1;
	s_pixel->texture->texture_now = s_pixel->map->map_game_int[(int)nbr1_y
	>> 6][(int)nbr1_x >> 6];
}

void	ft_find_wall2(t_elem *s_pixel, double nbr2_x, double nbr2_y)
{
	s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y);
	s_pixel->walls->if_gor_line = 0;
	s_pixel->texture->texture_now = s_pixel->map->map_game_int[(int)nbr2_y
	>> 6][(int)nbr2_x >> 6];
}

void	ft_choose_len(t_elem *s_pixel, double tmp_gor, double tmp_ver)
{
	if (tmp_gor >= tmp_ver)
	{
		s_pixel->walls->if_gor_line = 0;
		s_pixel->walls->len_vec = tmp_ver;
	}
	else
	{
		s_pixel->walls->if_gor_line = 1;
		s_pixel->walls->len_vec = tmp_gor;
	}
}

void	ft_find_wall(t_elem *s_pixel, double dir, double t_gor, double t_ver)
{
	double n1_x;
	double n1_y;
	double n2_x;
	double n2_y;

	ft_check_gor(s_pixel, dir, 1.0, 1.0);
	n1_x = s_pixel->walls->dot_wall_x;
	n1_y = s_pixel->walls->dot_wall_y;
	ft_check_ver(s_pixel, dir, 1.0, 1.0);
	n2_x = s_pixel->walls->dot_wall_x;
	n2_y = s_pixel->walls->dot_wall_y;
	if (n2_x >= 0 && n1_x >= 0)
	{
		t_gor = ft_get_len_vec(s_pixel, n1_x, n1_y);
		t_ver = ft_get_len_vec(s_pixel, n2_x, n2_y);
		ft_choose_len(s_pixel, t_gor, t_ver);
		if (t_gor >= t_ver)
			N = s_pixel->map->map_game_int[(int)n2_y >> 6][(int)n2_x >> 6];
		else
			N = s_pixel->map->map_game_int[(int)n1_y >> 6][(int)n1_x >> 6];
	}
	else if ((n1_x > 0) && (n2_x < 0))
		ft_find_wall1(s_pixel, n1_x, n1_y);
	else if ((n1_x < 0) && (n2_x > 0))
		ft_find_wall2(s_pixel, n2_x, n2_y);
}

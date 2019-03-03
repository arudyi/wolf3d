/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/03 18:31:34 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

/*int mouse_move(int x, int y, t_elem *s_pixel)
{
	static int pre_x = 910;

	y = 1;
	if ((pre_x > x || (x <= 0 && (pre_x > x || pre_x == x))))
		s_pixel->player->pov = (s_pixel->player->pov == 360) ? 2 : s_pixel->player->pov + 2;
	else if ((pre_x < x || x >= 1920))
		s_pixel->player->pov = (s_pixel->player->pov == 0) ? 358 : s_pixel->player->pov - 2;
	else if (x == pre_x)
		pre_x = x;
	pre_x = x;
	ft_after_key_mouse(s_pixel);
	ft_clean_display(s_pixel);
	ft_main_draw(s_pixel);
	return (0);
}*/

/*void exit_program(t_elem *s_pixel)
{
	int i;
	int height;

	system("killall afplay");
	height = s_pixel->map->map_height >> 6;
	i = -1;
	while (++i < height)
		free(s_pixel->map->map_game_int[i]);
	free(s_pixel->map->map_game_int);
	free(s_pixel->key);
	free(s_pixel->map);
	free(s_pixel->texture);
	free(s_pixel->player);
	free(s_pixel->walls);
	free(s_pixel);
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	system("leaks wolf3d");///////////////////
	exit(1);
}

int exit_x(t_elem *s_pixel)
{
	int i;
	int height;

	system("killall afplay");
	height = s_pixel->map->map_height >> 6;
	i = -1;
	while (++i < height)
		free(s_pixel->map->map_game_int[i]);
	free(s_pixel->map->map_game_int);
	free(s_pixel->key);
	free(s_pixel->map);
	free(s_pixel->texture);
	free(s_pixel->player);
	free(s_pixel->walls);
	free(s_pixel);
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	system("leaks wolf3d");///////////////////////
	exit(1);
	return (0);
}*/

/*double ft_get_angle_to_run1(double angle_tmp, double pov, double angle)
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
}*/

/*void ft_check_is_wall1(t_elem *s_pixel, int tmp_x, int tmp_y, double pov)
{
	s_pixel->player->x = s_pixel->player->x_camera;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? s_pixel->player->y_camera - (30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0))) : s_pixel->player->y_camera + (30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0)));
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->y_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? s_pixel->player->x_camera - (30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0))) : s_pixel->player->x_camera + (30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0)));
	s_pixel->player->y = s_pixel->player->y_camera;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->x_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? tmp_x - 20 : tmp_x + 20;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? tmp_y - 20 : tmp_y + 20;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->can_go_forward = 1;
}

void ft_check_is_wall2(t_elem *s_pixel, int tmp_x, int tmp_y, double pov)
{
	s_pixel->player->x = s_pixel->player->x_camera;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? s_pixel->player->y_camera + (30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0))): s_pixel->player->y_camera - (30 * cos(ft_get_angle_to_run(0.0, pov, 0, 0.0)));
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->y_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? s_pixel->player->x_camera + (30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0))) : s_pixel->player->x_camera - (30 * cos(ft_get_angle_to_run(0.0, pov, 1, 0.0)));
	s_pixel->player->y = s_pixel->player->y_camera;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->x_can_go = 1;
	s_pixel->player->x = (90 <= pov && pov <= 270) ? tmp_x + 20 : tmp_x - 20;
	s_pixel->player->y = (0 <= pov && pov <= 180) ? tmp_y + 20 : tmp_y - 20;
	if (ft_is_wall(s_pixel, s_pixel->player->x, s_pixel->player->y) == 1)
		s_pixel->player->can_go_forward = 1;
}

int ft_check_is_wall(t_elem *s_pixel, int tmp_x, int tmp_y, short int motion)
{
	double	pov;

	s_pixel->player->x_can_go = 0;
	s_pixel->player->y_can_go = 0;
	s_pixel->player->can_go_forward = 0;
	if (motion == 1 || motion == 2)
	{
		pov = s_pixel->player->pov;
		if (motion == 1)
			ft_check_is_wall1(s_pixel, tmp_x, tmp_y, pov);
		else if (motion == 2)
			ft_check_is_wall2(s_pixel, tmp_x, tmp_y, pov);
	}
	return (1);
}

void ft_change_player_dest_left_right1(t_elem *s_pixel, int tmp_x, int tmp_y, double new_angle)
{
	int new_px;
	int new_py;

	new_angle = 90 - s_pixel->player->pov;
	new_py = fabs(sin(new_angle / 180 * 3.14) * 10.);
	new_px = fabs(cos(new_angle / 180 * 3.14) * 10.);
	tmp_y = (90 < s_pixel->player->pov && s_pixel->player->pov < 270) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
	tmp_x = (0 < s_pixel->player->pov && s_pixel->player->pov < 180) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
	if (ft_is_wall(s_pixel, tmp_x, tmp_y))
	{
		s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > s_pixel->map->map_height - 70) ? s_pixel->player->y_camera : tmp_y;
		s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > s_pixel->map->map_width - 70) ? s_pixel->player->x_camera : tmp_x;
	}
}

void ft_change_player_dest_left_right(t_elem *s_pixel, int tmp_x, int tmp_y, double new_angle)
{
	int new_px;
	int new_py;

	new_angle = 90 - s_pixel->player->pov;
	new_py = fabs(sin(new_angle / 180 * 3.14) * 10.);
	new_px = fabs(cos(new_angle / 180 * 3.14) * 10.);
	if (s_pixel->key->go_right == 1)
	{
		tmp_y = (90 < s_pixel->player->pov && s_pixel->player->pov < 270) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
		tmp_x = (0 < s_pixel->player->pov && s_pixel->player->pov < 180) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
		if (ft_is_wall(s_pixel, tmp_x, tmp_y))
		{
			s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > s_pixel->map->map_height - 70) ? s_pixel->player->y_camera : tmp_y;
			s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > s_pixel->map->map_width - 70) ? s_pixel->player->x_camera : tmp_x;
		}
	}
	if (s_pixel->key->go_left == 1)
		ft_change_player_dest_left_right1(s_pixel, 0, 0, 0.0);
}*/

/*void ft_change_player_dest_up1(t_elem *s_pixel, int tmp_x, int tmp_y)
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
}*/

/*void ft_clean_display(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);
}

void ft_refresh(t_elem *s_pixel)
{
	s_pixel->key->go_left =	0;
	s_pixel->key->go_right = 0;
	s_pixel->key->go_up = 0;
	s_pixel->key->go_down =	0;
	s_pixel->key->see_left = 0;	
	s_pixel->key->see_right = 0;
	s_pixel->key->sit = 0;
	s_pixel->texture->mandatory_mode = 1;
	s_pixel->texture->texture_mode = 1;
	s_pixel->player->x_camera = s_pixel->map->begin_x_camera;
	s_pixel->player->y_camera = s_pixel->map->begin_y_camera;
	s_pixel->player->pov = 90;
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
}*/

/*void ft_change_pov(t_elem *s_pixel)
{

	if (s_pixel->key->see_left == 1)
		s_pixel->player->pov = (s_pixel->player->pov == 360) ? 2.0 : s_pixel->player->pov + 2.0;
	if (s_pixel->key->see_right == 1)
		s_pixel->player->pov = (s_pixel->player->pov == 0) ? 358.0 : s_pixel->player->pov - 2.0;
}*/

/*int ft_after_key_mouse(t_elem *s_pixel)
{
	if (s_pixel->key->see_left == 1 || s_pixel->key->see_right == 1)
		ft_change_pov(s_pixel);
	else if (s_pixel->key->go_up == 1 || s_pixel->key->go_right == 1 || s_pixel->key->go_left == 1 || s_pixel->key->go_down == 1)
		ft_change_player_dest(s_pixel, 0, 0, 0.0);
	return (0);
}

void ft_change_game_mode(int key, t_elem *s_pixel)
{
	if (key == 83)
		s_pixel->texture->mandatory_mode = 1;
	else if (key == 84)
		s_pixel->texture->mandatory_mode = 0;
	else if (key == 86)
		s_pixel->texture->texture_mode = 1;
	else if (key == 87)
		s_pixel->texture->texture_mode = 0;
}

int ft_key_press(int key, t_elem *s_pixel)
{
	if (key == 53)
		exit_program(s_pixel);
	else if (key == 51)
		ft_refresh(s_pixel);
	else if (key == 83 || key == 84 || key == 86 || key == 87)
		ft_change_game_mode(key, s_pixel);
	else if (key == 0)
		s_pixel->key->go_left =	1;
	else if (key == 2)
		s_pixel->key->go_right = 1;
	else if (key == 13)
		s_pixel->key->go_up = 1;
	else if (key == 1)
		s_pixel->key->go_down =	1;
	else if (key == 123)
		s_pixel->key->see_left = 1;
	else if (key == 124)
		s_pixel->key->see_right = 1;
	else if (key == 256)
		s_pixel->key->sit = 1;
	ft_after_key_mouse(s_pixel);
	ft_clean_display(s_pixel);
	ft_main_draw(s_pixel);
	return (0);
}*/

/*int ft_key_release(int key, t_elem *s_pixel)
{
	if (key == 0)
		s_pixel->key->go_left =	0;
	else if (key == 2)
		s_pixel->key->go_right = 0;
	else if (key == 13)
		s_pixel->key->go_up = 0;
	else if (key == 1)
		s_pixel->key->go_down =	0;
	else if (key == 123)
		s_pixel->key->see_left = 0;
	else if (key == 124)
		s_pixel->key->see_right = 0;
	else if (key == 256)
		s_pixel->key->sit = 0;
	ft_after_key_mouse(s_pixel);
	ft_clean_display(s_pixel);
	ft_main_draw(s_pixel);
	return (0);
}*/

/*void ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	if (!(x > 1919 || x < 0 || y > 959 || y < 0))
	{
		index = s_pixel->size_line * y + (x << 2);
		*(unsigned *)(s_pixel->begin_str + index) = color;
	}
}*/

/*int ft_is_wall(t_elem *s_pixel, int x, int y)
{
	if (x < 0 || y < 0 || x > s_pixel->map->map_width - 1 || y > s_pixel->map->map_height - 1)
		return (0);
	if (s_pixel->map->map_game_int[y >> 6][x >> 6] != 0)
		return (0); 
	return (1);
}*/

/*void ft_check_gor1(t_elem *s_pixel, double ax, double ay, short int is_inside)
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
}*/

/*double ft_get_len_vec(t_elem *s_pixel, double wall_x, double wall_y)
{
	double len;
	double dir;

	dir = s_pixel->player->dir;
	if (dir == 0 || dir == 360 || dir == 180)
		len = fabs((s_pixel->player->x_camera - wall_x) / s_pixel->walls->angle_cos);
	else
		len = fabs((s_pixel->player->y_camera - wall_y) / s_pixel->walls->angle_sin);
	return (len);
}

void ft_find_wall1(t_elem *s_pixel, double nbr1_x, double nbr1_y)
{
	s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y);
	s_pixel->walls->if_gor_line = 1;
	s_pixel->texture->texture_now = s_pixel->map->map_game_int[(int)nbr1_y >> 6][(int)nbr1_x >> 6];
}

void ft_find_wall2(t_elem *s_pixel, double nbr2_x, double nbr2_y)
{
	s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y);
	s_pixel->walls->if_gor_line = 0;
	s_pixel->texture->texture_now = s_pixel->map->map_game_int[(int)nbr2_y >> 6][(int)nbr2_x >> 6];
}

void ft_choose_len(t_elem *s_pixel, double tmp_gor, double tmp_ver)
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

void ft_find_wall(t_elem *s_pixel, double dir, double tmp_gor, double tmp_ver)
{
	double nbr1_x;
	double nbr1_y;
	double nbr2_x;
	double nbr2_y;

	ft_check_gor(s_pixel, dir, 1.0, 1.0);
	nbr1_x = s_pixel->walls->dot_wall_x;
	nbr1_y = s_pixel->walls->dot_wall_y;
	ft_check_ver(s_pixel, dir, 1.0, 1.0);
	nbr2_x = s_pixel->walls->dot_wall_x;
	nbr2_y = s_pixel->walls->dot_wall_y;
	if (nbr2_x >= 0 && nbr1_x >= 0)
	{
		tmp_gor = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y);
		tmp_ver = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y);
		ft_choose_len(s_pixel, tmp_gor, tmp_ver);
		if (tmp_gor >= tmp_ver)
			s_pixel->texture->texture_now = s_pixel->map->map_game_int[(int)nbr2_y >> 6][(int)nbr2_x >> 6];
		else
			s_pixel->texture->texture_now = s_pixel->map->map_game_int[(int)nbr1_y >> 6][(int)nbr1_x >> 6];
	}
	else if ((nbr1_x > 0) && (nbr2_x < 0))
		ft_find_wall1(s_pixel, nbr1_x, nbr1_y);
	else if ((nbr1_x < 0) && (nbr2_x > 0))
		ft_find_wall2(s_pixel, nbr2_x, nbr2_y);
}*/

/*int ft_get_color_part(t_elem *s_pixel, int color)
{
	if (s_pixel->texture->mandatory_mode == 1)
	{
		if (s_pixel->walls->if_gor_line == 1 && (0 <= s_pixel->player->dir && s_pixel->player->dir <= 180))
			color = 0xFFFFFF;
		else if (s_pixel->walls->if_gor_line == 1 && !(0 <= s_pixel->player->dir && s_pixel->player->dir <= 180))
			color = 0x00FFFF;
		else if (s_pixel->walls->if_gor_line == 0 && (90 <= s_pixel->player->dir && s_pixel->player->dir <= 270))
			color = 0xFFFF00;
		else
			color = 0xFF00FF;
	}
	else 
	{
		if (s_pixel->walls->if_gor_line == 1 && (0 <= s_pixel->player->dir && s_pixel->player->dir <= 180))
			color = 0xFFFFFF;
		else if (s_pixel->walls->if_gor_line == 1 && !(0 <= s_pixel->player->dir && s_pixel->player->dir <= 180))
			color = 0x00FFFF;
		else if (s_pixel->walls->if_gor_line == 0 && (90 <= s_pixel->player->dir && s_pixel->player->dir <= 270))
			color = 0xFFFF00;
		else
			color = 0xFF00FF;
	}
	return (color);
}

int ft_get_texture_part(t_elem *s_pixel, int offset, double step, double y)
{
	int color;
	int index;

	if (s_pixel->texture->mandatory_mode == 1)
	{
		if (s_pixel->walls->if_gor_line == 1 && (0 <= s_pixel->player->dir && s_pixel->player->dir <= 180))
			s_pixel->texture->texture_now = 0;
		else if (s_pixel->walls->if_gor_line == 1 && !(0 <= s_pixel->player->dir && s_pixel->player->dir <= 180))
			s_pixel->texture->texture_now = 1;
		else if (s_pixel->walls->if_gor_line == 0 && (90 <= s_pixel->player->dir && s_pixel->player->dir <= 270))
			s_pixel->texture->texture_now = 2;
		else
			s_pixel->texture->texture_now = 3;
	}
	y = (y / step);
	index = ((int)y << 8) + (offset << 2);
	color = *(unsigned *)(s_pixel->texture->begin_str_tex[s_pixel->texture->texture_now] + index);
	return (color);
}

int ft_get_texture(t_elem *s_pixel, int offset, double step, double y)
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
}*/

/*void ft_draw_walls(t_elem *s_pixel, int x)
{
	int		i;
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
	i = -1;
	height = 64 / s_pixel->walls->len_vec * 1662;
	y = 480 - (height  / 2 ); // >> 1
	step = (height / 64);
	while (tmp_y <= y)
			ft_pixel_to_image(s_pixel, x, tmp_y++, 0x202020); //if (!(x > 1919 || y > 959 || x < 0 || y < 0)) // could be deleted
	while (++i < height - 10)
		if (!(x > 1920 || y > 960 || x < 0 || y++ < 0))
			ft_pixel_to_image(s_pixel, x, y, ft_get_texture(s_pixel, offset, step, (double)i));
	while (y < 960)
			ft_pixel_to_image(s_pixel, x, y++, 0x696969); //if (!(x > 1919 || y > 959 || x < 0 || y < 0)) // could be deleted
}*/

/*void ft_cast_ray(t_elem *s_pixel)
{
	short int	i;
	double		k;
	double		dir;
	short int	is_para;
	int			x;

	is_para = 0;
	x = 1919;
	i = 0;
	k = 60. / 1920.;
	dir = (double)(s_pixel->player->pov - (60. / 2.));
	if (dir < 0)
		dir += 360;
	while (++i <= 1920)
	{
		s_pixel->player->dir = dir;
		s_pixel->walls->angle_cos = (cos(dir / 180 * 3.14));
		s_pixel->walls->angle_sin = (sin(dir / 180 * 3.14));
		s_pixel->walls->angle_tg = (tan(dir / 180 * 3.14));
		ft_find_wall(s_pixel, dir, -1.0, -1.0);
		ft_draw_walls(s_pixel, x--); 
		dir += k;
		if (dir > 360.)
			dir -= 360.;
	}
}

void ft_draw_game(t_elem *s_pixel)
{
	ft_cast_ray(s_pixel);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->img_ptr, 0, 0);
	ft_draw_interface(s_pixel);
}

void ft_draw_interface1(t_elem *s_pixel, char *str, char *tmp, char *tmp1)
{
	str = ft_strjoin(tmp, "                                    ");
	free(tmp);
	tmp1 = ft_itoa(s_pixel->player->health);
	tmp = ft_strjoin(str, tmp1);
	free(tmp1);
	free(str);
	str = ft_strjoin(tmp, "                        ");
	free(tmp);
	tmp1 = ft_itoa(s_pixel->player->ammo);
	tmp = ft_strjoin(str, tmp1);
	free(tmp1);
	free(str);
	str = ft_strjoin(tmp, "");
	free(tmp);	
	mlx_string_put(s_pixel->mlx_ptr, s_pixel->win_ptr, 100, 870, 0xFFFFFF, str);
	free(str);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->texture->arr_ptr_tex[12], 1600, 820);
}

void ft_draw_interface(t_elem *s_pixel)
{
	char *str;
	char *tmp;
	char *tmp1;

	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->texture->arr_ptr_tex[10], 887, 565);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->texture->arr_ptr_tex[11], 0, 730);
	tmp = ft_itoa(s_pixel->player->level);
	str = ft_strjoin(tmp, "                            ");
	free(tmp);
	tmp1 = ft_itoa(s_pixel->player->score);
	tmp = ft_strjoin(str, tmp1);
	free(tmp1);
    free(str);
	str = ft_strjoin(tmp, "                           ");
	free(tmp);
	tmp1 = ft_itoa(s_pixel->player->lives);
	tmp = ft_strjoin(str, tmp1);
	free(tmp1);
	free(str);
	ft_draw_interface1(s_pixel, str, tmp, tmp1);
}

void ft_main_draw(t_elem *s_pixel)
{
	ft_draw_game(s_pixel);
	mlx_hook(s_pixel->win_ptr, 2, 5, ft_key_press, s_pixel);
	mlx_hook(s_pixel->win_ptr, 3, 5, ft_key_release, s_pixel);
	mlx_hook(s_pixel->win_ptr, 17, 1L << 17, exit_x, s_pixel);
	mlx_hook(s_pixel->win_ptr, 6, 5, mouse_move, s_pixel);
	mlx_loop(s_pixel->mlx_ptr);
}*/
/*
int ft_read_first_time(int fd)
{
	int		count;
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
			if (!(48 <= buf[i] && buf[i] <= 57) && ((buf[i] != '\n')) && ((buf[i] != '\0')))
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

void ft_find_player_position(t_elem *s_pixel, int i, int j)
{
	s_pixel->is_player = 1;
	s_pixel->player->x_camera = (j << 6) + 22;
	s_pixel->player->y_camera = (i << 6) + 22;
	s_pixel->map->begin_x_camera = (j << 6) + 22;
	s_pixel->map->begin_y_camera = (i << 6) + 22;
}

int ft_ft_validate1(t_elem *s_pixel)
{
	s_pixel->size_is_right = s_pixel->size_column;
	s_pixel->size_column = 0;
	if (!(s_pixel->size_row >= 3))
		return (0);
	s_pixel->size_row = 0;
	return (1);
}

int ft_ft_validate2(t_elem *s_pixel)
{
	if (!(s_pixel->size_row >= 3))
		return (0);
	if (s_pixel->size_column != s_pixel->size_is_right)
		return (0);
	s_pixel->size_column = 0;
	s_pixel->size_row = 0;
	return (1);
}*/

/*int ft_validate(char **map, int i, t_elem *s_pixel, int row)
{
	while (++i < row)
	{
		s_pixel->j = -1;
		if (map[i][0] == '\0')
			return (0); 
		while (map[i][++s_pixel->j] != '\0')
		{
			if (map[i][s_pixel->j] == '0')
				ft_find_player_position(s_pixel, i, s_pixel->j);
			if (((s_pixel->j == 0 || s_pixel->j == s_pixel->size_is_right- 1) && !(48 < map[i][s_pixel->j] && map[i][s_pixel->j] <= 97)) || ((i == 0 || i == row - 1) && !(48 < map[i][s_pixel->j] && map[i][s_pixel->j] <= 97)))
				return (0);
			s_pixel->size_row++;
			s_pixel->size_column++;
			if (i == 0 && map[i][s_pixel->j + 1] == '\0')
				if (ft_ft_validate1(s_pixel) == 0)
					return (0);
			if (map[i][s_pixel->j + 1] == '\0' && i != 0)
				if (ft_ft_validate2(s_pixel) == 0)
					return (0);
		}
	}
	if (s_pixel->is_player == 0)
		return (0);
	ft_get_width_height(s_pixel, row);
	return (1);
}*/

/*void ft_get_width_height(t_elem *s_pixel, int row)
{
	s_pixel->map->map_width = s_pixel->size_is_right << 6;
	s_pixel->map->map_height = row << 6;
}*/

/*int ft_read_map(int fd, t_elem *s_pixel, int i, int	row, char *line)
{
	char	**map;

	if ((row = ft_read_first_time(fd)) < 2)
		return (0);
	close(fd);
	fd = open("map", O_RDONLY);
	map = (char **)malloc(sizeof(char *) * (row + 1));
	while (get_next_line(fd, &line))
	{
		map[++i] = ft_strdup(line);
		free(line);
	}
	close(fd);
	if (ft_validate(map, -1, s_pixel, row) == 0)
	{
		map[row] = NULL;
		i = -1;
		while (map[++i] != NULL)
			free(map[i]);
		free(map);
		return (0);
	}
	ft_create_char_map(s_pixel, map, row);
	ft_create_int_map(s_pixel);
	return (1);
}*/

/*void ft_create_char_map(t_elem *s_pixel, char **map, int row)
{
	int i;

	map[row] = NULL;
	s_pixel->map->map_game = (char **)malloc(sizeof(char *) * (row + 1));
	i = -1;
	while (map[++i] != NULL)
	{
		s_pixel->map->map_game[i] = ft_strdup(map[i]);
		free(map[i]);
	}
	free(map);
	s_pixel->map->map_game[row] = NULL;
}

void ft_create_int_map(t_elem *s_pixel)
{
	int i;
	int j;
	int k;

	i = -1;
	s_pixel->map->map_game_int = (int **)malloc(sizeof(int *) * (s_pixel->map->map_height >> 6));
	while (s_pixel->map->map_game[++i] != NULL)
	{
		j = -1;
		k = -1;
		s_pixel->map->map_game_int[i] = (int *)malloc(sizeof(int) * (s_pixel->map->map_width >> 6));
		while (s_pixel->map->map_game[i][++j] != '\0')
		{
			s_pixel->map->map_game_int[i][++k] = (48 <= s_pixel->map->map_game[i][j] && s_pixel->map->map_game[i][j] <= 57) ? s_pixel->map->map_game[i][j] - '0' : s_pixel->map->map_game[i][j]  - 0;
		}
		free(s_pixel->map->map_game[i]);
	}
	free(s_pixel->map->map_game);
}*/

/*void ft_get_map(t_elem *s_pixel, int ac, char **av)
{
	short int error;
	int fd;
	char *line;

	line = NULL;
	error = 0;
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "map") == 0)
		{
			error = 1;
			if ((fd = open("map", O_RDONLY)) == -1)
				error = 0;
			if (ft_read_map(fd, s_pixel, -1, 0, line) == 0)
				error = 0;
			close(fd);
		}
	}
	if (error == 0)
		ft_error_exit(s_pixel);
}*/

/*void ft_error_exit(t_elem *s_pixel)
{
	free(s_pixel->key);
	free(s_pixel->map);
	free(s_pixel->texture);
	free(s_pixel->player);
	free(s_pixel->walls);
	free(s_pixel);
	write(1, "error in ac, name or file is invalid\n", 37);
	system("leaks wolf3d"); ///////////////////////////
	exit(1);
}*/

/*void ft_get_addr_from_xpm(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	s_pixel->texture->begin_str_tex[0] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[1] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[1], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[2] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[2], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[3] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[3], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[4] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[4], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[5] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[5], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[6] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[6], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[7] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[7], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[8] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[8], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[9] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[9], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[10] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[10], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[11] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[11], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[12] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[12], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
}

void ft_load_texture1(t_elem *s_pixel)
{
	if (!(s_pixel->texture->arr_ptr_tex[6] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/eagle.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[7] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blood_min.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[8] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blood_max.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[9] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/red_door_skeleton.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[10] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/pistol.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[11] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/interface.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[12] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/pistol_icon.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
}

void ft_load_texture(t_elem *s_pixel)
{
	s_pixel->texture->tex_width = 64;
	s_pixel->texture->tex_height = 64;
	if (!(s_pixel->texture->arr_ptr_tex[0] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blue_wall.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);		
	if (!(s_pixel->texture->arr_ptr_tex[1] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/brown_wall.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[2] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/red_wall.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[3] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/eagle_with_swa.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[4] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/flag.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	if (!(s_pixel->texture->arr_ptr_tex[5] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/hitler.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height)))
		exit(1);
	ft_load_texture1(s_pixel);
}*/

void ft_prepare_programm1(t_elem *s_pixel)
{
	s_pixel->player->level = 1;
	s_pixel->player->health = 100;
	s_pixel->player->ammo = 15;
	s_pixel->player->score = 0;
	s_pixel->player->lives = 3;
	s_pixel->key->go_left = 0;
	s_pixel->key->go_right = 0;
	s_pixel->key->go_up = 0;
	s_pixel->key->go_down =	0;
	s_pixel->key->see_left = 0;
	s_pixel->key->see_right = 0;
	s_pixel->key->sit = 0;
	s_pixel->texture->mandatory_mode = 1;
	s_pixel->texture->texture_mode = 1;
}

void ft_prepare_programm(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	s_pixel->mlx_ptr = mlx_init();
	s_pixel->win_ptr = mlx_new_window(s_pixel->mlx_ptr, 1920, 960, "wolf3d");
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);
	s_pixel->player->pov = 90;
	s_pixel->walls->len_to_project_plane = 1662;
	ft_prepare_programm1(s_pixel);
	ft_load_texture(s_pixel);
	ft_get_addr_from_xpm(s_pixel);
	system("afplay ./Graphics/music.mp3 &");
	ft_main_draw(s_pixel);
}

int main(int ac, char **av)
{
	t_elem *s_pixel;

	if (!(s_pixel = (t_elem *)malloc(sizeof(t_elem))))
		exit(1);
	if (!(s_pixel->walls = (t_walls *)malloc(sizeof(t_walls))))
		exit(1);
	if (!(s_pixel->player = (t_player *)malloc(sizeof(t_player))))
		exit(1);
	if (!(s_pixel->texture = (t_texture *)malloc(sizeof(t_texture))))
		exit(1);
	if (!(s_pixel->map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	if (!(s_pixel->key = (t_key *)malloc(sizeof(t_key))))
		exit(1);
	s_pixel->is_player = 0;
	s_pixel->size_row = 0;
	s_pixel->size_is_right = 0;
	s_pixel->size_column = 0;
	ft_get_map(s_pixel, ac, av);
	ft_prepare_programm(s_pixel);
	system("leaks wolf3d");   ////////
	return (0);
}

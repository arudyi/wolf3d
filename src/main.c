/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/01 18:45:43 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"
#include <stdio.h>

int mouse_move(int x, int y, t_elem *s_pixel)
{
	static int pre_x = 910;

	y = 1;
	if ((pre_x > x || (x <= 0 && (pre_x > x || pre_x == x))))
		s_pixel->player->pov = (s_pixel->player->pov == 360) ? 0 : s_pixel->player->pov + 1;
	else if ((pre_x < x || x >= 1920))
		s_pixel->player->pov = (s_pixel->player->pov == 0) ? 360 : s_pixel->player->pov - 1;
	else if (x == pre_x)
		pre_x = x;
	pre_x = x;
	ft_after_key_mouse(s_pixel);
	ft_clean_display(s_pixel);
	ft_main_draw(s_pixel);
	return (0);
}

void exit_program(t_elem *s_pixel)
{
	int i;
	int height;

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
	//system("leaks wolf3d");
	exit(1);
}

int exit_x(t_elem *s_pixel)
{
	int i;
	int height;

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
	//system("leaks wolf3d");
	exit(1);
	return (0);
}

int ft_check_is_wall(t_elem *s_pixel, int tmp_x, int tmp_y, short int motion)
{
	double angle_gor;
	double angle_ver;
	double pov;
	int x;
	int y;

	s_pixel->player->x_can_go = 0;
	s_pixel->player->y_can_go = 0;
	s_pixel->player->can_go_forward = 0;
	if (motion == 1 || motion == 2)
	{
		pov = s_pixel->player->pov;
		if (0 <= pov && pov <= 90)
		{
			angle_ver = 90 - pov;
			angle_gor = pov;
		}
		else if (90 < pov && pov <= 180)
		{
			angle_gor = 180 - pov;
			angle_ver = 90 - angle_gor;
		}
		else if (180 < pov && pov <= 270)
		{
			angle_ver = 270 - pov;
			angle_gor = 90 - angle_ver;
		}
		else //if (270 < pov && pov <= 360)
		{
			angle_gor = 360 - pov;
			angle_ver = 90 - angle_gor;
		}
		if (motion == 1)
		{
			// ver ray
			x = s_pixel->player->x_camera;
			y = (0 <= pov && pov <= 180) ? s_pixel->player->y_camera - (30 * cos(angle_ver / 180 * 3.14)) : s_pixel->player->y_camera + (30 * cos(angle_ver / 180 * 3.14));
			if (ft_is_wall(s_pixel, x, y) == 1)
				s_pixel->player->y_can_go = 1; // return (0);
			// gor ray
			x = (90 <= pov && pov <= 270) ? s_pixel->player->x_camera - (30 * cos(angle_gor / 180 * 3.14)) : s_pixel->player->x_camera + (30 * cos(angle_gor / 180 * 3.14));
			y = s_pixel->player->y_camera;
			if (ft_is_wall(s_pixel, x, y) == 1)
				s_pixel->player->x_can_go = 1; //return (0);
			// diagonal line
			x = (90 <= pov && pov <= 270) ? tmp_x - 20 : tmp_x + 20;
			y = (0 <= pov && pov <= 180) ? tmp_y - 20 : tmp_y + 20;
			if (ft_is_wall(s_pixel, x, y) == 1)
				s_pixel->player->can_go_forward = 1; //return (0);
		}
		else if (motion == 2)
		{
			// ver ray
			x = s_pixel->player->x_camera;
			y = (0 <= pov && pov <= 180) ? s_pixel->player->y_camera + (30 * cos(angle_ver / 180 * 3.14)): s_pixel->player->y_camera - (30 * cos(angle_ver / 180 * 3.14));
			if (ft_is_wall(s_pixel, x, y) == 1)
				s_pixel->player->y_can_go = 1; //return (0);
			// gor ray
			x = (90 <= pov && pov <= 270) ? s_pixel->player->x_camera + (30 * cos(angle_gor / 180 * 3.14)) : s_pixel->player->x_camera - (30 * cos(angle_gor / 180 * 3.14));
			y = s_pixel->player->y_camera;
			if (ft_is_wall(s_pixel, x, y) == 1)
				s_pixel->player->x_can_go = 1; //return (0);
			// diagonal line
			x = (90 <= pov && pov <= 270) ? tmp_x + 20 : tmp_x - 20;
			y = (0 <= pov && pov <= 180) ? tmp_y + 20 : tmp_y - 20;
			if (ft_is_wall(s_pixel, x, y) == 1)
				s_pixel->player->can_go_forward = 1; // return (0);
		}
	}
	return (1);
}

void ft_change_player_dest(t_elem *s_pixel)
{
	double new_angle;
	int new_px; // double int
	int new_py; // double int
	double pov;
	int tmp_x;
	int tmp_y;
	int offset;
	double offset_tmp;

	pov = s_pixel->player->pov;
	if (s_pixel->key->go_up == 1 || s_pixel->key->go_down == 1) // go up go down
	{
		new_py = fabs(sin(pov / 180 * 3.14) * 10.); // pov
		new_px = fabs(cos(pov / 180 * 3.14) * 10.); // pov
		if (s_pixel->key->go_up == 1)
		{
			tmp_y = (0 < pov && pov < 180) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py; //(0 < pov && pov < 180)
			tmp_x = (90 < pov && pov < 270) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px; // (90 < pov && pov < 270)
			if (ft_is_wall(s_pixel, tmp_x, tmp_y) && ft_check_is_wall(s_pixel, tmp_x, tmp_y, 1) == 1)
			{
				if (s_pixel->player->can_go_forward == 0 && s_pixel->player->x_can_go == 1 && s_pixel->player->y_can_go == 1)
				{
					offset_tmp = tmp_x / 64.; // 
					offset = 10 * (offset_tmp - (int)offset_tmp);
					if (offset >= 5)
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
				else
				{
					s_pixel->player->y_camera = (s_pixel->player->y_can_go == 1) ? tmp_y : s_pixel->player->y_camera; // s_pixel->player->y_camera = /*(tmp_y < 70 || tmp_y > s_pixel->map->map_height - 70) ? s_pixel->player->y_camera :*/ tmp_y;
					s_pixel->player->x_camera = (s_pixel->player->x_can_go == 1) ? tmp_x : s_pixel->player->x_camera; // s_pixel->player->x_camera = /*(tmp_x < 70 || tmp_x > s_pixel->map->map_width - 70) ? s_pixel->player->x_camera :*/ tmp_x;
				}
			}
		}
		else if (s_pixel->key->go_down == 1)
		{
			tmp_y = (0 < pov && pov < 180) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
			tmp_x = (90 < pov && pov < 270) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
			if (ft_is_wall(s_pixel, tmp_x, tmp_y) && ft_check_is_wall(s_pixel, tmp_x, tmp_y, 2) == 1)
			{
				if (s_pixel->player->can_go_forward == 0 && s_pixel->player->x_can_go == 1 && s_pixel->player->y_can_go == 1)
				{
					offset_tmp = tmp_x / 64.; // 
					offset = 10 * (offset_tmp - (int)offset_tmp);
					if (offset >= 5)
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
				else
				{
					s_pixel->player->y_camera = (s_pixel->player->y_can_go == 1) ? tmp_y : s_pixel->player->y_camera; // s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > s_pixel->map->map_height - 70) ? s_pixel->player->y_camera : tmp_y;
					s_pixel->player->x_camera = (s_pixel->player->x_can_go == 1) ? tmp_x : s_pixel->player->x_camera; // s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > s_pixel->map->map_width - 70) ? s_pixel->player->x_camera : tmp_x;
				}
			}
		}
	}
	if ((s_pixel->key->go_left == 1 || s_pixel->key->go_right == 1)) // go left gp right
	{
		new_angle = 90 - s_pixel->player->pov;
		new_py = fabs(sin(new_angle / 180 * 3.14) * 10.); ///// 15
		new_px = fabs(cos(new_angle / 180 * 3.14) * 10.); ///// 15
		if (s_pixel->key->go_right == 1)
		{
			tmp_y = (90 < pov && pov < 270) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
			tmp_x = (0 < pov && pov < 180) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
			if (ft_is_wall(s_pixel, tmp_x, tmp_y)/* && ft_check_is_wall(s_pixel, tmp_x, tmp_y, 3) == 1*/)
			{
				s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > s_pixel->map->map_height - 70) ? s_pixel->player->y_camera : tmp_y;
				s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > s_pixel->map->map_width - 70) ? s_pixel->player->x_camera : tmp_x;
			}
		}
		if (s_pixel->key->go_left == 1)
		{
			tmp_y = (90 < pov && pov < 270) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
			tmp_x = (0 < pov && pov < 180) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
			if (ft_is_wall(s_pixel, tmp_x, tmp_y)/* && ft_check_is_wall(s_pixel, tmp_x, tmp_y, 4) == 1*/)
			{
				s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > s_pixel->map->map_height - 70) ? s_pixel->player->y_camera : tmp_y;
				s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > s_pixel->map->map_width - 70) ? s_pixel->player->x_camera : tmp_x;
			}
		}
	}
}

void ft_clean_display(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);

	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr1);
	s_pixel->img_ptr1 = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str1 = mlx_get_data_addr(s_pixel->img_ptr1, &bits_per_pixel, &s_pixel->size_line, &endian);
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
	s_pixel->player->x_camera = s_pixel->map->begin_x_camera;
	s_pixel->player->y_camera = s_pixel->map->begin_y_camera;
	s_pixel->player->pov = 90;
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr1);
	s_pixel->img_ptr1 = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
}

void ft_change_pov(t_elem *s_pixel)
{

	if (s_pixel->key->see_left == 1)
		s_pixel->player->pov = (s_pixel->player->pov == 360) ? 0 : s_pixel->player->pov + 1;
	if (s_pixel->key->see_right == 1)
		s_pixel->player->pov = (s_pixel->player->pov == 0) ? 360 : s_pixel->player->pov - 1;
}

int ft_after_key_mouse(t_elem *s_pixel)
{
	if (s_pixel->key->see_left == 1 || s_pixel->key->see_right == 1)
		ft_change_pov(s_pixel);
	else if (s_pixel->key->go_up == 1 || s_pixel->key->go_right == 1 || s_pixel->key->go_left == 1 || s_pixel->key->go_down == 1)
		ft_change_player_dest(s_pixel);
	return (0);
}

int ft_key_press(int key, t_elem *s_pixel)
{
	if (key == 53)
		exit_program(s_pixel);
	if (key == 51)
		ft_refresh(s_pixel);
	if (key == 0)
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
}

int ft_key_release(int key, t_elem *s_pixel)
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
}

void ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	if (!(x > 1919 || x < 0 || y > 959 || y < 0))
	{
		index = s_pixel->size_line * y + (x << 2);
		*(unsigned *)(s_pixel->begin_str + index) = color;
	}
}

void ft_pixel_to_image1(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	if (!(x > 1919 || x < 0 || y > 959 || y < 0))
	{
		index = s_pixel->size_line1 * y + (x << 2);
		//if (index < 0)
		//	index = index;
		*(unsigned *)(s_pixel->begin_str1 + index) = color;
	}
}

int ft_is_wall(t_elem *s_pixel, int x, int y)
{

	if (s_pixel->map->map_game_int[y >> 6][x >> 6] != 0)
	{
		//if (97 <= (int)s_pixel->map->map_game_int[y >> 6][x >> 6] && (int)s_pixel->map->map_game_int[y >> 6][x >> 6] <= 122)
		//	return (1);
		return (0); //if exist wall
	}
	return (1); // if dont exist wall
}

void ft_which_texture(t_elem *s_pixel, int x, int y)
{
	if ((int)s_pixel->map->map_game_int[y >> 6][x >> 6] != 0)
	{
		s_pixel->texture->texture_now = (int)s_pixel->map->map_game_int[y >> 6][x >> 6];
		//s_pixel->texture->texture_now = ((int)s_pixel->map->map_game_int[y >> 6][x >> 6] > 10) ? (int)s_pixel->map->map_game_int[y >> 6][x >> 6] - 87 : (int)s_pixel->map->map_game_int[y >> 6][x >> 6];
		//printf("s_pixel->texture->texture_now = %d\n", s_pixel->texture->texture_now);
	}
}

void ft_check_gor(t_elem *s_pixel, double dir)
{
	short int	is_inside;
	double		ax;
	double		ay;
	double		px; // int double/////////
	double		py; // int double////////
	double		xa;
	double		ya;

	px = s_pixel->player->x_camera;
	py = s_pixel->player->y_camera;
	is_inside = 1;

	ay = (0 <= dir && dir <= 180) ? ((int)py >> 6 << 6) - 1 : ((int)py >> 6 << 6) + 64; // <=
	ax = (dir == 90 || dir == 270) ? px : px + (py - ay) / s_pixel->walls->angle_tg;
	//ft_pixel_to_image1(s_pixel, ax, ay, 0xFFFFFF);
	ya = (0 <= dir && dir <= 180) ? -64. : 64.; // <=
	xa = (dir == 90 || dir == 270) ? 0. : 64. / s_pixel->walls->angle_tg;

	if (xa != 0. && (180 < dir && dir < 360))
		xa = -xa;

	while (is_inside)
	{
		//ft_pixel_to_image1(s_pixel, ax, ay, 0x00FFFF);
		if (ax < 0 || ax > s_pixel->map->map_width || ay < 0 || ay > s_pixel->map->map_height)
			break ;
		is_inside = (ft_is_wall(s_pixel, ax, ay) == 0) ? 0 : 1;
		//if (is_inside == 0)
		//	ft_pixel_to_image1(s_pixel, ax, ay, 0xFFFFFF);
		ax = (is_inside == 1) ? ax + xa : ax;
		ay = (is_inside == 1) ? ay + ya : ay;
	}
	s_pixel->walls->offset_x = ax;
	s_pixel->walls->dot_wall_x = (is_inside == 0) ? ax : -404;
	s_pixel->walls->dot_wall_y = (is_inside == 0) ? ay : -404;
}

void ft_check_ver(t_elem *s_pixel, double dir)
{
	short int	is_inside;
	double		bx;
	double		by;
	double		px; // double int //////
	double		py; // double int////////
	double		xa;
	double		ya;

	is_inside = 1;
	if (!(dir == 270 || dir == 90))
	{
		px = s_pixel->player->x_camera; // double
		py = s_pixel->player->y_camera; // double
		is_inside = 1;

		bx = (90 <= dir && dir <= 270) ? ((int)px >> 6 << 6) - 1. : ((int)px >> 6 << 6) + 64.;
		by = (dir == 90 || dir == 270) ? py : py + (px - bx) * s_pixel->walls->angle_tg;
		//ft_pixel_to_image1(s_pixel, bx, by, 0xFFFFFF);
		xa = (90 <= dir && dir <= 270) ? -64. : 64.;
		ya = (dir == 90 || dir == 270) ? 0. : 64. * s_pixel->walls->angle_tg;
	
		if (ya != 0. && !(90 < dir && dir < 270)) // !
			ya = -ya;
	
		while (is_inside)
		{
			//ft_pixel_to_image1(s_pixel, bx, by, 0xFF00FF);
			if (bx < 0 || bx > s_pixel->map->map_width || by < 0 || by > s_pixel->map->map_height)
				break ;
			is_inside = (ft_is_wall(s_pixel, bx, by) == 0) ? 0 : 1;
			//if (is_inside == 0)
			//	ft_pixel_to_image1(s_pixel, bx, by, 0xFFFFFF);
			bx = (is_inside == 1) ? bx + xa : bx;
			by = (is_inside == 1) ? by + ya : by;
		}
		s_pixel->walls->offset_y = by; // int
	}
	s_pixel->walls->dot_wall_x = (is_inside == 0) ? bx : -404;
	s_pixel->walls->dot_wall_y = (is_inside == 0) ? by : -404;
}

double ft_get_len_vec(t_elem *s_pixel, double wall_x, double wall_y) // double
{
	double len; // double
	double dir;

	dir = s_pixel->player->dir;
	if (dir == 0 || dir == 360 || dir == 180)
		len = fabs(fabs(s_pixel->player->x_camera - wall_x) / s_pixel->walls->angle_cos);
	else
		len = fabs(fabs(s_pixel->player->y_camera - wall_y) / s_pixel->walls->angle_sin); /// int
	//len = (len < 0) ? -len : len; // int
	return (len);
}

void ft_find_wall(t_elem *s_pixel, double dir)
{
	double nbr1_x; // double
	double nbr1_y;
	double nbr2_x;
	double nbr2_y;
	double tmp_gor;
	double tmp_ver;

	ft_check_gor(s_pixel, dir);
	nbr1_x = s_pixel->walls->dot_wall_x; ////////////// int
	nbr1_y = s_pixel->walls->dot_wall_y; ////////////// int
	ft_check_ver(s_pixel, dir);
	nbr2_x = s_pixel->walls->dot_wall_x; ///////////// int
	nbr2_y = s_pixel->walls->dot_wall_y; ////////////// int
	if (nbr2_x >= 0 && nbr2_y >= 0 && nbr1_x >= 0 && nbr1_y >= 0) // >=
	{
		tmp_gor = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y);
		tmp_ver = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y);
		if (tmp_gor > tmp_ver) // >=
		{
			s_pixel->walls->if_gor_line = 0;
			s_pixel->walls->len_vec = tmp_ver;
			ft_which_texture(s_pixel, nbr2_x, nbr2_y);
		}
		else
		{
			s_pixel->walls->if_gor_line = 1;
			s_pixel->walls->len_vec = tmp_gor;
			ft_which_texture(s_pixel, nbr1_x, nbr1_y);
		}
	}
	else if ((nbr1_x > 0 && nbr1_y > 0) && (nbr2_x < 0 && nbr2_y < 0))
	{
		s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y);
		s_pixel->walls->if_gor_line = 1;
		ft_which_texture(s_pixel, nbr1_x, nbr1_y);
	}
	else if ((nbr1_x < 0 && nbr1_y < 0) && (nbr2_x > 0 && nbr2_y > 0))
	{
		s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y);
		s_pixel->walls->if_gor_line = 0;
		ft_which_texture(s_pixel, nbr2_x, nbr2_y);
	}
}

int ft_get_texture(t_elem *s_pixel, int offset, double step, double y)
{
	int color;
	int index;

	y = (y / step);
	index = ((int)y << 8) + (offset << 2);
	color = *(unsigned *)(s_pixel->texture->begin_str_tex[s_pixel->texture->texture_now] + index);
	return (color);
}

void ft_draw_walls(t_elem *s_pixel, int x)
{
	int i;
	int y;
	double height;
	int offset;
	double step;
	int tmp_y;

	tmp_y = 0;
	if (s_pixel->walls->if_gor_line == 1)
		offset = s_pixel->walls->offset_x % 64;
	else
		offset = s_pixel->walls->offset_y % 64;
	i = -1;
	//s_pixel->walls->len_vec = s_pixel->walls->len_vec * cos(s_pixel->player->dir / 180 * 3.14);
	height = 64 / s_pixel->walls->len_vec * 1662;
	y = 480 - (height  / 2 ); // >> 1
	step = (height / 64);
	while (tmp_y <= y)
		if (!(x > 1920 || y > 960 || x < 0 || y < 0))
			ft_pixel_to_image(s_pixel, x, tmp_y++, 0x202020);
	while (++i < height)
	{
		if (!(x > 1920 || y > 960 || x < 0 || y < 0))
			ft_pixel_to_image(s_pixel, x, y, ft_get_texture(s_pixel, offset, step, (double)i));
		y++;
	}
	while (y < 960)
		if (!(x > 1920 || y > 960 || x < 0 || y < 0))
			ft_pixel_to_image(s_pixel, x, y++, 0x696969);
}

void ft_cast_ray(t_elem *s_pixel)
{
	short int i;
	double k;
	double dir;
	short int is_para;
	int x;

	is_para = 0;
	x = 1920;
	i = 0;
	k = 60. / 1920.;
	dir = (double)(s_pixel->player->pov - (60. / 2.));
	if (dir < 0)
		dir += 360;
	while (++i <= 1920)
	{
		s_pixel->player->dir = dir;
		s_pixel->walls->angle_cos = (cos(dir / 180 * 3.14)); // fabs
		s_pixel->walls->angle_sin = (sin(dir / 180 * 3.14)); // fabs
		s_pixel->walls->angle_tg = (tan(dir / 180 * 3.14)); // fabs
		ft_find_wall(s_pixel, dir);
		ft_draw_walls(s_pixel, x); 
		dir += k;
		//if (dir == 111.)
		//	dir = 111.;
		if (dir > 360.)
			dir -= 360.;
		x--;
	}
}

void ft_draw_game(t_elem *s_pixel)
{
	ft_cast_ray(s_pixel);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->img_ptr, 0, 0);
	//mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->img_ptr1, 0, 0);
	//ft_draw_interface(s_pixel);
}

void ft_draw_interface(t_elem *s_pixel)
{
	char *str;
	char *tmp;
	char *tmp1;

	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->texture->arr_ptr_tex[14], 887, 565);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->texture->arr_ptr_tex[16], 0, 730);
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
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->texture->arr_ptr_tex[17], 1600, 820);
	//system("leaks wolf3d");
	//exit(1);
}

void ft_main_draw(t_elem *s_pixel)
{
	ft_draw_game(s_pixel);
	mlx_hook(s_pixel->win_ptr, 2, 5, ft_key_press, s_pixel);
	mlx_hook(s_pixel->win_ptr, 3, 5, ft_key_release, s_pixel);
	mlx_hook(s_pixel->win_ptr, 17, 1L << 17, exit_x, s_pixel);
	mlx_hook(s_pixel->win_ptr, 6, 5, mouse_move, s_pixel);
	mlx_loop(s_pixel->mlx_ptr);
}

int ft_read_first_time(int fd)
{
	int count;
	int i;
	int row;
	char buf[100]; // 100
	int size_map;

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
			if (buf[i] == '\n')
				row++;
			if (buf[i + 1] == '\0' && count < 99)
				row++;
			size_map++;
			if (size_map > 3000)
			{
				printf("size_is_big or ");
				return (0);
			}
		}
		ft_bzero(&buf, 99);
	}
	//printf("good1\n");
	//printf("%d\n", row);
	//system("leaks wolf3d");
	return (row);
}

int ft_validate(char **map, int i, t_elem *s_pixel, int row)
{
	int size_column;
	int size_is_right;
	int size_row;
	int j;
	short int is_player;

	is_player = 0;
	size_row = 0;
	size_is_right = 0;
	size_column = 0;
	i = -1;
	while (++i < row)
	{
		j = -1;
		if (map[i][0] == '\0')
				return (0); 
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == '0')
			{
				is_player = 1;
				s_pixel->player->x_camera = (j << 6) + 22;
				s_pixel->player->y_camera = (i << 6) + 22;
				s_pixel->map->begin_x_camera = (j << 6) + 22;
				s_pixel->map->begin_y_camera = (i << 6) + 22;
			}
			//if (map[i][j] == '\n')
			//	return (0); 										///////////////////////////////
			//printf("row = %d\n", row);
			//printf("%c\n", map[2][2]);
			//printf("%c\n", map[0][0]);
			if ((i == 0 || i == row - 1) && !(48 < map[i][j] && map[i][j] <= 97))
				return (0);
			if ((j == 0 || j == size_is_right- 1) && !(48 < map[i][j] && map[i][j] <= 97)) 
				return (0);
			size_row++;
			size_column++;
			if (i == 0 && map[i][j + 1] == '\0')
			{
				size_is_right = size_column;
				size_column = 0;
				if (!(size_row >= 3))
					return (0);
				size_row = 0;
			}
			if (map[i][j + 1] == '\0' && i != 0)
			{
				if (!(size_row >= 3))
					return (0);
				if (size_column != size_is_right)
					return (0);
				size_column = 0;
				size_row = 0;
			}
		}
	}
	if (is_player == 0)
		return (0);
	s_pixel->map->map_width = size_is_right << 6; ///////// !!!!!!!!!!!!!!!!!!! ////////
	s_pixel->map->map_height = row << 6; ////////////// !!!!!!!!!!!!!!!!!!!!!!!!!!!! ///////////////////////////// 
	//printf("width = %d, height = %d\n",s_pixel->map->map_width , s_pixel->map->map_height);
	return (1);
}

int ft_read_map(int fd, t_elem *s_pixel)
{
	int		row;
	char	**map;
	char	*line;
	int		i;
	int		j;
	int 	k;

	i = -1;
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
	i = -1;
	s_pixel->map->map_game_int = (int **)malloc(sizeof(int *) * (s_pixel->map->map_height >> 6)); /// !!!!!!!!!!!!! //////// s_pixel->map->map_width
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
	i = -1;
	/*while (++i < s_pixel->map->map_height >> 6)
	{
		k = -1;
		while (++k < s_pixel->map->map_width >> 6)
			printf("%d", s_pixel->map->map_game_int[i][k]);
		printf("\n");
	}*/
	//printf("%d\n", s_pixel->map->map_game_int[1][2]);
	return (1);
}

void ft_get_map(t_elem *s_pixel, int ac, char **av)
{
	short int error;
	int fd;

	ac = 2;
	av[1] = "map";
	error = 0;
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "map") == 0)
		{
			error = 1;
			if ((fd = open("map", O_RDONLY)) == -1)
				error = 0;
			if (ft_read_map(fd, s_pixel) == 0)
				error = 0;
			close(fd);
		}
	}
	if (error == 0)
	{
		free(s_pixel->key);
		free(s_pixel->map);
		free(s_pixel->texture);
		free(s_pixel->player);
		free(s_pixel->walls);
		free(s_pixel);
		printf("error in ac, name or file is invalid\n");
		system("leaks wolf3d");
		exit(1);
	}
	
}

void ft_load_texture(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	s_pixel->texture->tex_width = 64;
	s_pixel->texture->tex_height = 64;
	s_pixel->texture->arr_ptr_tex[0] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blue_wall.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[1] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/brown_wall.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[2] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/red_wall.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[3] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/eagle_with_swa.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[4] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/flag.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[5] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/hitler.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[6] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/eagle.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[7] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/door.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[8] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/door_next_level.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[9] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/red_door_skeleton.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[10] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blood_min.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height); // a
	s_pixel->texture->arr_ptr_tex[11] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blood_max.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height); // b
	s_pixel->texture->arr_ptr_tex[12] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/red_door.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height); //c
	s_pixel->texture->arr_ptr_tex[13] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/vova.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//d
	s_pixel->texture->arr_ptr_tex[14] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/pistol.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//e
	s_pixel->texture->arr_ptr_tex[15] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/gachamuchi.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//f
	s_pixel->texture->arr_ptr_tex[16] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/interface.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//g
	s_pixel->texture->arr_ptr_tex[17] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/pistol_icon.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//h
	s_pixel->texture->arr_ptr_tex[18] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_column.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//i
	s_pixel->texture->arr_ptr_tex[19] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_rakovina.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//l
	s_pixel->texture->arr_ptr_tex[20] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_table_with_blood.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//k
	s_pixel->texture->arr_ptr_tex[21] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_table.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//l
	s_pixel->texture->arr_ptr_tex[22] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_flag.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//m
	s_pixel->texture->arr_ptr_tex[23] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_kubok.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//n
	s_pixel->texture->arr_ptr_tex[24] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_korona.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//o
	s_pixel->texture->arr_ptr_tex[25] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_death.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//p
	s_pixel->texture->arr_ptr_tex[26] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_gold_krest.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//q
	s_pixel->texture->arr_ptr_tex[27] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_luzha.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//r
	s_pixel->texture->arr_ptr_tex[28] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_more.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//s
	s_pixel->texture->arr_ptr_tex[29] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_toalet.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//t
	s_pixel->texture->arr_ptr_tex[30] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/sprite_tree.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);//u

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
	s_pixel->texture->begin_str_tex[13] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[13], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[14] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[14], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[15] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[15], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[16] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[16], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[17] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[17], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[18] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[18], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[19] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[19], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[20] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[20], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[21] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[21], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[22] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[22], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[23] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[23], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[24] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[24], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[25] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[25], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[26] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[26], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[27] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[27], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[28] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[28], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[29] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[29], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[30] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[30], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
}

void ft_prepare_programm(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	s_pixel->mlx_ptr = mlx_init();
	s_pixel->win_ptr = mlx_new_window(s_pixel->mlx_ptr, 1920, 960, "wolf3d");
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);

	s_pixel->img_ptr1 = mlx_new_image(s_pixel->mlx_ptr, 1920, 960); ////////////////////////////////////////////////
	s_pixel->begin_str1 = mlx_get_data_addr(s_pixel->img_ptr1, &bits_per_pixel, &s_pixel->size_line1, &endian); ////////////////////

	s_pixel->player->pov = 180; //90
	s_pixel->walls->len_to_project_plane = 1662;
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
	//s_pixel->player->x_camera = 940; ///////////////////////////////////////////////////////////////////////////////////
	//s_pixel->player->y_camera = 70; /////////////////////////////////////////////////////////////////////////////////
	ft_load_texture(s_pixel);
	ft_main_draw(s_pixel);
}

int main(int ac, char **av)
{
	t_elem *s_pixel;

	if (!(s_pixel = (t_elem *)malloc(sizeof(t_elem))))
		return (0);
	if (!(s_pixel->walls = (t_walls *)malloc(sizeof(t_walls))))
		return (0);
	if (!(s_pixel->player = (t_player *)malloc(sizeof(t_player))))
		return (0);
	if (!(s_pixel->texture = (t_texture *)malloc(sizeof(t_texture))))
		return (0);
	if (!(s_pixel->map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if (!(s_pixel->key = (t_key *)malloc(sizeof(t_key))))
		return (0);
	ft_get_map(s_pixel, ac, av);
	ft_prepare_programm(s_pixel);
	system("leaks wolf3d");
	return (0);
}

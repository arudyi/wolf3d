/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/02/15 18:02:07 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"
#include <stdio.h>

/*int	mouse_release(int button, int x, int y, t_elem *s_pixel)
{
	x = y;
	return (0);
}

int	mouse_press(int button, int x, int y, t_elem *s_pixel)
{
	x = y;
	return (0);
}
*/

void exit_program(t_elem *s_pixel)
{
	free(s_pixel->player);
	free(s_pixel->walls);
	free(s_pixel);
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->win_ptr);
	//system("leaks wolf3d");
	exit(1);
}

void ft_change_player_dest(t_elem *s_pixel, int key)
{
	double new_angle;
	int new_px; // double
	int new_py; // double
	double pov;
	int tmp_x;
	int tmp_y;

	pov = s_pixel->player->pov;
	if (key == 13 || key == 1) // go up go down
	{
		new_py = fabs(sin(pov / 180 * 3.14) * 20); // * 10
		new_px = fabs(cos(pov / 180 * 3.14) * 20); // cos(pov / 180 * 3.14)
		if (key == 13)
		{
			tmp_y = (0 < pov && pov < 180) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
			tmp_x = (90 < pov && pov < 270) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
			
			s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > 890) ? s_pixel->player->y_camera : tmp_y;
			s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > 1850) ? s_pixel->player->x_camera : tmp_x;
		}
		else
		{
			tmp_y = (0 < pov && pov < 180) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
			tmp_x = (90 < pov && pov < 270) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
			
			s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > 890) ? s_pixel->player->y_camera : tmp_y;
			s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > 1850) ? s_pixel->player->x_camera : tmp_x;
		}
	}
	else // go left gp right
	{
		new_angle = 90 - s_pixel->player->pov;
		new_py = fabs(sin(new_angle / 180 * 3.14) * 20); /////
		new_px = fabs(cos(new_angle / 180 * 3.14) * 20); /////
		if (key == 2)
		{
			tmp_y = (90 < pov && pov < 270) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
			tmp_x = (0 < pov && pov < 180) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
			s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > 890) ? s_pixel->player->y_camera : tmp_y;
			s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > 1850) ? s_pixel->player->x_camera : tmp_x;
		}
		else
		{
			tmp_y = (90 < pov && pov < 270) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
			tmp_x = (0 < pov && pov < 180) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
			s_pixel->player->y_camera = (tmp_y < 70 || tmp_y > 890) ? s_pixel->player->y_camera : tmp_y;
			s_pixel->player->x_camera = (tmp_x < 70 || tmp_x > 1850) ? s_pixel->player->x_camera : tmp_x;
		}
	}
}

void ft_clean_display(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr1);
	s_pixel->img_ptr1 = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str1 = mlx_get_data_addr(s_pixel->img_ptr1, &bits_per_pixel, &s_pixel->size_line, &endian);
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);
}

/*int mouse_move(int x, int y, t_elem *s_pixel)
{
	static int pre_x;

	if (pre_x >= x)
	{
		if (s_pixel->player->pov + 1 == 360)
			s_pixel->player->pov = 0;
		else
			s_pixel->player->pov++;
	}
	else if (pre_x < x)
	{
		if (s_pixel->player->pov == 0)
			s_pixel->player->pov = 359;
		else
			s_pixel->player->pov--;
	}
	pre_x = x;
	ft_clean_display(s_pixel);
	ft_main_draw(s_pixel);
	return (0);
}*/

void ft_refresh(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;
	s_pixel->player->x_camera = 900;
	s_pixel->player->y_camera = 500;
	s_pixel->player->pov = 90;
	mlx_destroy_image(s_pixel->mlx_ptr, s_pixel->img_ptr);
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr1, &bits_per_pixel, &s_pixel->size_line, &endian);
}

void ft_change_pov(int key, t_elem *s_pixel)
{

	if (key == 123)
	{
		if (s_pixel->player->pov == 360)
			s_pixel->player->pov = 2;
		else
			s_pixel->player->pov += 2;
	}
	else if (key == 124)
	{
		if (s_pixel->player->pov == 0)
			s_pixel->player->pov = 358;
		else
			s_pixel->player->pov -= 2;
	}
}

int	ft_check_key(int key, t_elem *s_pixel)
{
	if (key == 53)
		exit_program(s_pixel);
	if (key == 0 || key == 13 || key == 2 || key == 1)
		ft_change_player_dest(s_pixel, key);
	if (key == 51)
		ft_refresh(s_pixel);
	if (key == 123 || key == 124)
		ft_change_pov(key, s_pixel);
	ft_clean_display(s_pixel);
	ft_main_draw(s_pixel);
	return (0);
}

void ft_pixel_to_image_1(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	x = x << 2;
	index = s_pixel->size_line * y + x;
	*(unsigned *)(s_pixel->begin_str1 + index) = color;
}

void ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	x = x << 2;
	index = s_pixel->size_line * y + x; // index = s_pixel->size_line * y + x * 4;
	*(unsigned *)(s_pixel->begin_str + index) = color;
}

void ft_draw_square(t_elem *s_pixel, int x, int y, int color)
{
	int tmp_x;
	int tmp_y;

	tmp_x = -1;
	while (++tmp_x < 64)
	{
		tmp_y = -1;
		while (++tmp_y < 64)
			ft_pixel_to_image_1(s_pixel, x + tmp_x, y + tmp_y, color);
	}
}

void ft_set_walls(t_elem *s_pixel)
{
	int x;
	int y;
	int i;

	i = 0;
	x = 0;
	while (++i <= 30)
	{
		ft_draw_square(s_pixel, x, 0, 0x0000FF);
		ft_draw_square(s_pixel, x, 896, 0x0000FF);
		x += 64;
	}
	i = 0;
	y = 64;
	while (++i <= 13)
	{
		ft_draw_square(s_pixel, 0, y, 0x0000FF);
		ft_draw_square(s_pixel, 1856, y, 0x0000FF);
		y += 64;
	}
	i = 0;
	y = 320;
	while (++i <= 5)
	{
		ft_draw_square(s_pixel, 1472, y, 0x0000FF);
		y += 64;
	}

	i = 0;
	y = 320;
	while (++i <= 5)
	{
		ft_draw_square(s_pixel, 1280, y, 0x0000FF);
		y += 64;
	}
}

int ft_is_wall(t_elem *s_pixel, int x, int y)
{
	int index;

	x = x << 2;
	index = s_pixel->size_line * y + x;
	if (*(unsigned *)(s_pixel->begin_str1 + index) == 0x0000FF || *(unsigned *)(s_pixel->begin_str1 + index) == 0xFF0000 || *(unsigned *)(s_pixel->begin_str1 + index) == 0x00FF00 || *(unsigned *)(s_pixel->begin_str1 + index) == 0xFFFFFF)
		return (0);
	return (1);
}

void ft_check_gor(t_elem *s_pixel, double dir)
{
	short int	is_inside;
	double		ax;
	double		ay;
	int			px;
	int			py;
	double		xa;
	double		ya;

	px = s_pixel->player->x_camera;
	py = s_pixel->player->y_camera;
	is_inside = 1;
	ay = (0 < dir && dir < 180) ? (py >> 6 << 6) - 1 : (py >> 6 << 6) + 64;
	ax = (dir == 90 || dir == 270) ? px : px + (py - ay) / s_pixel->walls->angle_tg;
	ya = (0 < dir && dir < 180) ? -64. : 64.;
	xa = (dir == 90 || dir == 270) ? 0. : 64. / s_pixel->walls->angle_tg;
	if (xa != 0 && (180 < dir && dir < 360))
		xa = -xa;
	while (is_inside)
	{
		//printf("ax = %f, ay = %f\n", ax, ay);
		if (ax < 0 || ax > 1920 || ay < 0 || ay > 960)
			break ;
		is_inside = (ft_is_wall(s_pixel, ax, ay) == 0) ? 0 : 1;
		//ft_pixel_to_image_1(s_pixel, ax, ay, 0x00FF00);
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
	double		px;
	double		py;
	double		xa;
	double		ya;

	is_inside = 1;
	if (!(dir == 270 || dir == 90))
	{
		px = (double)s_pixel->player->x_camera;
		py = (double)s_pixel->player->y_camera;
		is_inside = 1;
		bx = (!(90 < dir && dir < 270)) ? ((int)px >> 6 << 6) + 64 : ((int)px >> 6 << 6) - 1;
		by = (dir == 90 || dir == 270) ? py : py + (px - bx) * s_pixel->walls->angle_tg; // tan(dir / 180 * 3.14)
		xa = (!(90 < dir && dir < 270)) ? 64 : -64;
		ya = (dir == 90 || dir == 270) ? 0 : 64 * s_pixel->walls->angle_tg; // tan(dir / 180 * 3.14)
		if (ya != 0 && !(90 < dir && dir < 270))
			ya = (0 < dir && dir < 180) ? -ya: -ya;
		while (is_inside)
		{
			//printf("bx = %f, by = %f\n", bx, by);
			if (bx < 0 || bx > 1920 || by < 0 || by > 960)
				break ;
			is_inside = (ft_is_wall(s_pixel, bx, by) == 0) ? 0 : 1;
			//ft_pixel_to_image_1(s_pixel, bx, by, 0xFF0000);
			bx += (is_inside == 1) ? xa : 0;
			by += (is_inside == 1) ? ya : 0;
		}
		s_pixel->walls->offset_y = by;
	}
	s_pixel->walls->dot_wall_x = (is_inside == 0) ? bx : -404;
	s_pixel->walls->dot_wall_y = (is_inside == 0) ? by : -404;
}

int ft_get_len_vec(t_elem *s_pixel, double wall_x, double wall_y)
{
	double len;
	double dir;

	dir = s_pixel->player->dir;
	if (dir == 0 || dir == 360 || dir == 180)
		len = fabs(s_pixel->player->x_camera - wall_x) / s_pixel->walls->angle_cos;
	else
		len = fabs(s_pixel->player->y_camera - wall_y) / s_pixel->walls->angle_sin;
	len = (len < 0) ? -len : len;
	return (len);
}

void ft_find_wall(t_elem *s_pixel, double dir)
{
	double nbr1_x;
	double nbr1_y;
	double nbr2_x;
	double nbr2_y;
	
	ft_check_gor(s_pixel, dir);
	nbr1_x = s_pixel->walls->dot_wall_x;
	nbr1_y = s_pixel->walls->dot_wall_y;
	ft_check_ver(s_pixel, dir);
	nbr2_x = s_pixel->walls->dot_wall_x;
	nbr2_y = s_pixel->walls->dot_wall_y;
	if (nbr2_x > 0 && nbr2_y > 0 && nbr1_x > 0 && nbr1_y > 0)
	{
		nbr1_x = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y);
		nbr2_x = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y);
		if (nbr1_x > nbr2_x)
		{
			s_pixel->walls->if_gor_line = 0;
			s_pixel->walls->len_vec = nbr2_x;
		}
		else
		{
			s_pixel->walls->if_gor_line = 1;
			s_pixel->walls->len_vec = nbr1_x;
		}
	}
	else if ((nbr1_x > 0 && nbr1_y > 0) && (nbr2_x < 0 && nbr2_y < 0))
	{
		s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y);
		s_pixel->walls->if_gor_line = 1;
	}
	else if ((nbr1_x < 0 && nbr1_y < 0) && (nbr2_x > 0 && nbr2_y > 0))
	{
		s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y);
		s_pixel->walls->if_gor_line = 0;
	}
	else
	{
		printf("Error in len\n");
		exit(1);
	}
	//printf("len = %f\n", s_pixel->walls->len_vec);
}

int ft_get_texture(t_elem *s_pixel, int offset, double step)
{
	static int y = 0;
	int color;
	int index;
	static int k = 0;

	index = s_pixel->texture->size_line * y + offset * 4;
	color = *(unsigned *)(s_pixel->texture->begin_str_tex[0] + index);
	k++;
	if (k >= step)
	{
		y++;
		k = 0;
	}
	y = (y == 64) ? 0: y;
	return (color);
}

void ft_draw_walls(t_elem *s_pixel, int x)
{
	int i;
	int y;
	int height;
	int offset;
	double step;

	if (s_pixel->walls->if_gor_line == 1)
		offset = s_pixel->walls->offset_x % 64;
	else
		offset = s_pixel->walls->offset_y % 64;
	i = 0;
	height = 64 / s_pixel->walls->len_vec * 1662;
	y = 480 - (height >> 1);
	step = height / 64.;
	while (++i <= height)
	{
		if (!(x > 1920 || y > 960 || x < 0 || y < 0))
		{
			ft_pixel_to_image(s_pixel, x, y, ft_get_texture(s_pixel, offset, step));
		}
		y++;
	}
}

void ft_cast_ray(t_elem *s_pixel)
{
	short int i;
	double k;
	double dir;
	int x;

	x = 1920;
	i = 0;
	k = 60. / 1920.;
	dir = (double)(s_pixel->player->pov - (60. / 2.));
	//dir = (double)s_pixel->player->pov;
	if (dir < 0)
		dir += 360;
	s_pixel->player->dir = dir;
	//ft_find_wall(s_pixel, dir);
	//printf("i = %d, dir = %f\n", i, dir);
	//printf("x = %d, y = %d\n", s_pixel->player->x_camera, s_pixel->player->y_camera);
	while (++i <= 1921) // 60 1920
	{
		s_pixel->walls->angle_cos = cos(dir / 180 * 3.14);
		s_pixel->walls->angle_sin = sin(dir / 180 * 3.14);
		s_pixel->walls->angle_tg = tan(dir / 180 * 3.14);
		//printf("i = %d, dir = %f\n", i, dir);
		if (dir > 360)
			dir -= 360;
		ft_find_wall(s_pixel, dir);
		ft_draw_walls(s_pixel, x);
		dir += k;
		x--;
	}
}

void ft_draw_game(t_elem *s_pixel)
{
	ft_set_walls(s_pixel);
	ft_cast_ray(s_pixel);
}

void ft_main_draw(t_elem *s_pixel)
{
	ft_draw_game(s_pixel);
	//ft_pixel_to_image_1(s_pixel, s_pixel->player->x_camera, s_pixel->player->y_camera, 0xFFFFFF);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->img_ptr, 0, 0);
	mlx_hook(s_pixel->win_ptr, 2, 5, ft_check_key, s_pixel);
	//mlx_hook(s_pixel->win_ptr, 4, 5, mouse_press, s_pixel);
	//mlx_hook(s_pixel->win_ptr, 5, 5, mouse_release, s_pixel);
	//mlx_hook(s_pixel->win_ptr, 6, 5, mouse_move, s_pixel);
	mlx_loop(s_pixel->mlx_ptr);
}

void ft_prepare_programm(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	s_pixel->texture->tex_width = 64;
	s_pixel->texture->tex_height = 64;
	s_pixel->mlx_ptr = mlx_init();
	s_pixel->win_ptr = mlx_new_window(s_pixel->mlx_ptr, 1920, 960, "wolf3d");
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->img_ptr1 = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);
	s_pixel->begin_str1 = mlx_get_data_addr(s_pixel->img_ptr1, &bits_per_pixel, &s_pixel->size_line, &endian);
	s_pixel->player->x_camera = 855;
	s_pixel->player->y_camera = 500;
	s_pixel->player->pov = 90;
	s_pixel->walls->len_to_project_plane = 1662;
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
	s_pixel->texture->arr_ptr_tex[10] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blood_min.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[11] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/blood_max.XPM", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->arr_ptr_tex[12] = mlx_xpm_file_to_image(s_pixel->mlx_ptr, "Graphics/red_door.xpm", &s_pixel->texture->tex_width, &s_pixel->texture->tex_height);
	s_pixel->texture->begin_str_tex[0] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[1] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[2] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[3] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[4] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[5] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[6] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[7] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[8] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[9] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[10] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[11] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	s_pixel->texture->begin_str_tex[12] = mlx_get_data_addr(s_pixel->texture->arr_ptr_tex[0], &bits_per_pixel, &s_pixel->texture->size_line, &endian);
	ft_main_draw(s_pixel);
}

int main(void)
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
	ft_prepare_programm(s_pixel);
	return (0);
}

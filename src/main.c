/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/02/13 19:27:47 by arudyi           ###   ########.fr       */
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

	pov = s_pixel->player->pov;
	if (key == 13 || key == 1) // go up go down
	{
		new_py = fabs(sin(pov / 180 * 3.14) * 10);
		new_px = fabs(cos(pov / 180 * 3.14) * 10);
		if (key == 13)
		{
			s_pixel->player->y_camera = (0 < pov && pov < 180) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
			s_pixel->player->x_camera = (90 < pov && pov < 270) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
		}
		else
		{
			s_pixel->player->y_camera = (0 < pov && pov < 180) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
			s_pixel->player->x_camera = (90 < pov && pov < 270) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
		}
	}
	else // go left gp right
	{
		new_angle = 90 - s_pixel->player->dir;
		new_py = fabs(sin(new_angle / 180 * 3.14) * 10);
		new_px = fabs(cos(new_angle / 180 * 3.14) * 10);
		if (key == 2)
		{
			s_pixel->player->y_camera = (90 < pov && pov < 270) ? s_pixel->player->y_camera - new_py : s_pixel->player->y_camera + new_py;
			s_pixel->player->x_camera = (0 < pov && pov < 180) ? s_pixel->player->x_camera + new_px : s_pixel->player->x_camera - new_px;
		}
		else
		{
			s_pixel->player->y_camera = (90 < pov && pov < 270) ? s_pixel->player->y_camera + new_py : s_pixel->player->y_camera - new_py;
			s_pixel->player->x_camera = (0 < pov && pov < 180) ? s_pixel->player->x_camera - new_px : s_pixel->player->x_camera + new_px;
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
		if (s_pixel->player->pov == 360.0)
			s_pixel->player->pov = 0.0;
		else
			s_pixel->player->pov += 1.0;
	}
	else if (key == 124)
	{
		if (s_pixel->player->pov == 0.0)
			s_pixel->player->pov = 359.0;
		else
			s_pixel->player->pov -= 1.0;
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

	index = s_pixel->size_line * y + x * 4;
	*(unsigned *)(s_pixel->begin_str1 + index) = color;
}

void ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color)
{
	int index;

	index = s_pixel->size_line * y + x * 4;
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

	index = s_pixel->size_line * y + x * 4;
	if (*(unsigned *)(s_pixel->begin_str1 + index) == 0x0000FF/* || *(unsigned *)(s_pixel->begin_str1 + index) == 0xFF0000 || *(unsigned *)(s_pixel->begin_str1 + index) == 0x00FF00*/)
		return (0);
	return (1);
}

void ft_check_gor(t_elem *s_pixel, int dir)
{
	short int	is_inside;
	double	ax;
	double	ay;
	double	px;
	double	py;
	double	xa;
	double	ya;

	px = (double)s_pixel->player->x_camera;
	py = (double)s_pixel->player->y_camera;
	is_inside = 1;
	ay = (0 < dir && dir < 180) ? (int)py / 64 * 64 - 1 : (int)py / 64 * 64 + 64;
	ax = (dir == 90 || dir == 270) ? px : px + (py - ay) / tan((double)dir / 180 * 3.14);
	ya = (0 < dir && dir < 180) ? -64.0 : 64.0;
	xa = (dir == 90 || dir == 270) ? 0.0 : 64 / tan((double)dir / 180 * 3.14);
	if (xa != 0 && (180 < dir && dir < 360))
		xa = (double)xa * -1.0;
	while (is_inside)
	{
		if (ax < 0 || ax > 1920 || ay < 0 || ay > 960)
			break ;
		is_inside = (ft_is_wall(s_pixel, ax, ay) == 0) ? 0 : 1;
		ft_pixel_to_image_1(s_pixel, ax, ay, 0x00FF00);
		ax = (is_inside == 1) ? ax + xa : ax + 0;
		ay = (is_inside == 1) ? ay + ya : ay + 0;
	}
	s_pixel->walls->dot_wall_x = (is_inside == 0) ? ax : -404;
	s_pixel->walls->dot_wall_y = (is_inside == 0) ? ay : -404;
}

void ft_check_ver(t_elem *s_pixel, int dir)
{
	short int	is_inside;
	double		bx;
	double		by;
	double		px;
	double		py;
	double		xa;
	double		ya;

	if (!(dir == 270 || dir == 90))
	{
		px = (double)s_pixel->player->x_camera;
		py = (double)s_pixel->player->y_camera;
		is_inside = 1;
		bx = (!(90 < dir && dir < 270)) ? (int)px / 64 * 64 + 64 : (int)px / 64 * 64 - 1;
		by = (dir == 90 || dir == 270) ? py : py + (px - bx) * tan((double)dir / 180 * 3.14);
		xa = (!(90 < dir && dir < 270)) ? 64 : -64;
		ya = (dir == 90 || dir == 270) ? 0 : 64 * tan((double)dir / 180 * 3.14);
		if (ya != 0 && !(90 < dir && dir < 270))
			ya = (0 < dir && dir < 180) ? ya * -1.0: ya * -1.0;
		while (is_inside)
		{
			if (bx < 0 || bx > 1920 || by < 0 || by > 960)
				break ;
			is_inside = (ft_is_wall(s_pixel, bx, by) == 0) ? 0 : 1;
			ft_pixel_to_image_1(s_pixel, bx, by, 0xFF0000);
			bx += (is_inside == 1) ? xa : 0;
			by += (is_inside == 1) ? ya : 0;
		}
	}
	if (!(dir == 270 || dir == 90))
	{
		s_pixel->walls->dot_wall_x = (is_inside == 0) ? bx : -404;
		s_pixel->walls->dot_wall_y = (is_inside == 0) ? by : -404;
	}
}

int ft_get_len_vec(t_elem *s_pixel, double wall_x, double wall_y, int dir)
{
	double len;

	if (dir == 0 || dir == 360 || dir == 180)
		len = fabs(s_pixel->player->x_camera - wall_x) / cos((double)dir / 180 * 3.14);
	else
		len = fabs(s_pixel->player->y_camera - wall_y) / sin((double)dir / 180 * 3.14); //M_PI
	len *= (len < 0) ? -1 : 1;
	return (len);
}

void ft_find_wall(t_elem *s_pixel, int dir)
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
		s_pixel->walls->len_vec = fmin(ft_get_len_vec(s_pixel, nbr1_x, nbr1_y, dir), ft_get_len_vec(s_pixel, nbr2_x, nbr2_y, dir));
	else if ((nbr1_x > 0 && nbr1_y > 0) && (nbr2_x < 0 && nbr2_y < 0))
		s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr1_x, nbr1_y, dir);
	else if ((nbr1_x < 0 && nbr1_y < 0) && (nbr2_x > 0 && nbr2_y > 0))
		s_pixel->walls->len_vec = ft_get_len_vec(s_pixel, nbr2_x, nbr2_y, dir);
	else
	{
		printf("Error in len\n");
		exit(1);
	}
	printf("dir = %d, len = %f\n", dir, s_pixel->walls->len_vec);
}

void ft_draw_walls(t_elem *s_pixel, int x)
{
	int y;
	int tmp_y;
	int i;
	int k;
	double height;

	k = 32; ///////////
	height = 64 / s_pixel->walls->len_vec * 1662;
	y = 480 - (height / 2); ///// 960 / 2
	printf("x = %x, height = %f\n", x, height);
	while (k)
	{
		i = 0;
		tmp_y = y;
		while (i <= height)
		{
			if (!(x > 1920 || tmp_y > 960 || x < 0 || tmp_y < 0))
				ft_pixel_to_image(s_pixel, x , tmp_y, 0x0000FF);
			tmp_y++;
			i++;
		}
		x++;
		k--;
	}
}

void ft_cast_ray(t_elem *s_pixel)
{
	short int i;
	//double k;
	double dir;
	int x;

	x = 1920;
	i = 0;
	//k = 60.0 / 1920.0;
	//dir = (double)(s_pixel->player->pov - (60.0 / 2.0));
	dir = s_pixel->player->pov;
	if (dir > 360)
		dir = dir - 360;
	else if (dir < 0)
		dir = 360 - (dir * -1);
	s_pixel->player->dir = dir;
	printf("x = %d, y = %d\n", s_pixel->player->x_camera, s_pixel->player->y_camera);
	ft_find_wall(s_pixel, dir);
	/*while (++i < 60) // 60
	{
		if (dir > 360)
			dir = dir - 360;
		else if (dir < 0)
			dir = 360 - (dir * -1);
		ft_find_wall(s_pixel, dir);
		ft_draw_walls(s_pixel, x);
		dir++;// +k;
		x -= 32;
	}*/
}

void ft_draw_game(t_elem *s_pixel)
{
	ft_set_walls(s_pixel);
	ft_cast_ray(s_pixel);
}

void ft_main_draw(t_elem *s_pixel)
{
	ft_draw_game(s_pixel);
	ft_pixel_to_image_1(s_pixel, s_pixel->player->x_camera, s_pixel->player->y_camera, 0xFFFFFF);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr, s_pixel->img_ptr1, 0, 0);
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

	s_pixel->mlx_ptr = mlx_init();
	s_pixel->win_ptr = mlx_new_window(s_pixel->mlx_ptr, 1920, 960, "wolf3d");
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->img_ptr1 = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel, &s_pixel->size_line, &endian);
	s_pixel->begin_str1 = mlx_get_data_addr(s_pixel->img_ptr1, &bits_per_pixel, &s_pixel->size_line, &endian);
	s_pixel->player->x_camera = 900;
	s_pixel->player->y_camera = 500;
	s_pixel->player->pov = 110;
	s_pixel->walls->len_to_project_plane = 1662;;
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
	ft_prepare_programm(s_pixel);
	return (0);
}

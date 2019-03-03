/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:23:07 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/03 18:25:51 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

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

void ft_clean_display(t_elem *s_pixel)
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
}
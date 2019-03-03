/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:17:33 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/03 18:17:44 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void ft_get_addr_from_xpm(t_elem *s_pixel)
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
}

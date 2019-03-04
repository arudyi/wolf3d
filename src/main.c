/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:13 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 09:48:53 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_prepare_programm1(t_elem *s_pixel)
{
	s_pixel->player->level = 1;
	s_pixel->player->health = 100;
	s_pixel->player->ammo = 15;
	s_pixel->player->score = 0;
	s_pixel->player->lives = 3;
	s_pixel->key->go_left = 0;
	s_pixel->key->go_right = 0;
	s_pixel->key->go_up = 0;
	s_pixel->key->go_down = 0;
	s_pixel->key->see_left = 0;
	s_pixel->key->see_right = 0;
	s_pixel->key->sit = 0;
	s_pixel->texture->mandatory_mode = 1;
	s_pixel->texture->texture_mode = 1;
}

void	ft_prepare_programm(t_elem *s_pixel)
{
	int bits_per_pixel;
	int endian;

	s_pixel->mlx_ptr = mlx_init();
	s_pixel->win_ptr = mlx_new_window(s_pixel->mlx_ptr, 1920, 960, "wolf3d");
	s_pixel->img_ptr = mlx_new_image(s_pixel->mlx_ptr, 1920, 960);
	s_pixel->begin_str = mlx_get_data_addr(s_pixel->img_ptr, &bits_per_pixel,
	&s_pixel->size_line, &endian);
	s_pixel->player->pov = 90;
	s_pixel->walls->len_to_project_plane = 1662;
	s_pixel->texture->tex_width = 64;
	s_pixel->texture->tex_height = 64;
	ft_prepare_programm1(s_pixel);
	ft_load_texture(s_pixel);
	ft_get_addr_from_xpm(s_pixel);
	system("afplay ./Graphics/music.mp3 &");
	ft_main_draw(s_pixel);
}

int		main(int ac, char **av)
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
	system("leaks wolf3d");
	return (0);
}

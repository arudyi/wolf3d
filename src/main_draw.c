/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:29:29 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 09:10:05 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_cast_ray(t_elem *s_pixel)
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

void	ft_draw_game(t_elem *s_pixel)
{
	ft_cast_ray(s_pixel);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr,
	s_pixel->img_ptr, 0, 0);
	ft_draw_interface(s_pixel);
}

void	ft_draw_interface1(t_elem *s_pixel, char *str, char *tmp, char *tmp1)
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
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr,
	s_pixel->texture->arr_ptr_tex[12], 1600, 820);
}

void	ft_draw_interface(t_elem *s_pixel)
{
	char *str;
	char *tmp;
	char *tmp1;

	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr,
	s_pixel->texture->arr_ptr_tex[10], 887, 565);
	mlx_put_image_to_window(s_pixel->mlx_ptr, s_pixel->win_ptr,
	s_pixel->texture->arr_ptr_tex[11], 0, 730);
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

void	ft_main_draw(t_elem *s_pixel)
{
	ft_draw_game(s_pixel);
	mlx_hook(s_pixel->win_ptr, 2, 5, ft_key_press, s_pixel);
	mlx_hook(s_pixel->win_ptr, 3, 5, ft_key_release, s_pixel);
	mlx_hook(s_pixel->win_ptr, 17, 1L << 17, exit_x, s_pixel);
	mlx_hook(s_pixel->win_ptr, 6, 5, mouse_move, s_pixel);
	mlx_loop(s_pixel->mlx_ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:23:07 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 09:35:13 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

int		mouse_move(int x, int y, t_elem *s_pixel)
{
	static int pre_x = 910;

	y = 1;
	if ((pre_x > x || (x <= 0 && (pre_x > x || pre_x == x))))
		s_pixel->player->pov = (s_pixel->player->pov == 360) ? 2 :
		s_pixel->player->pov + 2;
	else if ((pre_x < x || x >= 1920))
		s_pixel->player->pov = (s_pixel->player->pov == 0) ? 358 :
		s_pixel->player->pov - 2;
	else if (x == pre_x)
		pre_x = x;
	pre_x = x;
	ft_after_key_mouse(s_pixel);
	ft_clean_display(s_pixel);
	ft_main_draw(s_pixel);
	return (0);
}

void	ft_change_pov(t_elem *s_pixel)
{
	if (s_pixel->key->see_left == 1)
		s_pixel->player->pov = (s_pixel->player->pov == 360) ? 2.0 :
		s_pixel->player->pov + 2.0;
	if (s_pixel->key->see_right == 1)
		s_pixel->player->pov = (s_pixel->player->pov == 0) ? 358.0 :
		s_pixel->player->pov - 2.0;
}

int		ft_after_key_mouse(t_elem *s_pixel)
{
	if (s_pixel->key->see_left == 1 || s_pixel->key->see_right == 1)
		ft_change_pov(s_pixel);
	else if (s_pixel->key->go_up == 1 || s_pixel->key->go_right == 1 ||
	s_pixel->key->go_left == 1 || s_pixel->key->go_down == 1)
		ft_change_player_dest(s_pixel, 0, 0, 0.0);
	return (0);
}

void	ft_change_game_mode(int key, t_elem *s_pixel)
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

int		ft_key_press(int key, t_elem *s_pixel)
{
	if (key == 53)
		exit_program(s_pixel);
	else if (key == 51)
		ft_refresh(s_pixel);
	else if (key == 83 || key == 84 || key == 86 || key == 87)
		ft_change_game_mode(key, s_pixel);
	else if (key == 0)
		s_pixel->key->go_left = 1;
	else if (key == 2)
		s_pixel->key->go_right = 1;
	else if (key == 13)
		s_pixel->key->go_up = 1;
	else if (key == 1)
		s_pixel->key->go_down = 1;
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

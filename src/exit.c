/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:23:07 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/03 18:26:39 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void ft_error_exit(t_elem *s_pixel)
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
}

void exit_program(t_elem *s_pixel)
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
}
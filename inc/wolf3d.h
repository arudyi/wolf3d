/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/02/13 13:27:26 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <pthread.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "../lib/libft/includes/libft.h"

typedef struct		s_walls
{
	double		dot_wall_x;
	double		dot_wall_y;
	double		len_ver;
	double		len_gor;
	double		len_vec;
	double 		len_to_project_plane;
}					t_walls;

typedef struct		s_player
{
 	int		x_camera;
	int		y_camera;
	double		pov;
	double		dir;
}					t_player;

typedef struct		s_elem
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	void			*img_ptr1;
	char			*begin_str;
	char			*begin_str1;
	int				size_line;
	t_player		*player;
	t_walls			*walls;
}					t_elem;

void ft_main_draw(t_elem *s_pixel);
int ft_is_wall(t_elem *s_pixel, int x, int y);

#endif
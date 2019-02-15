/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/02/15 17:09:25 by arudyi           ###   ########.fr       */
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
	short int		if_gor_line;
	int				offset_x;
	int				offset_y;
	double			angle_sin;
	double			angle_cos;
	double			angle_tg;
	double			dot_wall_x;
	double			dot_wall_y;
	double			len_ver;
	double			len_gor;
	double			len_vec;
	double 			len_to_project_plane;
}					t_walls;

typedef struct		s_player
{
 	int				x_camera;
	int				y_camera;
	int				pov;
	double			dir;
}					t_player;

typedef struct		s_texture
{
	int				size_line;
 	int				tex_width;
	int				tex_height;
	void			*arr_ptr_tex[13];
	char			*begin_str_tex[13];
}					t_texture;

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
	t_texture		*texture;
}					t_elem;

int ft_get_texture(t_elem *s_pixel, int offset, double step);
void ft_main_draw(t_elem *s_pixel);
int ft_is_wall(t_elem *s_pixel, int x, int y);

#endif
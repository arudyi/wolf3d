/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/02/19 19:16:53 by arudyi           ###   ########.fr       */
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
	short int 		level;
	short int 		health;
	short int 		ammo;
	short int 		score;
	short int 		lives;
	short int		if_sit;
 	int				x_camera;
	int				y_camera;
	int				pov;
	double			dir;
}					t_player;

typedef struct		s_texture
{
	short int		texture_now;
	int				size_line;
 	int				tex_width;
	int				tex_height;
	void			*arr_ptr_tex[30];
	char			*begin_str_tex[30];
}					t_texture;

typedef struct		s_map
{
	int				begin_x_camera;
	int				begin_y_camera;
	int				map_width;
	int				map_height;
	char			**map_game;
	int				**map_game_int;
}					t_map;

typedef struct		s_elem
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*begin_str;
	int				size_line;
	t_player		*player;
	t_walls			*walls;
	t_texture		*texture;
	t_map 			*map;
}					t_elem;

void ft_draw_interface(t_elem *s_pixel);
int ft_get_texture(t_elem *s_pixel, int offset, double step, double i);
void ft_main_draw(t_elem *s_pixel);
int ft_is_wall(t_elem *s_pixel, int x, int y);

#endif

/*

1111111444111111111111111111
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000009
3000000000000000000000000008
3000000010100000000000000007
3000000010100000000000000006
3000000010100000000000000005
3000000010100000000000000004
3000000000000000000000000003
3000000000000000000000000002
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1000000000000000000000000001
1111111444111111111111111111

*/
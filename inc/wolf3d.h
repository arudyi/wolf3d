/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/02/26 19:45:51 by arudyi           ###   ########.fr       */
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
 	int				x_camera; // double
	int				y_camera; // double
	int				pov;
	double			dir;
}					t_player;

typedef struct		s_texture
{
	short int		texture_now;
	int				size_line;
 	int				tex_width;
	int				tex_height;
	void			*arr_ptr_tex[50];
	char			*begin_str_tex[50];
}					t_texture;

typedef struct		s_map
{
	int				begin_x_camera; // double
	int				begin_y_camera; // double
	int				map_width;
	int				map_height;
	char			**map_game;
	int				**map_game_int;
}					t_map;

typedef struct		s_key
{
	short int		go_up;		
	short int		go_down;	
	short int		go_left;		
	short int		go_right;		
	short int		see_left;	
	short int		see_right;
	short int		sit;
}					t_key;

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
	t_key 			*key;
}					t_elem;

int mouse_move(int x, int y, t_elem *s_pixel);
void exit_program(t_elem *s_pixel);
int exit_x(t_elem *s_pixel);
void ft_change_player_dest(t_elem *s_pixel);
void ft_clean_display(t_elem *s_pixel);
void ft_refresh(t_elem *s_pixel);
void ft_change_pov(t_elem *s_pixel);
int ft_after_key_mouse(t_elem *s_pixel);
int ft_key_press(int key, t_elem *s_pixel);
int ft_key_release(int key, t_elem *s_pixel);
void ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color);
int ft_is_wall(t_elem *s_pixel, int x, int y);
void ft_which_texture(t_elem *s_pixel, int x, int y);
void ft_check_gor(t_elem *s_pixel, double dir);
void ft_check_ver(t_elem *s_pixel, double dir);
int ft_get_len_vec(t_elem *s_pixel, double wall_x, double wall_y);
void ft_find_wall(t_elem *s_pixel, double dir);
int ft_get_texture(t_elem *s_pixel, int offset, double step, double y);
void ft_draw_walls(t_elem *s_pixel, int x);
void ft_cast_ray(t_elem *s_pixel);
void ft_draw_game(t_elem *s_pixel);
void ft_draw_interface(t_elem *s_pixel);
void ft_main_draw(t_elem *s_pixel);
int ft_read_first_time(int fd);
int ft_validate(char **map, int i, t_elem *s_pixel, int row);
int ft_read_map(int fd, t_elem *s_pixel);
void ft_get_map(t_elem *s_pixel, int ac, char **av);
void ft_load_texture(t_elem *s_pixel);
void ft_prepare_programm(t_elem *s_pixel);

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
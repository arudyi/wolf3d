/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 10:10:18 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H// WOLF3D_H
# define FRACTAL_H

# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "../lib/libft/includes/libft.h"
# define validate1 ((s_pixel->j == 0 || s_pixel->j == s_pixel->size_is_right - 1) && !(48 < map[i][s_pixel->j] && map[i][s_pixel->j] <= 97)) || ((i == 0 || i == row - 1) && !(48 < map[i][s_pixel->j] && map[i][s_pixel->j] <= 97))
# define c_gor_ax (int)s_pixel->player->x_camera + ((int)s_pixel->player->y_camera - ay) / s_pixel->walls->angle_tg;
# define c_gor_ay ((int)s_pixel->player->y_camera >> 6 << 6) - 1 : ((int)s_pixel->player->y_camera >> 6 << 6) + 64;

typedef struct		s_walls
{
	double			nbr1_x;
	double			nbr1_y;
	double			nbr2_x;
	double			nbr2_y;
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
	int				x;
	int				y;
	short int		can_go_forward;
	short int       x_can_go;
	short int       y_can_go;
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
	int 			x;
	short int		mandatory_mode;
	short int		texture_mode;
	short int		texture_now;
	int				size_line;
 	int				tex_width;
	int				tex_height;
	void			*arr_ptr_tex[50];
	char			*begin_str_tex[50];
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
	int				i;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*begin_str;
	int				size_line;
	short int		is_player;
	int				size_column;
	int				size_is_right;
	int				size_row;
	int				j;
	t_player		*player;
	t_walls			*walls;
	t_texture		*texture;
	t_map 			*map;
	t_key 			*key;
}					t_elem;

int					mouse_move(int x, int y, t_elem *s_pixel);
void				exit_program(t_elem *s_pixel);
int					exit_x(t_elem *s_pixel);
void				ft_change_player_dest(t_elem *s_pixel, int tmp_x, int tmp_y, double pov);
void				ft_clean_display(t_elem *s_pixel);
void				ft_refresh(t_elem *s_pixel);
void				ft_change_pov(t_elem *s_pixel);
int					ft_after_key_mouse(t_elem *s_pixel);
int					ft_key_press(int key, t_elem *s_pixel);
int					ft_key_release(int key, t_elem *s_pixel);
void				ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color);
int					ft_is_wall(t_elem *s_pixel, int x, int y);
void				ft_which_texture(t_elem *s_pixel, int x, int y);
void				ft_check_gor(t_elem *s_pixel, double dir, double ax, double ay);
void				ft_check_ver1(t_elem *s_pixel, double bx, double by, short int is_in);
void				ft_check_gor1(t_elem *s_pixel, double ax, double ay, short int is_in);
void				ft_check_ver(t_elem *s_pixel, double dir, double ax, double ay);
double				ft_get_len_vec(t_elem *s_pixel, double wall_x, double wall_y);
void				ft_find_wall(t_elem *s_pixel, double dir, double tmp_gor, double tmp_ver);
int					ft_get_texture(t_elem *s_pixel, int offset, double step, double y);
void				ft_draw_walls(t_elem *s_pixel, int x);
void				ft_cast_ray(t_elem *s_pixel);
void				ft_draw_game(t_elem *s_pixel);
void				ft_draw_interface(t_elem *s_pixel);
void				ft_main_draw(t_elem *s_pixel);
int					ft_read_first_time(int fd, int count);
int					ft_validate(char **map, int i, t_elem *s_pixel, int row);
int					ft_read_map(int fd, t_elem *s_pixel, int row, char *line);
void				ft_get_map(t_elem *s_pixel, int ac, char **av);
void				ft_load_texture1(t_elem *s_pixel);
void				ft_load_texture(t_elem *s_pixel);
void				ft_prepare_programm(t_elem *s_pixel);
void				ft_draw_interface1(t_elem *s_pixel, char *str, char *tmp, char *tmp1);
void				ft_error_exit(t_elem *s_pixel);
void				ft_get_addr_from_xpm(t_elem *s_pixel);
void				ft_prepare_programm1(t_elem *s_pixel);
void				ft_get_width_height(t_elem *s_pixel, int row);
void				ft_create_int_map(t_elem *s_pixel);
void				ft_create_char_map(t_elem *s_pixel, char **map, int row);
int					ft_is_wall1(t_elem *s_pixel, int x, int y);
double				ft_get_angle_to_run(double a_tmp, double pov, short int gor, double a);
double				ft_get_angle_to_run1(double angle_tmp, double pov, double angle);
int					ft_check_is_wall(t_elem *s_pixel, int tmp_x, int tmp_y, short int m);
void				ft_check_is_wall1(t_elem *s_pixel, int tmp_x, int tmp_y, double pov);
void				ft_check_is_wall2(t_elem *s_pixel, int tmp_x, int tmp_y, double pov);
void				ft_change_player_dest_down(t_elem *s_pixel, int t_x, int t_y, double p);
void				ft_change_player_dest_down1(t_elem *s_pixel, int tmp_x, int tmp_y);
void				ft_change_player_dest_up(t_elem *s_pixel, int t_x, int tmp_y, double p);
void				ft_change_player_dest_up1(t_elem *s_pixel, int tmp_x, int tmp_y);
void				ft_change_game_mode(int key, t_elem *s_pixel);
void				ft_change_left_right(t_elem *s_pixel, int tmp_x, int tmp_y, double n_a);
void				ft_change_left_right1(t_elem *s_pixel, int tmp_x, int tmp_y, double n_a);
int					ft_ft_validate1(t_elem *s_pixel);
int					ft_ft_validate2(t_elem *s_pixel);
void				ft_find_player_position(t_elem *s_pixel, int i, int j);
void				ft_find_wall1(t_elem *s_pixel, double nbr1_x, double nbr1_y);
void				ft_find_wall2(t_elem *s_pixel, double nbr2_x, double nbr2_y);
void				ft_choose_len(t_elem *s_pixel, double tmp_gor, double tmp_ver);
int					ft_get_color_part(t_elem *s_pixel, int color);
int					ft_get_texture_part(t_elem *s_pixel, int offset, double step, double y);
void				ft_get_addr_from_xpm1(t_elem *s_pixel);
void				ft_load_texture2(t_elem *s_pixel);

#endif

/*

11111111111111
10000000000001
10000000000101
10050000000101
10010000000101
10100001110101
10000000000001
11111234567811

*/
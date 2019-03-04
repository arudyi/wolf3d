/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:50:17 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 11:57:31 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "../lib/libft/includes/libft.h"
# define V1 (s_pixel->j == 0 || s_pixel->j == s_pixel->size_is_right - 1)
# define V2 !(48 < map[i][s_pixel->j] && map[i][s_pixel->j] <= 97)
# define V3 (i == 0 || i == row - 1)
# define V4 !(48 < map[i][s_pixel->j] && map[i][s_pixel->j] <= 97)
# define C_GOR_AX1 ((int)s_pixel->player->y_camera >> 6 << 6) - 1
# define C_GOR_AX2 ((int)s_pixel->player->y_camera >> 6 << 6) + 64
# define C_G_Y1 (int)s_pixel->player->x_camera
# define C_G_Y2 (int)s_pixel->player->x_camera
# define C_G_Y3 (int)s_pixel->player->y_camera - ay
# define C_G_Y4 s_pixel->walls->angle_tg
# define CHECK1 (0 <= s_pixel->player->dir && s_pixel->player->dir <= 180)
# define CHECK2 !(0 <= s_pixel->player->dir && s_pixel->player->dir <= 180)
# define CHECK3 (90 <= s_pixel->player->dir && s_pixel->player->dir <= 270)
# define C_VER_BX1 ((int)s_pixel->player->x_camera >> 6 << 6) - 1.
# define C_VER_BX2 ((int)s_pixel->player->x_camera >> 6 << 6) + 64.
# define C_V_Y1 (int)s_pixel->player->y_camera
# define C_V_Y2 (int)s_pixel->player->y_camera
# define C_V_Y3 ((int)s_pixel->player->x_camera - bx)
# define C_V_Y4 s_pixel->walls->angle_tg
# define C_VER_IF1 bx < 0 || bx > s_pixel->map->map_width - 1
# define C_VER_IF2 by < 0 || by > s_pixel->map->map_height - 1
# define C_VER_IF3 ft_is_wall(s_pixel, bx + 1, by) == 0
# define N s_pixel->texture->texture_now

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
	double			len_to_project_plane;
}					t_walls;

typedef struct		s_player
{
	int				x;
	int				y;
	short int		can_go_forward;
	short int		x_can_go;
	short int		y_can_go;
	short int		level;
	short int		health;
	short int		ammo;
	short int		score;
	short int		lives;
	short int		if_sit;
	int				x_camera;
	int				y_camera;
	int				pov;
	double			dir;
}					t_player;

typedef struct		s_texture
{
	int				x;
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
	t_map			*map;
	t_key			*key;
}					t_elem;

int					mouse_move(int x, int y, t_elem *s_pixel);
void				exit_program(t_elem *s_pixel);
int					exit_x(t_elem *s_pixel);
void				ft_change_player_dest(t_elem *s_pixel,
					int tmp_x, int tmp_y, double pov);
void				ft_clean_display(t_elem *s_pixel);
void				ft_refresh(t_elem *s_pixel);
void				ft_change_pov(t_elem *s_pixel);
int					ft_after_key_mouse(t_elem *s_pixel);
int					ft_key_press(int key, t_elem *s_pixel);
int					ft_key_release(int key, t_elem *s_pixel);
void				ft_pixel_to_image(t_elem *s_pixel, int x, int y, int color);
int					ft_is_wall(t_elem *s_pixel, int x, int y);
void				ft_which_texture(t_elem *s_pixel, int x, int y);
void				ft_check_gor(t_elem *s_pixel,
					double dir, double ax, double ay);
void				ft_check_ver1(t_elem *s_pixel,
					double bx, double by, short int is_in);
void				ft_check_gor1(t_elem *s_pixel,
					double ax, double ay, short int is_in);
void				ft_check_ver(t_elem *s_pixel,
					double dir, double ax, double ay);
double				ft_get_len_vec(t_elem *s_pixel,
					double wall_x, double wall_y);
void				ft_find_wall(t_elem *s_pixel,
					double dir, double t_gor, double t_ver);
int					ft_get_texture(t_elem *s_pixel,
					int offset, double step, double y);
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
void				ft_draw_interface1(t_elem *s_pixel,
					char *str, char *tmp, char *tmp1);
void				ft_error_exit(t_elem *s_pixel);
void				ft_get_addr_from_xpm(t_elem *s_pixel);
void				ft_prepare_programm1(t_elem *s_pixel);
void				ft_get_width_height(t_elem *s_pixel, int row);
void				ft_create_int_map(t_elem *s_pixel);
void				ft_create_char_map(t_elem *s_pixel, char **map, int row);
int					ft_is_wall1(t_elem *s_pixel, int x, int y);
double				ft_get_angle_to_run(double a_tmp,
					double pov, short int gor, double a);
double				ft_get_angle_to_run1(double angle_tmp,
					double pov, double angle);
int					ft_check_is_wall(t_elem *s_pixel,
					int tmp_x, int tmp_y, short int m);
void				ft_check_is_wall1(t_elem *s_pixel,
					int tmp_x, int tmp_y, double pov);
void				ft_check_is_wall2(t_elem *s_pixel,
					int tmp_x,
					int tmp_y, double pov);
void				ft_change_player_dest_down(t_elem *s_pixel,
					int t_x, int t_y, double p);
void				ft_change_player_dest_down1(t_elem *s_pixel,
					int tmp_x, int tmp_y);
void				ft_change_player_dest_up(t_elem *s_pixel,
					int t_x, int tmp_y, double p);
void				ft_change_player_dest_up1(t_elem *s_pixel,
					int tmp_x, int tmp_y);
void				ft_change_game_mode(int key, t_elem *s_pixel);
void				ft_change_left_right(t_elem *s_pixel, int tmp_x,
					int tmp_y, double n_a);
void				ft_change_left_right1(t_elem *s_pixel, int tmp_x,
					int tmp_y, double n_a);
int					ft_ft_validate1(t_elem *s_pixel);
int					ft_ft_validate2(t_elem *s_pixel);
void				ft_find_player_position(t_elem *s_pixel, int i, int j);
void				ft_find_wall1(t_elem *s_pixel, double nbr1_x,
					double nbr1_y);
void				ft_find_wall2(t_elem *s_pixel, double nbr2_x,
					double nbr2_y);
void				ft_choose_len(t_elem *s_pixel, double tmp_gor,
					double tmp_ver);
int					ft_get_color_part(t_elem *s_pixel, int color);
int					ft_get_texture_part(t_elem *s_pixel, int offset,
					double step, double y);
void				ft_get_addr_from_xpm1(t_elem *s_pixel);
void				ft_load_texture2(t_elem *s_pixel);
void				exit_texture(void);
#endif

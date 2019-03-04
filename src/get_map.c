/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:17:38 by arudyi            #+#    #+#             */
/*   Updated: 2019/03/04 09:04:45 by arudyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/wolf3d.h"

void	ft_get_map(t_elem *s_pixel, int ac, char **av)
{
	short int	error;
	int			fd;
	char		*line;

	line = NULL;
	error = 0;
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "map") == 0)
		{
			s_pixel->i = -1;
			error = 1;
			if ((fd = open("map", O_RDONLY)) == -1)
				error = 0;
			if (ft_read_map(fd, s_pixel, 0, line) == 0)
				error = 0;
			close(fd);
		}
	}
	if (error == 0)
		ft_error_exit(s_pixel);
}

int		ft_read_map(int fd, t_elem *s_pixel, int row, char *line)
{
	char	**map;

	if ((row = ft_read_first_time(fd, 0)) < 2)
		return (0);
	close(fd);
	fd = open("map", O_RDONLY);
	map = (char **)malloc(sizeof(char *) * (row + 1));
	while (get_next_line(fd, &line))
	{
		map[++s_pixel->i] = ft_strdup(line);
		free(line);
	}
	close(fd);
	if (ft_validate(map, -1, s_pixel, row) == 0)
	{
		map[row] = NULL;
		s_pixel->i = -1;
		while (map[++s_pixel->i] != NULL)
			free(map[s_pixel->i]);
		free(map);
		return (0);
	}
	ft_create_char_map(s_pixel, map, row);
	ft_create_int_map(s_pixel);
	return (1);
}

int		ft_validate(char **map, int i, t_elem *s_pixel, int row)
{
	while (++i < row)
	{
		s_pixel->j = -1;
		if (map[i][0] == '\0')
			return (0);
		while (map[i][++s_pixel->j] != '\0')
		{
			if (map[i][s_pixel->j] == '0')
				ft_find_player_position(s_pixel, i, s_pixel->j);
			if (validate1)
				return (0);
			s_pixel->size_row++;
			s_pixel->size_column++;
			if (i == 0 && map[i][s_pixel->j + 1] == '\0')
				if (ft_ft_validate1(s_pixel) == 0)
					return (0);
			if (map[i][s_pixel->j + 1] == '\0' && i != 0)
				if (ft_ft_validate2(s_pixel) == 0)
					return (0);
		}
	}
	if (s_pixel->is_player == 0)
		return (0);
	ft_get_width_height(s_pixel, row);
	return (1);
}

void	ft_create_char_map(t_elem *s_pixel, char **map, int row)
{
	int i;

	map[row] = NULL;
	s_pixel->map->map_game = (char **)malloc(sizeof(char *) * (row + 1));
	i = -1;
	while (map[++i] != NULL)
	{
		s_pixel->map->map_game[i] = ft_strdup(map[i]);
		free(map[i]);
	}
	free(map);
	s_pixel->map->map_game[row] = NULL;
}

void	ft_create_int_map(t_elem *s_pixel)
{
	int i;
	int j;
	int k;

	i = -1;
	s_pixel->map->map_game_int = (int **)malloc(sizeof(int *) *
	(s_pixel->map->map_height >> 6));
	while (s_pixel->map->map_game[++i] != NULL)
	{
		j = -1;
		k = -1;
		s_pixel->map->map_game_int[i] = (int *)malloc(sizeof(int) *
		(s_pixel->map->map_width >> 6));
		while (s_pixel->map->map_game[i][++j] != '\0')
		{
			s_pixel->map->map_game_int[i][++k] = (48 <=
			s_pixel->map->map_game[i][j]
			&& s_pixel->map->map_game[i][j] <= 57) ?
			s_pixel->map->map_game[i][j]
			- '0' : s_pixel->map->map_game[i][j] - 0;
		}
		free(s_pixel->map->map_game[i]);
	}
	free(s_pixel->map->map_game);
}

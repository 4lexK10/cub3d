/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:50:36 by lboumahd          #+#    #+#             */
/*   Updated: 2025/03/19 20:35:12 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_v(t_map *map, int x, int y)
{
	while (map->map_tab[0][x])
	{
		y = 0;
		while (y < map->height)
		{
			if (y == 0 && !check_char(map->map_tab[y][x], "1"))
				return (0);
			if (is_space(map->map_tab[y][x]))
			{
				if (y > 0 && map->map_tab[y - 1][x] != '1')
					return (0);
				while (y < map->height && is_space(map->map_tab[y][x]))
					y++;
				if (y < map->height && map->map_tab[y][x] != '1')
					return (0);
			}
			if (y < map->height)
				y++;
		}
		if (!check_char(map->map_tab[y - 1][x], "1"))
			return (0);
		x++;
	}
	return (1);
}

int	check_h(t_map *map, int y, int x)
{
	while (map->map_tab[y])
	{
		x = 0;
		while (map->map_tab[y][x])
		{
			if (x == 0 && !check_char(map->map_tab[y][x], "1"))
				return (0);
			if (is_space(map->map_tab[y][x]))
			{
				if (x > 0 && map->map_tab[y][x - 1] != '1')
					return (0);
				while (map->map_tab[y][x]
					&& is_space(map->map_tab[y][x]))
					x++;
				if (map->map_tab[y][x] && map->map_tab[y][x] != '1')
					return (0);
			}
			if (map->map_tab[y][x])
				x++;
		}
		if (!check_char(map->map_tab[y][x - 1], "1"))
			return (0);
		y++;
	}
	return (1);
}

void	validate_map_closure(t_map *map, t_data *data)
{
	(void) data;
	if (!check_h(map, 0, 0) || !check_v(map, 0, 0))
	{
		ft_error("map not closed");
		if (data->info->texture_e)
			free(data->info->texture_e);
		if (data->info->texture_s)
			free(data->info->texture_s);
		if (data->info->texture_w)
			free(data->info->texture_w);
		if (data->info->texture_n)
			free(data->info->texture_n);
		if (data->info->path) 
			free(data->info->path);
		if (map->map_arr)
			free(map->map_arr);
		if (map->map_tab)
			free_map_tab(map->map_tab);
		free(map);
		free(data->info);
		exit(1);
	}
}

void	get_raw_data(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!get_first_info(data->raw_map, data->info, line))
		{
			if (!check_valid_line(line) || !check_infos(data->info))
			{
				free_data(data);
				free(line);
				ft_error("invalid input");
				exit(1);
			}
			data->raw_map->map_arr = add_to_line(
					data->raw_map->map_arr, line);
			free(line);
		}
		line = get_next_line(fd);
	}
	change_to_map_tab(data->raw_map);
	validate_map_closure(data->raw_map, data);
	close(fd);
}

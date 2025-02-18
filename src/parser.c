/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:50:36 by lboumahd          #+#    #+#             */
/*   Updated: 2025/02/18 18:40:33 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	check_char(char needle, char *haystack)
{
	int	i;

	i = 0;
	while (haystack[i])
	{
		if (needle == haystack[i])
			return (1);
		i++;
	}
	return (0);
}

int check_infos(t_info *infos)
{
    if(!infos->texture_E || !infos->texture_N || !infos->texture_S || !infos->texture_W)
        return (0);
    if(infos->c_floor_hex == -1|| infos->c_sky_hex == -1)
        return (0);
    return(1);
}

int check_v(t_map *map, int x, int y)
{
    while (map->map_tab[0][x])
    {
        y = 0;
        while (y < map->height)
        {
            if (y == 0 && !check_char(map->map_tab[y][x], "1 "))
                return (0);
            if (map->map_tab[y][x] == ' ')
            {
                if (y > 0 && map->map_tab[y - 1][x] != '1')
                    return (0);
                while (y < map->height && map->map_tab[y][x] == ' ')
                    y++;
                if (y < map->height && map->map_tab[y][x] != '1')
                    return (0);
            }
            if (y < map->height)
                y++;
        }
        if (!check_char(map->map_tab[y - 1][x], "1 "))
            return (0);
        x++;
    }
    return (1);
}

int check_h(t_map *map, int y, int x)
{
    while (map->map_tab[y])
    {
        x = 0;
        while (map->map_tab[y][x])
        {
            if (x == 0 && !check_char(map->map_tab[y][x], "1 "))
                return (0);
            if (map->map_tab[y][x] == ' ')
            {
                if (x > 0 && map->map_tab[y][x - 1] != '1')
                    return (0);
                while (map->map_tab[y][x] && map->map_tab[y][x] == ' ')
                    x++;
                if (map->map_tab[y][x] && map->map_tab[y][x] != '1')
                    return (0);
            }
            if (map->map_tab[y][x])
                x++;
        }
        if (!check_char(map->map_tab[y][x - 1], "1 "))
            return (0);
        y++;
    }
    return (1);
}

int is_space(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
		return(1);
    return(0);
}

int check_valid_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != 'W' &&
            line[i] != 'E' && line[i] != 'S' && line[i] != 'N' && !is_space(line[i]))
            return (0);
        i++;
    }
    return (1); 
}

void get_raw_data(t_data *data, int fd)
{
    char *line;

    while ((line = get_next_line(fd)))
    {
        if (!get_first_info(data->raw_map, data->info, line))
        {    
            if(!check_valid_line(line) || !check_infos(data->info))
            {
                free(line);
                ft_error("invalid input");
                exit(1);
            }
            data->raw_map->map_arr = add_to_line(data->raw_map->map_arr, line);
            free(line);
        }
    }
    change_to_map_tab(data->raw_map);
    if(!check_h(data->raw_map, 0, 0) || !check_v(data->raw_map, 0, 0))
        {
            ft_error("map not closed");
            exit(1);
        }
    close(fd);
}

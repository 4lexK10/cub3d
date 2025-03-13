/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:58:01 by linaboumahd       #+#    #+#             */
/*   Updated: 2025/03/13 19:17:48 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture(char **split_line)
{
	char	*path;
	int		path_len;

	if (!split_line[1] || split_line[2])
	{
		free_split(split_line);
		ft_error("Error: Invalid texture format\n");
		exit(1);
	}
	path = ft_strdup(split_line[1]);
	if (!path)
	{
		free_split(split_line);
		ft_error("Error: Memory allocation failed\n");
		exit(1);
	}
	path_len = ft_strlen(path);
	if (path[path_len - 1] == '\n')
		path[path_len - 1] = '\0';
	return (path);
}

int	handle_textures_and_colors(t_info *info, char **split_line)
{
	if (!ft_strncmp(split_line[0], "NO", 3))
		info->texture_N = get_texture(split_line);
	else if (!ft_strncmp(split_line[0], "SO", 3))
		info->texture_S = get_texture(split_line);
	else if (!ft_strncmp(split_line[0], "WE", 3))
		info->texture_W = get_texture(split_line);
	else if (!ft_strncmp(split_line[0], "EA", 3))
		info->texture_E = get_texture(split_line);
	else if (!ft_strncmp(split_line[0], "F", 2))
		info->c_floor_hex = process_rgb_input(split_line);
	else if (!ft_strncmp(split_line[0], "C", 2))
		info->c_sky_hex = process_rgb_input(split_line);
	else
		return (0);
	return (1);
}

int	check_textures(t_info *info)
{
	if (!info->texture_N || access(info->texture_N, F_OK) != 0
		|| access(info->texture_N, R_OK) != 0)
		return (0);
	if (!info->texture_S || access(info->texture_S, F_OK) != 0
		|| access(info->texture_S, R_OK) != 0)
		return (0);
	if (!info->texture_W || access(info->texture_W, F_OK) != 0
		|| access(info->texture_W, R_OK) != 0)
		return (0);
	if (!info->texture_E || access(info->texture_E, F_OK) != 0
		|| access(info->texture_E, R_OK) != 0)
		return (0);
	return (1);
}

char	**cleaned(char **split_line)
{
	int		i;
	int		j;
	char	*trimmed;

	i = 2;
	j = 2;
	while (split_line[i])
	{
		trimmed = trim_trailing_spaces(split_line[i]);
		if (ft_strlen(trimmed) > 0)
			split_line[j++] = trimmed;
		else
			free(split_line[i]);
		i++;
	}
	split_line[j] = NULL;
	return (split_line);
}

int	get_first_info(t_map *map, t_info *info, char *line)
{
	char	**split_line;

	if (map->map_arr)
		return (0);
	if (!line || (line[0] == '\n' && !line[1]))
	{
		free(line);
		return (1);
	}
	split_line = ft_split(line, ' ');
	split_line = cleaned(split_line);
	if (!split_line || !split_line[0])
	{
		free_split(split_line);
		return (0);
	}
	if (!handle_textures_and_colors(info, split_line))
	{
		free_split(split_line);
		return (0);
	}
	free_split(split_line);
	free(line);
	return (1);
}

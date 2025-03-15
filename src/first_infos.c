/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:58:01 by linaboumahd       #+#    #+#             */
/*   Updated: 2025/03/14 21:32:25 by lboumahd         ###   ########.fr       */
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
		info->texture_n = get_texture(split_line);
	else if (!ft_strncmp(split_line[0], "SO", 3))
		info->texture_s = get_texture(split_line);
	else if (!ft_strncmp(split_line[0], "WE", 3))
		info->texture_w = get_texture(split_line);
	else if (!ft_strncmp(split_line[0], "EA", 3))
		info->texture_e = get_texture(split_line);
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
	if (!info->texture_n || access(info->texture_n, F_OK) != 0
		|| access(info->texture_n, R_OK) != 0)
		return (0);
	if (!info->texture_s || access(info->texture_s, F_OK) != 0
		|| access(info->texture_s, R_OK) != 0)
		return (0);
	if (!info->texture_w || access(info->texture_w, F_OK) != 0
		|| access(info->texture_w, R_OK) != 0)
		return (0);
	if (!info->texture_e || access(info->texture_e, F_OK) != 0
		|| access(info->texture_e, R_OK) != 0)
		return (0);
	return (1);
}

char	**cleaned(char **split_line)
{
	int		i;
	int		j;
	char	*trimmed;
	char	**new_split;

	if (!split_line)
		return (NULL);
	new_split = malloc((ft_split_len(split_line) + 1) * sizeof(char *));
	if (!new_split)
		return (NULL);
	i = 0;
	j = 0;
	while (split_line[i])
	{
		trimmed = trim_trailing_spaces(split_line[i]);
		if (trimmed && ft_strlen(trimmed) > 0)
			new_split[j++] = trimmed;
		else
			free(trimmed);
		free(split_line[i]);
		i++;
	}
	new_split[j] = NULL;
	free(split_line);
	return (new_split);
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

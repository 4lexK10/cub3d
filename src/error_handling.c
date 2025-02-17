/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:50:53 by akloster          #+#    #+#             */
/*   Updated: 2025/01/18 20:57:56 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_split(char **split_line)
{
    int i = 0;

    if (!split_line)
        return;
    while (split_line[i])
        free(split_line[i++]);
    free(split_line);
}

int	ft_error(char *str)
{
	size_t	res;

	res = 0;
	while (*str)	
		res += write(STDERR_FILENO, str++, 1);
	res += write(STDERR_FILENO, "\n", 1);
	if (res != (ft_strlen(str) + 1))
		return (2);
	return (EXIT_FAILURE);
}


static void	free_texture(t_texture *tex)
{
	free(tex->path);
	free(tex->pixies);	
	tex->pixies = NULL;
}

void	free_all(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free_texture(&data->info->tex_N);
	free_texture(&data->info->tex_S);
	free_texture(&data->info->tex_W);
	free_texture(&data->info->tex_E);	
	if (data->raw_map)
	{
		for (int i = 0; data->raw_map->map_tab && data->raw_map->map_tab[i]; i++)
			free(data->raw_map->map_tab[i]);
		free(data->raw_map->map_tab);
		free(data->raw_map);
	}
	ft_memset(data, 0, sizeof(t_data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:49:34 by akloster          #+#    #+#             */
/*   Updated: 2025/03/19 19:47:52 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_info(t_info *info)
{
	info->c_floor_hex = -1;
	info->c_sky_hex = -1;
	info->texture_e = NULL;
	info->texture_n = NULL;
	info->texture_s = NULL;
	info->texture_w = NULL;
}

void	init_parsing(t_data *data, int fd)
{
	get_raw_data(data, fd);
	data->map = data->raw_map->map_tab;
	if (!check_textures(data->info))
	{
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
		if (data->raw_map->map_tab)
			free_map_tab(data->raw_map->map_tab);
		free(data->raw_map);
		free(data->info);
		ft_error("wrong textures");
		exit(1);
	}
}

void	init_data(t_data *data)
{
	data->raw_map = malloc(sizeof(t_map));
	if (!data->raw_map)
	{
		ft_error("Mem allocation\n");
		exit (1);
	}
	ft_memset(data->raw_map, 0, sizeof(t_map));
	data->raw_map->height = 0;
	data->raw_map->width = 0;
	data->info = malloc(sizeof(t_info));
	if (!data->info)
	{
		free(data->raw_map);
		data->raw_map = NULL;
		ft_error("Mem allocation\n");
		return ;
	}
	ft_memset(data->info, 0, sizeof(t_info));
	init_info(data->info);
	data->file = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->nbr_column = 0;
	data->raw_map->player = 0;
}

static void	convert(t_data *data)
{
	data->info->tex_n.path = data->info->texture_n;
	data->info->tex_s.path = data->info->texture_s;
	data->info->tex_e.path = data->info->texture_e;
	data->info->tex_w.path = data->info->texture_w;
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	(void) av;
	if (ac != 2)
		return (ft_error("error: incorrect number of arguments"));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (EXIT_FAILURE);
	}
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data);
	init_parsing(&data, fd);
	close(fd);
	convert(&data);
	if (init_mlx(&data) || init_textures(&data) || raycasting(&data, START))
		return (free_all(&data), EXIT_FAILURE);
	event_hook(&data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:49:34 by akloster          #+#    #+#             */
/*   Updated: 2025/02/17 19:53:09 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_info(t_info *info)
{
	info->c_floor_hex = -1;
	info->c_sky_hex = -1;
	info->texture_E = NULL;
	info->texture_N = NULL;
	info->texture_S = NULL;
	info->texture_W = NULL;
}
void	init_parsing(t_data *data, int fd)
{
    get_raw_data(data, fd);
    data->map = data->raw_map->map_tab;
	if (!check_textures(data->info))
	{
		ft_error("wrong textures");
		exit(1);
	}
	//free t_map and tinfo
}
void	init_data(t_data *data, char *path)
{   
    (void)path;	
    data->raw_map = malloc(sizeof(t_map)); //tofree
	if (!data->raw_map)
	{
		ft_error("Mem allocation\n");
		exit (1);
	}
	ft_memset(data->raw_map, 0, sizeof(t_map));
	data->raw_map->height = 0;
	data->raw_map->width = 0;
	data->info = malloc(sizeof(t_info)); //tofree
	if (!data->info)
	{
		free(data->raw_map);
		ft_error("Mem allocation\n");
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
	data->info->tex_N.path = data->info->texture_N;
	data->info->tex_S.path = data->info->texture_S;
	data->info->tex_E.path = data->info->texture_E;
	data->info->tex_W.path = data->info->texture_W;
}

int	main(int ac, char **av)
{
	t_data	data;
	int	fd;

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
	init_data(&data, av[1]);
	init_parsing(&data, fd);
	close(fd);
	convert(&data);
	if (init_mlx(&data) || init_textures(&data))
		return (EXIT_FAILURE);	
	raycasting(&data, START);
	event_hook(&data);
	free (data.info);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}

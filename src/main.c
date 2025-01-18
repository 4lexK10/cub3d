/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:49:34 by akloster          #+#    #+#             */
/*   Updated: 2025/01/18 19:30:34 by lboumahd         ###   ########.fr       */
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
	//check existence + validity of files 
    get_raw_data(data, fd);//fill fd into **raw_map
    data->map = data->raw_map->map_tab;
    //check extension
	//check validity  RGB - Txture - map
}
void	init_data(t_data *data, char *path)
{   
    (void)path;	
    data->raw_map = malloc(sizeof(t_map));
	if (!data->raw_map)
		ft_error("Mem allocation\n");
	//first_clean(path);
   // data->raw_map->line_count = get_number_of_lines(path);
	data->raw_map->height = 0;
	data->raw_map->width = 0;
	data->info = malloc(sizeof(t_info)); // free !!!!
	if (!data->info)
	    ft_error("Mem allocation\n");
	init_info(data->info);
	data->file = NULL;
    data->mlx = NULL;
    data->win = NULL;
    data->nbr_column = 0;
    data->raw_map->player = 0;
}
int	main(int ac, char **av)
{
	t_data	data;
    int fd;

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
	
	if (init_mlx(&data) || init_textures(&data))
		return (EXIT_FAILURE);	
	raycasting(&data, START);
	event_hook(&data);	
	mlx_loop(data.mlx);
    //a free dans la loop
      if (data.info)
    {
        free(data.info->texture_N);
        free(data.info->texture_S);
        free(data.info->texture_W);
        free(data.info->texture_E);
        free(data.info);
    }
    if (data.raw_map)
    {
        for (int i = 0; data.raw_map->map_tab && data.raw_map->map_tab[i]; i++)
            free(data.raw_map->map_tab[i]);
        free(data.raw_map->map_tab);
        free(data.raw_map);
    }
    close(fd);
	return (EXIT_SUCCESS);
}

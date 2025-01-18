/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:49:34 by akloster          #+#    #+#             */
/*   Updated: 2025/01/18 18:28:17 by lboumahd         ###   ########.fr       */
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
    //  printf("\nMap Layout now:\n");
    // for (int i = 0; data->map && data->map[i]; i++)
    //     printf("%s\n", data->map[i]); // a voir how to allocate
    //check extension
	//check validity  RGB - Txture - map
	//player position a voir avec alberto 
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

// int	main(int ac, char **av)
// {
// 	t_data data;
// 	int	fd;

// 	//ac & test check 
// 	fd = open(av[1], O_RDONLY);
// 	//fd error 
// 	init_data(&data, av[1]);
// 	init_parsing(&data, fd);
// 	//free + close fd
//free t_map and t_info 
// }

////////////////////////////TESTTTT//////////////////////////////////////////////////////


int main(int ac, char **av)
{
    t_data data;
    int fd;

    if (ac != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.cub>\n", av[0]);
        return (EXIT_FAILURE);
    }

 
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (EXIT_FAILURE);
    }


    init_data(&data, av[1]);
    init_parsing(&data, fd);

    printf("Parsed Textures:\n");
    printf("North: %s\n", data.info->texture_N);
    printf("South: %s\n", data.info->texture_S);
    printf("West: %s\n", data.info->texture_W);
    printf("East: %s\n", data.info->texture_E);

    printf("\nRGB Values:\n");
    printf("Floor: %lx\n", data.info->c_floor_hex);
    printf("Sky: %lx\n", data.info->c_sky_hex);

    printf("\nRawMap Layout:\n");
    for (int i = 0; data.raw_map->map_tab && data.raw_map->map_tab[i]; i++)
        printf("%s\n", data.raw_map->map_tab[i]);
    //  printf("\nMap Layout:\n");
    // for (int i = 0; data.map && data.map[i]; i++)
    //     printf("%s\n", data.map[i]);

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

    return (1);
}

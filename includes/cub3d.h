/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:05:23 by akloster          #+#    #+#             */
/*   Updated: 2025/01/18 18:56:44 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
// #include "mlx.h"
# include "../libft/libft.h"
# include "../GNL/get_next_line.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define X 0
# define Y 1

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
}	t_img;

typedef struct s_player
{
	float pos[2];
	float dir[2];
	float plane[2];
}	t_player;

typedef struct s_info{
	t_img	img;
	char	*path;
	int		width;
	int height;
	unsigned long c_floor_hex;
	unsigned long c_sky_hex;
	char	*texture_N;
	char	*texture_S;
	char	*texture_W;
	char	*texture_E;

} t_info;

typedef struct s_map
{
    char            *line;
    char            *map_arr;
    char            **map_tab;
    int             width;
    int             height;
    int             line_count;
	int				player;
} t_map;

typedef struct s_data
{
	char	**map;
	t_map 	*raw_map;
	t_info	*info;
	char **file;
	t_img 		img;
	void		*mlx;
	void		*win;
	int			nbr_column;
}	t_data;



int	init_mlx(t_data *data);
int raycasting(t_data *data);
int	ft_error(char *str);
void	get_player_vector(t_data *data, t_player *player);
void	set_vector(float vector[2], float x, float y);

//main
void	init_parsing(t_data *data, int fd);
void	init_data(t_data *data, char *path);

//first_info
int get_first_info(t_map *map, t_info *info, char *line);
char *get_texture(char **split_line);
unsigned long	process_rgb_input(char *line);
//parser 
void get_raw_data(t_data *data, int fd);
int get_number_of_lines(char *path);
//parser utils
char    *add_to_line(char *map_line, char *line);
void    change_to_map_tab(t_map *map);

//error


void free_split(char **split_line);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:05:23 by akloster          #+#    #+#             */
/*   Updated: 2025/02/19 19:44:44 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include "mlx.h"
# include "../libft/libft.h"
# include "../GNL/get_next_line.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define X 0
# define Y 1
# define ESC_KEY 0xff1b
# define W_KEY 0x0077 //is AZERTY now
# define A_KEY 0x0061 //is AZERTY now
# define S_KEY 0x0073
# define D_KEY 0x0064
# define START 0x0
# define LEFT_ARROW 0xff51
# define RIGHT_ARROW 0xff53
# define KEY_DOWN 2
# define FOV 0.66666
# define MOVE_SPEED 0.1

typedef struct s_img
{
	void	*ptr_img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
	int	width;
	int	height;
	int	*data;
}	t_img;

typedef struct s_wall
{	
	int	h;
	int	start;
	int	end;
	double	x;
	int	tex_X;
	int	tex_Y;
	double	pos;
	double	step;
	
}	t_wall;

typedef struct	s_ray
{
	double		cameraX;
	double		cast[2];
	double		side_dist[2];
	double		delta_dist[2];
	double		perp_dist;
	int		step[2];
	int		side;
	bool		hit;
	int		map_x;
	int		map_y;
}	t_ray;


typedef struct s_player
{
	double pos[2];
	double dir[2];
	double plane[2];
}	t_player;

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

typedef struct	s_texture
{
	char		*path;
	int		*pixies;
}	t_texture;

typedef struct s_info
{
	t_img	img;
	char	*path;
	int		width;
	int height;
	long c_floor_hex;
	long c_sky_hex;
	char	*texture_N;
	char	*texture_S;
	char	*texture_W;
	char	*texture_E;
	t_texture	tex_N;
	t_texture	tex_S;
	t_texture	tex_W;
	t_texture	tex_E;
} t_info;

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
	t_player	player;
}	t_data;

int	init_mlx(t_data *data);
int	raycasting(t_data *data, int keycode);
int	ft_error(char *str);
void	get_player_vector(t_data *data, t_player *player);
int	init_frame(t_data *data, t_img *frame);
void	render_column(t_data *data, t_img *frame, t_ray *ray, int x);
double	absf(double nbr);
void	pre_init(t_player *player, t_ray *ray, int x);
void	set_vector(double vector[2], double x, double y);
void	rotation(t_player *player, double a);
void	move_player(char **map, t_player *player, int keycode);
void	event_hook(t_data *data);
void	translation(char **map, t_player *player, int keycode);
int	init_textures(t_data *data);
void	free_all(t_data *data);
void	init_parsing(t_data *data, int fd);
void	init_data(t_data *data, char *path);

//first_info
int get_first_info(t_map *map, t_info *info, char *line);
char *get_texture(char **split_line);
long	process_rgb_input(char **line);
//parser 
void get_raw_data(t_data *data, int fd);
int check_textures(t_info *info);
char	*adapt_tab(char *map_line, int width);
//parser utils
char    *add_to_line(char *map_line, char *line);
void    change_to_map_tab(t_map *map);
int is_space(char c);
char *trim_trailing_spaces(char *str);
void	resize_map(t_map *map);
int check_valid_line(char *line);

//error


void free_split(char **split_line);

#endif

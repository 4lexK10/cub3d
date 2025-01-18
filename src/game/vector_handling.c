/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:31:03 by akloster          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:25 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_vector(double vector[2], double x, double y)
{
	vector[X] = x;
	vector[Y] = y;
}

static void	set_FOV(t_player *player, char dir)
{
	if (dir == 'N')
	{
		set_vector(player->dir, 0.0, 1);
		set_vector(player->plane, -FOV, 0.0);
	}
	else if (dir == 'E')	
	{
		set_vector(player->dir, -1, 0.0);
		set_vector(player->plane, 0.0, -FOV);
	}
	else if (dir == 'S')	
	{
		set_vector(player->dir, 0.0, -1);
		set_vector(player->plane, FOV, 0.0);
	}
	else if (dir == 'W')	
	{
		set_vector(player->dir, 1, 0.0);
		set_vector(player->plane, 0.0, FOV);
	}
	rotation(player, 0.001);
}

static void	get_pos(char **map, int *i, int *j)
{	
	*i = -1;
	*j = -1;
	while (map[++(*i)])
	{
		*j = -1;
		while (map[*i][++(*j)])
		{
			if (ft_isalpha(map[*i][*j]))
				return ;
		}
	}
}

void	get_player_vector(t_data *data, t_player *player)
{
	int	i;
	int	j;	

	get_pos(data->map, &i, &j);
	set_vector(player->pos, (double) j, (double) i);
	//(data->map)[i][j] = '0'; <-- fixes unwanted wall of initial position
	if (data->map[i][j - 1] == '1')
		player->pos[X] += 0.05;
	if (data->map[i - 1][j] == '1')
		player->pos[Y] += 0.05;
	set_FOV(player, data->map[i][j]);
}

void	move_player(char **map, t_player *player, int keycode)
{
	translation(map, player, keycode);
	if (keycode == LEFT_ARROW)
		rotation(player, -0.05);
	else if (keycode == RIGHT_ARROW)
		rotation(player, 0.05);
	else
		return ;
	player->plane[X] = (player->dir[Y] * FOV) /
		sqrtf(powf(player->dir[X], 2) + powf(player->dir[Y], 2));
	if (player->dir[Y] > 0 && player->plane[X] > 0)
		player->plane[X] = -player->plane[X];
	if (player->dir[Y] < 0 && player->plane[X] < 0)
		player->plane[X] = -player->plane[X];
	player->plane[Y] = sqrtf(powf(FOV, 2) - powf(player->plane[X], 2));
	if (player->dir[X] < 0 && player->plane[Y] > 0)
		player->plane[Y] = -player->plane[Y];
	if (player->dir[X] > 0 && player->plane[Y] < 0)
		player->plane[Y] = -player->plane[Y];
}




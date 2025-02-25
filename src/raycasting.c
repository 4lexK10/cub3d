/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:27:37 by akloster          #+#    #+#             */
/*   Updated: 2025/01/18 20:33:57 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calibrate_ray(t_player *player, t_ray *ray, int step, int axis)
{
	int	map_pos;

	if (axis == X)
		map_pos = ray->map_x;
	else
		map_pos = ray->map_y;
	ray->step[axis] = step;
	if (step == 1)
		ray->side_dist[axis] = (map_pos + 1 - player->pos[axis])
			* ray->delta_dist[axis];
	else
		ray->side_dist[axis] = (player->pos[axis] - map_pos)
			* ray->delta_dist[axis];
}

static void	init_ray(t_player *player, t_ray *ray, int x)
{
	pre_init(player, ray, x);
	if (ray->cast[X] != 0)
		ray->delta_dist[X] = absf(1.0 / ray->cast[X]);
	if (ray->cast[Y] != 0)
		ray->delta_dist[Y] = absf(1.0 / ray->cast[Y]);
	if (ray->cast[X] < 0)
		calibrate_ray(player, ray, -1, X);
	else
		calibrate_ray(player, ray, 1, X);
	if (ray->cast[Y] < 0)
		calibrate_ray(player, ray, -1, Y);
	else
		calibrate_ray(player, ray, 1, Y);
}

static void	dda(t_data *data, t_ray *ray)
{
	if (ray->side_dist[X] < ray->side_dist[Y])
	{
		ray->side_dist[X] += ray->delta_dist[X];
		ray->map_x += ray->step[X];
		ray->side = 0;
	}
	else
	{
		ray->side_dist[Y] += ray->delta_dist[Y];
		ray->map_y += ray->step[Y];
		ray->side = 1;
	}
	if (data->map[ray->map_y][ray->map_x] != '0')
		ray->hit = true;
}

int	raycasting(t_data *data, int keycode)
{
	t_ray	ray;
	t_img	frame;
	int		x;

	if (keycode == START)
		get_player_vector(data, &data->player);
	else
		move_player(data->map, &data->player, keycode);
	if (init_frame(data, &frame))
		return (ft_error("Error: mlx\n"));
	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_ray(&data->player, &ray, x);
		while (!ray.hit)
			dda(data, &ray);
		if (ray.side == 0)
			ray.perp_dist = ray.side_dist[X] - ray.delta_dist[X];
		else
			ray.perp_dist = ray.side_dist[Y] - ray.delta_dist[Y];
		render_column(data, &frame, &ray, x);
	}
	mlx_put_image_to_window(data->mlx, data->win, frame.ptr_img, 0, 0);
	mlx_destroy_image(data->mlx, frame.ptr_img);
	return (0);
}

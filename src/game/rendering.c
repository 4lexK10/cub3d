/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:28:40 by akloster          #+#    #+#             */
/*   Updated: 2025/01/14 17:10:59 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_img *frame, int x, int y, unsigned int color)
{
	if (x >= 0 && y >= 0 && x <= WIN_WIDTH && y <= WIN_HEIGHT
		&& ((y * WIN_WIDTH + x) <= (WIN_WIDTH * WIN_HEIGHT - 1)))
		frame->data[y * WIN_WIDTH + x] = color;
	else
		printf("(%d %d) %x\n", x, y, color); // <<TAKE out
}

static unsigned int	get_color(t_data *data, t_ray *ray, int x, int y)
{
	if (ray->side && ray->cast[Y] < 0)
		return (data->info.texture_S.pixies[y * TEX_WIDTH + x]);
	else if (ray->side && ray->cast[Y] > 0)
		return (data->info.texture_N.pixies[y * TEX_WIDTH + x]);
	else if (!ray->side && ray->cast[X] > 0)
		return (data->info.texture_W.pixies[y * TEX_WIDTH + x]);
	else if (!ray->side && ray->cast[X] < 0)
		return (data->info.texture_E.pixies[y * TEX_WIDTH + x]);
	return (0x000000);
}

static void	calibrate_texture(t_data *data, t_wall *wall, t_ray *ray)
{
	if (ray->side)
		wall->x = data->player.pos[X] + ray->perp_dist * ray->cast[X];
	else
		wall->x = data->player.pos[Y] + ray->perp_dist * ray->cast[Y];
	wall->x -= floor(wall->x);
	wall->tex_X = (int) (wall->x * (double) TEX_WIDTH);
	if (!ray->side && ray->cast[X] > 0) 
		wall->tex_X = TEX_WIDTH - wall->tex_X - 1;
	if (ray->side && ray->cast[Y] < 0)
		wall->tex_X = TEX_WIDTH - wall->tex_X - 1;
	wall->step = 1.0 * TEX_HEIGHT / wall->h;
	wall->pos = (wall->start - WIN_HEIGHT / 2 + wall->h / 2) * wall->step;	
}

void	render_column(t_data *data, t_img *frame, t_ray *ray, int x)
{
	t_wall		wall;
	int		y;

	wall.h = (int) (WIN_HEIGHT / ray->perp_dist); //hunt down perp_dist
	wall.start = -wall.h / 2 + WIN_HEIGHT / 2;
	if (wall.start < 0)
		wall.start = 0;
	wall.end = wall.h / 2 + WIN_HEIGHT / 2;
	if (wall.end >= WIN_HEIGHT)
		wall.end = WIN_HEIGHT - 1;
	calibrate_texture(data, &wall, ray);
	y = wall.start - 1;
	while (++y <= wall.end)
	{
		wall.tex_Y = (int) wall.pos & (TEX_HEIGHT - 1);
		wall.pos += wall.step;
		put_pixel(frame, x, y, get_color(data, ray, wall.tex_X, wall.tex_Y));
	}
	y = -1;
//	if (!x)
//		printf("wall %d ray->perp_disti %f start %d\n", wall.h, ray->perp_dist, wall.start);
	while (++y < wall.start)
	{
		put_pixel(frame, x, y, data->info.color_C);
	}
	y = wall.end;
	while (++y < WIN_HEIGHT)
		put_pixel(frame, x, y, data->info.color_F);
//	if (!x)
//		printf("!rendering\n");
}




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:03:04 by akloster          #+#    #+#             */
/*   Updated: 2025/01/14 17:13:00 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_img(t_data *data, t_texture *tex, char *path)
{
	t_img	img;
	int	x;
	int	y;

	y = -1;
	img.ptr_img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);
	if (!img.ptr_img)
		return (ft_error("error: malloc failed"));
	img.data = (int *)mlx_get_data_addr(img.ptr_img, &img.bpp, &img.line_length, &img.endian);
	tex->pixies = (int *)malloc(img.width * img.height * sizeof(int));
	if (!tex->pixies)
		return (mlx_destroy_image(data->mlx, img.ptr_img), ft_error("error: malloc failed"));
	while (++y < img.height)
	{
		x = -1;
		while (++x < img.width)
			tex->pixies[y * img.width + x] = img.data[y * img.width + x];
	}
	mlx_destroy_image(data->mlx, img.ptr_img);
	return (EXIT_SUCCESS);
}

static int	get_texture(t_data *data, t_texture *tex)
{
	int		fd;

	fd = open(tex->path, O_RDONLY);
	if (fd == -1)
		return (ft_error("error: open failed"));
	if (load_img(data, tex, tex->path))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_textures(t_data *data)
{
	if (get_texture(data, &data->info.texture_N)
		|| get_texture(data, &data->info.texture_S)
		|| get_texture(data, &data->info.texture_E)
		|| get_texture(data, &data->info.texture_W))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

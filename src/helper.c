/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:32:06 by lboumahd          #+#    #+#             */
/*   Updated: 2025/03/19 20:27:36 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_split_len(char **split)
{
	int	count;

	count = 0;
	if (!split)
		return (0);
	while (split[count])
		count++;
	return (count);
}

void	free_map_tab(char **map_tab)
{
	int	i;

	if (!map_tab)
		return ;
	i = 0;
	while (map_tab[i])
	{
		free(map_tab[i]);
		i++;
	}
	free(map_tab);
}
void	free_data(t_data *data)
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
	if (data->raw_map->map_arr)
		free(data->raw_map->map_arr);
	if (data->raw_map)
		free(data->raw_map);
	if (data->info)
		free(data->info);
}
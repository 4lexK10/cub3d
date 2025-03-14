/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:32:06 by lboumahd          #+#    #+#             */
/*   Updated: 2025/03/14 21:34:22 by lboumahd         ###   ########.fr       */
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

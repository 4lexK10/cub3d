/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 21:32:06 by lboumahd          #+#    #+#             */
/*   Updated: 2025/03/19 20:57:01 by lboumahd         ###   ########.fr       */
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

void	check_ext(char *av)
{
	int	i;

	i = ft_strlen(av);
	if (i < 4 || av[i - 4] != '.' || av[i - 3] != 'c'
		|| av[i - 2] != 'u' || av[i - 1] != 'b')
	{
		ft_error("Invalid file extension. Must be .cub");
		exit(1);
	}
}

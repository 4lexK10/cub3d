/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:38:42 by lboumahd          #+#    #+#             */
/*   Updated: 2025/02/19 19:40:45 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *trim_trailing_spaces(char *str)
{
    int len;
	
	if (!str) 
		return (NULL);
    len = ft_strlen(str);

    while (len > 0 && is_space((unsigned char)str[len - 1]))
        len--;
    str[len] = '\0';
    return (str);
}

void	resize_map(t_map *map)
{
	int	i;
	int j;
	int w_max;
	
	i = 0;
	w_max = 0;
	while (map->map_tab[i])
	{
		j = 0;
		while (map->map_tab[i][j])
			j++;
		if (j > w_max)
			w_max = j;
		i++;
	}
	i = 0;
	while (map->map_tab[i])
	{
		map->map_tab[i] = adapt_tab(map->map_tab[i], w_max);
		if (!map->map_tab[i])
			ft_error("Err Malloc");
		i++;
	}
	map->height = i;
}
int is_space(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
		return(1);
    return(0);
}

int check_valid_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1' && line[i] != '0' && line[i] != 'W' &&
            line[i] != 'E' && line[i] != 'S' && line[i] != 'N' && !is_space(line[i]))
            return (0);
        i++;
    }
    return (1); 
}

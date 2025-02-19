/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:06:11 by lboumahd          #+#    #+#             */
/*   Updated: 2025/02/19 19:40:17 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_size(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	return (i);
}

char    *add_to_line(char *map_line, char *line)
{
    int		size;
	int		i;
	char	*arr;
    
    i = 0;
	if (line[0] == '\n')
            line[0] = ' ';
	size = get_size(map_line) + get_size(line);
	arr = malloc(sizeof(char) * size + 2);
	if (arr == NULL)
		return (NULL);
	while (map_line && map_line[i])
	{
		arr[i] = map_line[i];
		i++;
	}
	while (*line)
		arr[i++] = *line++;
	arr[size] = ';';
	arr[size + 1] = '\0';
	if (map_line)
		free(map_line);
	return (arr);
}

char	*adapt_tab(char *map_line, int width)
{
	char *str;
	
	if ((int)ft_strlen(map_line) <= width)
	{
		str = malloc(sizeof(char) * width + 1);		
		if (!str)
			return (NULL);
		ft_memset(str, ' ', width);
	    str[width] = '\0';
    	if (map_line)
    	{
        	ft_memcpy(str, map_line, ft_strlen(map_line));
       		free(map_line);
    	}
    	return (str);
	}
	return(map_line);
}


void	check_player(char *map_arr, t_map *map)
{
	int i;

	i = 0;
	while(map_arr[i] && map_arr)
	{
		if(map_arr[i] == 'N' || map_arr[i] == 'S'
		|| map_arr[i] == 'E' || map_arr[i] == 'W')
			map->player++;
		i++;
	}
	if (map->player != 1)
	{
		ft_error("too many or no player detected");
		exit(1);
	}	
}
void    change_to_map_tab(t_map *map)
{
	if(!map || !map->map_arr)
	{	
		ft_error("empty map");
		exit(1);
	}
	check_player(map->map_arr, map);
	map->map_tab = ft_split(map->map_arr, ';');
	resize_map(map);
	free(map->map_arr);
    map->map_arr = NULL;
}


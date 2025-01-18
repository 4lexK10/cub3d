/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linaboumahdi <linaboumahdi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:00:59 by linaboumahd       #+#    #+#             */
/*   Updated: 2025/01/08 01:32:38 by linaboumahd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	count_commas(const char *line)
// {
// 	int	count;

// 	count = 0;
// 	while (*line)
// 	{
// 		if (*line == ',')
// 		{
// 			if (*(line + 1) == ',')
// 			{	
//                 ft_error("Error: Consecutive commas found.");
//                 exit(1);
//             }
//             count++;
// 		}
// 		line++;
// 	}
// 	return (count);
// }

// void	validate_rgb_range(const char **rgb_values)
// {
// 	int	i;
// 	int	val;

// 	i = 0;
// 	while (rgb_values[i])
// 	{
// 		val = ft_atoi(rgb_values[i]);
// 		if (val < 0 || val > 255)
// 		{	
//             ft_error("Error: RGB values must be between 0 and 255.");
//             exit(1);
//         }
// 		i++;
// 	}
// }

// void	validate_rgb_format(char *line)
// {
// 	if (count_commas(line) != 2)
// 	{
//         ft_error("Error: Input must contain 2 commas.");
//         exit(1);
//     }
// }

// unsigned long	get_hex_value(const char **rgb_values)
// {
// 	int				r;
// 	int				g;
// 	int				b;
// 	unsigned long	hex;

// 	r = ft_atoi(rgb_values[0]);
// 	g = ft_atoi(rgb_values[1]);
// 	b = ft_atoi(rgb_values[2]);
// 	hex = ((unsigned long)r << 24) | ((unsigned long)g << 16);
// 	hex |= ((unsigned long)b << 8) | 255;
// 	return (hex);
// }

// unsigned long	process_rgb_input(char *line)
// {
// 	char	**rgb_values;
// 	unsigned long	hex_value;

// 	validate_rgb_format(line);
// 	rgb_values = ft_split(line, ',');
// 	if (!rgb_values)
// 	{
//         ft_error("Error: Memory allocation failed.");
//         exit(1);
//     }
//     validate_rgb_range((const char **)rgb_values);
// 	hex_value = get_hex_value((const char **)rgb_values);
// 	free_split(rgb_values);
// 	return (hex_value);
// }

int	count_commas(const char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
		{
			if (*(line + 1) == ',')
			{
				ft_error("Error: Consecutive commas found.");
				exit(1);
			}
			count++;
		}
		line++;
	}
	return (count);
}

void	validate_rgb_range(const char **rgb_values)
{
	int	i;
	int	val;

	i = 0;
	while (rgb_values[i])
	{
		val = ft_atoi(rgb_values[i]);
		if (val < 0 || val > 255)
		{
			ft_error("Error: RGB values must be between 0 and 255.");
			exit(1);
		}
		i++;
	}
}

void	validate_rgb_format(char *line)
{
	if (count_commas(line) != 2)
	{
		ft_error("Error: Input must contain exactly 2 commas.");
		exit(1);
	}
}

unsigned long	get_hex_value(const char **rgb_val)
{
	int				r;
	int				g;
	int				b;
	unsigned long	hex;

	r = ft_atoi(rgb_val[0]);
	g = ft_atoi(rgb_val[1]);
	b = ft_atoi(rgb_val[2]);
	hex = ((unsigned long)r << 16) | ((unsigned long)g << 8) | (unsigned long)b;
	return (hex);
}

unsigned long	process_rgb_input(char *line)
{
	char			**rgb_values;
	unsigned long	hex_value;

	validate_rgb_format(line);
	rgb_values = ft_split(line, ',');
	if (!rgb_values)
	{
		ft_error("Error: Memory allocation failed.");
		exit(1);
	}
	validate_rgb_range((const char **)rgb_values);
	hex_value = get_hex_value((const char **)rgb_values);
	free_split(rgb_values);
	return (hex_value);
}

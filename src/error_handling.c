/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linaboumahdi <linaboumahdi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:50:53 by akloster          #+#    #+#             */
/*   Updated: 2025/01/07 00:17:27 by linaboumahd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_split(char **split_line)
{
    int i = 0;

    if (!split_line)
        return;
    while (split_line[i])
        free(split_line[i++]);
    free(split_line);
}

int	ft_error(char *str)
{
	while (*str)	
		write(STDERR_FILENO, str++, 1);
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

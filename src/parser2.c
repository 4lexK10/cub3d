/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:15:08 by lboumahd          #+#    #+#             */
/*   Updated: 2025/03/19 16:08:58 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_char(char needle, char *haystack)
{
	int	i;

	i = 0;
	while (haystack[i])
	{
		if (needle == haystack[i] || is_space(needle))
			return (1);
		i++;
	}
	return (0);
}

int	check_infos(t_info *infos)
{
	if (!infos->texture_e || !infos->texture_n
		|| !infos->texture_s || !infos->texture_w)
		return (0);
	if (infos->c_floor_hex == -1 || infos->c_sky_hex == -1)
		return (0);
	return (1);
}

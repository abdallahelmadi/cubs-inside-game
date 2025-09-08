/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:06:55 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/29 16:06:55 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_walls_top_bottom(char **map, int map_height)
{
	if (check_top_walls(map, map_height) != 0)
		return (1);
	if (check_bottom_walls(map, map_height) != 0)
		return (1);
	return (0);
}

int	check_walls_left_right(char **map, int map_height)
{
	int	i;
	int	len;

	i = 0;
	while (i < map_height)
	{
		if (!map[i])
		{
			printf("Error: Invalid map row\n");
			return (1);
		}
		len = ft_strlen(map[i]);
		while (len > 0 && (map[i][len - 1] == '\r' || map[i][len - 1] == '\n'))
			len--;
		if (check_left_walls(map, len, i) != 0)
			return (1);
		if (check_right_walls(map, len, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:46:59 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/12 19:46:59 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// int check_map()

int	once_player(char **map)
{
	int	i;
	int	j;
	int	count_player;

	i = 0;
	count_player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				count_player++;
				if (count_player > 1)
					return (write(2,
							"Error: Multiple players found in map\n", 37), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_invalid_space(char **map, int i, int j)
{
	int	map_height;
	int	len;

	map_height = 0;
	len = ft_strlen(map[i]);
	while (map[map_height])
		map_height++;
	if (map[i][j] == '0' || map[i][j] == 'N' ||
		map[i][j] == 'S' || map[i][j] == 'E' ||
		map[i][j] == 'W')
	{
		if (i - 1 < 0 || j >= ft_strlen(map[i - 1]) || map[i - 1][j] == ' ')
			return (1);
		if (i + 1 >= map_height || j >= ft_strlen(map[i + 1])
			|| map[i + 1][j] == ' ')
			return (1);
		if (j - 1 < 0 || map[i][j - 1] == ' ')
			return (1);
		if (j + 1 >= len || map[i][j + 1] == ' ')
			return (1);
	}
	return (0);
}

int	check_invalid_spaces(char **map, int map_height)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	while (i < map_height)
	{
		j = 1;
		len = ft_strlen(map[i]);
		while (j < len - 1)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'S' || map[i][j] == 'E' ||
				map[i][j] == 'W')
			{
				if (is_invalid_space(map, i, j) != 0)
					return (printf("Error : invalid spaces\n"), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_valid_characters(char **map, int map_height)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\r' || map[i][j] == '\n')
			{
				j++;
				continue ;
			}
			if (map[i][j] != '0' && map[i][j] != '1' &&
				map[i][j] != 'N' && map[i][j] != 'S' &&
				map[i][j] != 'E' && map[i][j] != 'W' &&
				map[i][j] != ' ')
				return (write(2, "Error: Invalid character in map\n", 32), 1);
			j++;
		}
		i++;
	}
	return (0);
}

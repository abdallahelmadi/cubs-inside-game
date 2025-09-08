/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:41:12 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/29 16:41:12 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_top_walls(char **map, int map_height)
{
	int	i;
	int	len;

	(void)map_height;
	len = ft_strlen(map[0]);
	while (len > 0 && (map[0][len - 1] == '\r' || map[0][len - 1] == '\n'))
		len--;
	i = 0;
	while (i < len && map[0][i] == ' ')
		i++;
	while (i < len)
	{
		if (map[0][i] != '1')
		{
			printf("Error: map is not surrounded by walls\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_bottom_walls(char **map, int map_height)
{
	int	j;
	int	len;

	len = ft_strlen(map[map_height - 1]);
	while (len > 0 && (map[map_height - 1][len - 1] == '\r'
		|| map[map_height - 1][len - 1] == '\n'))
		len--;
	j = 0;
	while (j < len && map[map_height - 1][j] == ' ')
		j++;
	while (j < len)
	{
		if (map[map_height - 1][j] == ' ')
			j++;
		else if (map[map_height - 1][j] != '1')
		{
			printf("Error: map is not surrounded by walls\n");
			return (1);
		}
		j++;
	}
	return (0);
}

int	check_left_walls(char **map, int len, int i)
{
	int	j;

	j = 0;
	while (j < len && map[i][j] == ' ')
		j++;
	if (j >= len || map[i][j] != '1')
	{
		printf("Error :map is not surrounded by walls\n");
		return (1);
	}
	return (0);
}

int	check_right_walls(char **map, int len, int i)
{
	int	j;

	j = len - 1;
	while (j >= 0 && map[i][j] == ' ')
		j--;
	if (j < 0 || map[i][j] != '1')
	{
		printf("Error: map is not surrounded by walls\n");
		return (1);
	}
	return (0);
}

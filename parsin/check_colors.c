/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:51:14 by bnafiai           #+#    #+#             */
/*   Updated: 2025/09/09 15:21:48 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_valid_colors(char **colors)
{
	int	i;
	int	j;

	i = 0;
	while (colors[i])
	{
		j = 0;
		while (colors[i][j])
		{
			if (colors[i][j] == 13 || colors[i][j] == '\n'
				|| colors[i][j] == ' ')
				break ;
			if (colors[i][j] < '0' || colors[i][j] > '9')
			{
				write(2, "Error : Invalid color value\n", 28);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_range_rgb(int color)
{
	if (color < 0 || color > 255)
	{
		write(2, "Error : Color value out of range (0-255)\n", 41);
		return (1);
	}
	return (0);
}

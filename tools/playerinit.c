/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:17:50 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/03 18:38:46 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	ft_charcmp(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (i + 1);
		i++;
	}
	return (0);
}

/*
  1. found the player position on the map;
  2. set player x, y position;
  3. set the angler depending on the character of player;

          1PI/2
	        .
	        .
	1PI . . . . . 0PI
	        .
		    .
		  3PI/2
*/

void	playerinit(t_globaldata *t)
{
	int (x), (y);
	y = -1;
	while (t->map[++y])
	{
		x = -1;
		while (t->map[y][++x])
		{
			if (ft_charcmp(t->map[y][x], "NEWS"))
			{
				t->player.px = x * TILE_SIZE + TILE_SIZE / 2;
				t->player.py = y * TILE_SIZE + TILE_SIZE / 2;
				if (t->map[y][x] == 'E')
					t->player.angler = 0;
				else if (t->map[y][x] == 'N')
					t->player.angler = PI / 2;
				else if (t->map[y][x] == 'W')
					t->player.angler = PI;
				else if (t->map[y][x] == 'S')
					t->player.angler = 3 * PI / 2;
				return ;
			}
		}
	}
}

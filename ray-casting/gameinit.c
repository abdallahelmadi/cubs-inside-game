/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:17:26 by abdael-m          #+#    #+#             */
/*   Updated: 2025/07/31 09:39:46 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_tile(t_init *g, int x, int y, int color)
{
	int i, j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(g->mlx, g->win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_init *g, double x1, double y1, double x2, double y2, int color)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	double steps = fmax(fabs(dx), fabs(dy));
	double x_inc = dx / steps;
	double y_inc = dy / steps;

	for (int i = 0; i < steps; i++)
	{
		mlx_pixel_put(g->mlx, g->win, x1 + 3, y1 + 3, color);
		x1 += x_inc;
		y1 += y_inc;
	}
}

void	draw_player(t_init *g, int x, int y, int color)
{
	int i, j;

	// Draw the player square centered around x, y
	int offset = 5;
	for (i = -offset; i < offset; i++)
	{
		for (j = -offset; j < offset; j++)
		{
			mlx_pixel_put(g->mlx, g->win, g->player.x + j, g->player.y + i, color);
		}
	}

	// Draw direction (FOV) line from center
	double line_length = 200;
	double x_end = g->player.x + cos(g->player.angle) * line_length;
	double y_end = g->player.y + sin(g->player.angle) * line_length;
	draw_line(g, g->player.x, g->player.y, x_end, y_end, 0x00FF00);
}

void	drawmap(t_init *g)
{
	(void)g;
	char map[20][15] = {
		"111111111111111",
		"100000000000001",
		"100010000000001",
		"110000001000001",
		"100011111000001",
		"100010001000001",
		"110010001000101",
		"100001000000101",
		"100P00000000101",
		"111111111111111",
		NULL
	};

	int i = 0;
	int j;

	while (ROWS > i)
	{
		j = 0;
		while (COLS > j)
		{
			if (map[i][j] == '1')
				draw_tile(g, j * TILE_SIZE, i * TILE_SIZE, 0xFFFFFF);
			else if (map[i][j] == 'P')
			{
				g->player.x = j * TILE_SIZE + 12;
				g->player.y = i * TILE_SIZE + 12;
				g->player.angle = 270 * (M_PI / 180.0);
				draw_player(g, j * TILE_SIZE + 14, i * TILE_SIZE + 14, 0xFF0000);
			}
			j++;
		}
		i++;
	}
}

void	gameinit(char **map, char **textures, int *colors)
{
	t_init	init;

	init.colors = colors;
	init.textures = textures;
	init.map = map;
	init.mlx = mlx_init();
	init.win = mlx_new_window(init.mlx, WIN_WIDTH, WIN_HEIGHT, "...");

	drawmap(&init);
 
	mlx_loop(init.mlx);
}

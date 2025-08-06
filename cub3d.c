/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:51:14 by abdael-m          #+#    #+#             */
/*   Updated: 2025/08/06 10:50:39 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_charcmp(char c, char *s)
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

int	handle_presses(int key, void *arg)
{
	(void)arg;
	if (key == 97)
		printf("a\n");
	if (key == 115)
		printf("s\n");
	if (key == 100)
		printf("d\n");
	if (key == 119)
		printf("w\n");
	if (key == 65307)
		printf("esc\n");
	if (key == 65361)
		printf("left\n");
	if (key == 65363)
		printf("right\n");
	return (0);
}

void	draw_wall(int start_x, int start_y, t_globaldata *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			mlx_pixel_put(data->mlx, data->win, start_x + x, start_y + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_player(char ty, int start_x, int start_y, t_globaldata *data)
{
	int	x;
	int	y;

	y = 0;
	data->player.px = start_x + 5;
	data->player.py = start_y + 5;
	if (ty == 'N')
		data->player.angler = 3 * PI / 2;
	else if (ty == 'S')
		data->player.angler = PI / 2;
	else if (ty == 'E')
		data->player.angler = 0;
	else if (ty == 'W')
		data->player.angler = PI;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			mlx_pixel_put(data->mlx, data->win, start_x + x + 5, start_y + y + 5, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	rerenderinit(t_globaldata *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_charcmp(data->map[y][x], "1"))
				draw_wall(x * TILE_SIZE, y * TILE_SIZE, data);
			else if (ft_charcmp(data->map[y][x], "NSEW"))
				draw_player(data->map[y][x], x * TILE_SIZE, y * TILE_SIZE, data);
			x++;
		}
		y++;
	}
}

void	gameinit(char **map, char **textures, int *colors)
{
	t_globaldata	data;

	data.colors = colors;
	data.textures = textures;
	data.map = map;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "...");
	rerenderinit(&data);
	mlx_hook(data.win, 2, 1L << 0, handle_presses, &data);
	mlx_loop(data.mlx);
}

int	main(void)
{
	gameinit(
		(char *[]){
		"111111111111111",
		"1S0000000000101",
		"100000000000101",
		"100000000000101",
		"100000000000101",
		"100000000000101",
		"100001000000101",
		"100000100000101",
		"100000010000001",
		"111111111111111",
		NULL
	},
		(char *[]){
		"./path_to_the_east_texture",
		"./path_to_the_east_texture",
		"./path_to_the_east_texture",
		"./path_to_the_east_texture",
		NULL
	},
		(int []){0xffffff, 0xff0000}
		);
	return (0);
}

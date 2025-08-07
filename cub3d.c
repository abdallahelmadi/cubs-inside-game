/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:51:14 by abdael-m          #+#    #+#             */
/*   Updated: 2025/08/07 09:03:40 by abdael-m         ###   ########.fr       */
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

int	is_wall(t_globaldata *data, double x, double y)
{
	int	map_x = (int)(x / TILE_SIZE);
	int	map_y = (int)(y / TILE_SIZE);

	if (data->map[map_y][map_x] == '1')
		return (1); // It's a wall
	return (0);     // It's empty
}

int	handle_press(int key, t_globaldata *arg)
{
	mlx_clear_window(arg->mlx, arg->win);
	double move_speed = 2.1; // Adjust speed as needed

	if (key == 119) // W
	{
		double new_x = arg->player.px + cos(arg->player.angler) * move_speed;
		double new_y = arg->player.py + sin(arg->player.angler) * move_speed;
		if (!is_wall(arg, new_x, new_y))
		{
			arg->player.px = new_x;
			arg->player.py = new_y;
		}
	}

	if (key == 115) // S
	{
		double new_x = arg->player.px - cos(arg->player.angler) * move_speed;
		double new_y = arg->player.py - sin(arg->player.angler) * move_speed;
		if (!is_wall(arg, new_x, new_y))
		{
			arg->player.px = new_x;
			arg->player.py = new_y;
		}
	}

	if (key == 97) // A
	{
		double new_x = arg->player.px + cos(arg->player.angler - M_PI_2) * move_speed;
		double new_y = arg->player.py + sin(arg->player.angler - M_PI_2) * move_speed;
		if (!is_wall(arg, new_x, new_y))
		{
			arg->player.px = new_x;
			arg->player.py = new_y;
		}
	}

	if (key == 100) // D
	{
		double new_x = arg->player.px + cos(arg->player.angler + M_PI_2) * move_speed;
		double new_y = arg->player.py + sin(arg->player.angler + M_PI_2) * move_speed;
		if (!is_wall(arg, new_x, new_y))
		{
			arg->player.px = new_x;
			arg->player.py = new_y;
		}
	}

	if (key == 65361)
	{
    	arg->player.angler -= M_PI/12;
		if (arg->player.angler < 0)
    		arg->player.angler += 2 * M_PI;
	}
    if (key == 65363)
	{
    	arg->player.angler += M_PI/12;
		if (arg->player.angler > 2 * M_PI)
    		arg->player.angler -= 2 * M_PI;
	}

	if (key == 65307) // ESC
		exit(0);
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

void	draw_player(t_globaldata *data)
{
	int	x;
	int	y;

	y = -2;
	while (y < 2)
	{
		x = -2;
		while (x < 2)
		{
			mlx_pixel_put(data->mlx, data->win,
				data->player.px + x, data->player.py + y, 0xFF0000);
			x++;
		}
		y++;
	}

	double dx = cos(data->player.angler);
	double dy = sin(data->player.angler);
	double i = 0;
	while (1)
	{
		int line_x = data->player.px + dx * i;
		int line_y = data->player.py + dy * i;
		if (data->map[line_y / TILE_SIZE][line_x / TILE_SIZE] == '1')
			break ;
		mlx_pixel_put(data->mlx, data->win, line_x, line_y, 0x00FF00); // Green
		i += 1;
	}
}

int	rerenderinit(t_globaldata *data)
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
			x++;
		}
		y++;
	}
	draw_player(data); // Draw player after map ✅
	return (0);
}

void	playerinit(t_globaldata *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_charcmp(data->map[y][x], "NEWS"))
			{
				data->player.px = x * TILE_SIZE + TILE_SIZE / 2;
				data->player.py = y * TILE_SIZE + TILE_SIZE / 2;
				if (data->map[y][x] == 'N')
					data->player.angler = M_PI / 2;
				else if (data->map[y][x] == 'S')
					data->player.angler = 3 * M_PI / 2;
				else if (data->map[y][x] == 'E')
					data->player.angler = 0;
				else if (data->map[y][x] == 'W')
					data->player.angler = M_PI;
				return ;
			}
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
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	playerinit(&data);
	mlx_loop_hook(data.mlx, rerenderinit, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_press, &data);
	mlx_loop(data.mlx);
}

int	main(void)
{
	gameinit(
		(char *[]){
		"111111111111111",
		"1N0000000000101",
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

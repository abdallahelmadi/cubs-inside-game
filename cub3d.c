/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:51:14 by abdael-m          #+#    #+#             */
/*   Updated: 2025/08/07 19:14:54 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_collision(t_globaldata *t, double x, double y)
{
	int	map_x = (int)(x / TILE_SIZE);
	int	map_y = (int)(y / TILE_SIZE);

	if (t->map[map_y][map_x] == '1')
		return (1); // It's a wall
	return (0);     // It's empty
}

int tester(t_globaldata *data, double x, double y)
{
	double buffer = 1; // margin for player size
	return (
		check_collision(data, x + buffer, y + buffer) ||
		check_collision(data, x - buffer, y + buffer) ||
		check_collision(data, x + buffer, y - buffer) ||
		check_collision(data, x - buffer, y - buffer)
	);
}

int	handle_press(int key, t_globaldata *t)
{
	mlx_clear_window(t->mlx, t->win);
	double move_speed = 2.1; // Adjust speed as needed

	if (key == 119) // W
	{
		double new_x = t->player.px + cos(t->player.angler) * move_speed;
		double new_y = t->player.py + sin(t->player.angler) * move_speed;
		if (!check_collision(t, new_x, new_y))
		{
			t->player.px = new_x;
			t->player.py = new_y;
		}
	}

	if (key == 115) // S
	{
		double new_x = t->player.px - cos(t->player.angler) * move_speed;
		double new_y = t->player.py - sin(t->player.angler) * move_speed;
		if (!check_collision(t, new_x, new_y))
		{
			t->player.px = new_x;
			t->player.py = new_y;
		}
	}

	if (key == 97) // A
	{
		double new_x = t->player.px + cos(t->player.angler - M_PI_2) * move_speed;
		double new_y = t->player.py + sin(t->player.angler - M_PI_2) * move_speed;
		if (!check_collision(t, new_x, new_y))
		{
			t->player.px = new_x;
			t->player.py = new_y;
		}
	}

	if (key == 100) // D
	{
		double new_x = t->player.px + cos(t->player.angler + M_PI_2) * move_speed;
		double new_y = t->player.py + sin(t->player.angler + M_PI_2) * move_speed;
		if (!check_collision(t, new_x, new_y))
		{
			t->player.px = new_x;
			t->player.py = new_y;
		}
	}

	if (key == 65361)
	{
    	t->player.angler -= M_PI/12;
		if (t->player.angler < 0)
    		t->player.angler += 2 * M_PI;
	}
    if (key == 65363)
	{
    	t->player.angler += M_PI/12;
		if (t->player.angler > 2 * M_PI)
    		t->player.angler -= 2 * M_PI;
	}

	if (key == 65307) // ESC
		exit(0);
	return (0);
}



















/*
  draw rays, explaination:
  - ray_angle: stores the angle of the current ray being cast.
  - ray_step: the amount to increment the angle after each ray.
  - i: how many rays will cast.

  - 136: FOV / WIN_WIDTH to get the step of rays moves each time in radians (not px).
  - 137: the dection of view - FOV / 2, to get the first rays radians position.
  - 141, 144: if the ray_angle get out of 2PI range, set it to correct one.
*/

void	ft_drawrays(t_globaldata *t)
{
	double	(ray_angle), (ray_step);
	int		i;

	ray_step = FOV / WIN_WIDTH;
	ray_angle = t->player.angler - (FOV / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		if (ray_angle < 0)
			ray_angle += PI2;
		if (ray_angle > PI2)
			ray_angle -= PI2;



		// still here
		double dx = cos(ray_angle);
		double dy = sin(ray_angle);
		double length = 0;
		while (1)
		{
			int ray_x = t->player.px + dx * length;
			int ray_y = t->player.py + dy * length;

			if (ray_x < 0 || ray_x >= WIN_WIDTH || ray_y < 0 || ray_y >= WIN_HEIGHT)
				break ;
			if (tester(t, ray_x, ray_y))
				break ;
			mlx_pixel_put(t->mlx, t->win, ray_x, ray_y, 0x00FF00);
			length += 1;
		}
		// still here



		ray_angle += ray_step;
	}
}

/*
  draw player position
*/
void	ft_drawplayer(t_globaldata *t)
{
	int	(x), (y);

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			mlx_pixel_put(t->mlx, t->win, t->player.px + x, t->player.py + y, 0xFF0000);
	}
}

/*
  draw 2D wall
*/
void	ft_drawwall(int start_x, int start_y, t_globaldata *t)
{
	int	(x), (y);

	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
		{
			if (y == 0 || x == 0)
				mlx_pixel_put(t->mlx, t->win, start_x + x, start_y + y, 0x000000);
			else
				mlx_pixel_put(t->mlx, t->win, start_x + x, start_y + y, 0xFFFFFF);
		}
	}
}

/*
  the function how's rerender each time to make animation,
  we call all fucntion of fetching here.
*/
int	rerenderinit(t_globaldata *t)
{
	int	(x), (y);

	y = -1;
	while (t->map[++y])
	{
		x = -1;
		while (t->map[y][++x])
		{
			if (ft_charcmp(t->map[y][x], "1"))
				ft_drawwall(x * TILE_SIZE, y * TILE_SIZE, t);
		}
	}
	ft_drawplayer(t);
	ft_drawrays(t);
	return (0);
}

/*
  check if c include in s
*/
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

/*
  first we try to found the play as N, E, W or S,
  and define the player x, y position.
  in finall we define the view deriction in angler.
*/
void	playerinit(t_globaldata *t)
{
	int	(x), (y);

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
				if (t->map[y][x] == 'N')
					t->player.angler = PI / 2;
				else if (t->map[y][x] == 'E')
					t->player.angler = 0;
				else if (t->map[y][x] == 'W')
					t->player.angler = PI;
				else if (t->map[y][x] == 'S')
					t->player.angler = 3 * PI / 2;
				return ;
			}
		}
	}
}

/*
  create globaldata struct and open window, create player and define it.
  and rerend the rerenderinit function to create animation.
  with the press events handling.
*/
void	gameinit(char **map, char **textures, int *colors)
{
	t_globaldata	t;

	t.colors = colors;
	t.textures = textures;
	t.map = map;
	t.mlx = mlx_init();
	t.win = mlx_new_window(t.mlx, WIN_WIDTH, WIN_HEIGHT, "...");
	playerinit(&t);
	mlx_loop_hook(t.mlx, rerenderinit, &t);
	mlx_hook(t.win, 2, 1L << 0, handle_press, &t);
	mlx_loop(t.mlx);
}

/*
  you just need to call gameinit function to start the ray-casting.
  the values of parameter, should be allocted to be freed later.
*/
int	main(void)
{
	gameinit(
		(char *[]){
		"111111111111111",
		"1W0000000000101",
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
		(int []){0xFFFFFF, 0xFF0000}
	);
	return (0);
}

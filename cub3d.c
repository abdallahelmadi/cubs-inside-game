/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:51:14 by abdael-m          #+#    #+#             */
/*   Updated: 2025/08/09 10:50:37 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
  draw background
*/
void	ft_drawbackground(t_globaldata *t)
{
	int (y), (x);
	y = -1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			my_mlx_pixel_put(&t->img, x, y, t->colors[0]);
	}
	y = WIN_HEIGHT / 2;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			my_mlx_pixel_put(&t->img, x, y, t->colors[1]);
	}
}

/*
  helper function to set a pixel in the image buffer
*/
void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
  helper for handle_press function
*/
void	ft_setplayer(double new_x, double new_y, t_globaldata *t)
{
	if (!is_player_colliding(t, new_x, new_y))
	{
		t->player.px = new_x;
		t->player.py = new_y;
	}
}

/*
  helper for handle_press function
*/
void	ft_setfov(double angler, t_globaldata *t)
{
	t->player.angler = angler;
	if (t->player.angler < 0)
		t->player.angler += 2 * PI;
	else if (t->player.angler > 2 * PI)
		t->player.angler -= 2 * PI;
}

/*
  exit and free the resources
*/
int	exit_free(t_globaldata *t)
{
	(void)t;
	exit(0);
}

/*
  handle the key press
  - 119: W
  - 115: S
  - 97: A
  - 100: D
  - 65361: left
  - 65363: right
  - 65307: esc
*/
int	handle_press(int key, t_globaldata *t)
{
	if (key == 119)
		ft_setplayer(t->player.px + cos(t->player.angler) * 3,
			t->player.py + sin(t->player.angler) * 3, t);
	if (key == 115)
		ft_setplayer(t->player.px - cos(t->player.angler) * 3,
			t->player.py - sin(t->player.angler) * 3, t);
	if (key == 97)
		ft_setplayer(t->player.px + cos(t->player.angler - PID2) * 3,
			t->player.py + sin(t->player.angler - PID2), t);
	if (key == 100)
		ft_setplayer(t->player.px + cos(t->player.angler + PID2) * 3,
			t->player.py + sin(t->player.angler + PID2) * 3, t);
	if (key == 65361)
		ft_setfov(t->player.angler - PI / 12, t);
	if (key == 65363)
		ft_setfov(t->player.angler + PI / 12, t);
	if (key == 65307)
		exit_free(t);
	return (0);
}

/*
  check if the position is inside wall
*/
int	ft_iswall(t_globaldata *t, double currently_x, double currently_y)
{
	return (t->map[(int)(currently_y / TILE_SIZE)]
		[(int)(currently_x / TILE_SIZE)] == '1');
}

/*
  check all direction of FOV of player if are walls
*/
int	is_player_colliding(t_globaldata *t, double currently_x, double currently_y)
{
	double	buffer;

	buffer = 1;
	return (ft_iswall(t, currently_x + buffer, currently_y + buffer)
		|| ft_iswall(t, currently_x - buffer, currently_y + buffer)
		|| ft_iswall(t, currently_x + buffer, currently_y - buffer)
		|| ft_iswall(t, currently_x - buffer, currently_y - buffer));
}

/*
  draw rays as 3D
*/
void	ft_drwaray3d(t_globaldata *t, int length, int index)
{
	int (wall_height), (wall_start), (wall_end), (y);
	wall_height = (int)(((double)TILE_SIZE / (double)length) * \
		((WIN_WIDTH / 2) / tan(FOV / 2)));
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	if (wall_height < 1)
		wall_height = 1;
	wall_start = (WIN_HEIGHT / 2) - (wall_height / 2);
	wall_end = (WIN_HEIGHT / 2) + (wall_height / 2);
	y = wall_start;
	while (y < wall_end)
	{
		my_mlx_pixel_put(&t->img, index, y, 0xFFFFFF);
		y++;
	}
}

/*
  draw rays, explaination:
  - i: how many rays will cast.
  - ray_angle: stores the angle of the current ray being cast.
  - ray_step: the amount to increment the angle after each ray.
  - dx, dy: the value each time we need to add to the position (.., ..)
    to still in same angler for x and y.
  - ray_x, ray_y: position of player + the angler position movment, for make
    the ray in the way of angler.

  - 140: FOV / WIN_WIDTH to get the step of rays
    moves each time in radians (not px).
  - 141: the dection of view - FOV / 2, to get the first rays radians position.
  - 145, 148: if the ray_angle get out of 2PI range, set it to correct one.
*/
void	ft_drawrays(t_globaldata *t)
{
	double (ray_angle), (ray_step), (dx), (dy), (ray_x), (ray_y), (i), (length);
	ray_step = FOV / WIN_WIDTH;
	ray_angle = t->player.angler - (FOV / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		if (ray_angle < 0)
			ray_angle += PI2;
		if (ray_angle > PI2)
			ray_angle -= PI2;
		dx = cos(ray_angle);
		dy = sin(ray_angle);
		ray_x = t->player.px + dx;
		ray_y = t->player.py + dy;
		length = 0;
		while (!is_player_colliding(t, ray_x, ray_y))
		{
			ray_x += dx;
			ray_y += dy;
			length++;
		}
		ft_drwaray3d(t, length, i);
		ray_angle += ray_step;
	}
}

/*
  draw player position
*/
void	ft_drawplayer(t_globaldata *t)
{
	int (x), (y);
	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			my_mlx_pixel_put(&t->img, t->player.px + x,
				t->player.py + y, 0xFF0000);
	}
}

/*
  draw 2D wall
*/
void	ft_drawwall(int start_x, int start_y, t_globaldata *t, int color)
{
	int (x), (y);
	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
			my_mlx_pixel_put(&t->img, start_x + x, start_y + y, color);
	}
}

/*
  the function how's rerender each time to make animation,
  we call all fucntion of fetching here.
*/
int	rerenderinit(t_globaldata *t)
{
	ft_drawbackground(t);
	ft_drawrays(t);
	mlx_put_image_to_window(t->mlx, t->win, t->img.ptr, 0, 0);
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
	t.img.ptr = mlx_new_image(t.mlx, WIN_WIDTH, WIN_HEIGHT);
	t.img.data = mlx_get_data_addr(t.img.ptr, &t.img.bpp,
			&t.img.size_line, &t.img.endian);
	mlx_loop_hook(t.mlx, rerenderinit, &t);
	mlx_hook(t.win, 2, 1L << 0, handle_press, &t);
	mlx_hook(t.win, 17, 0L, exit_free, &t);
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
		"1N0000000000001",
		"100000000000001",
		"110000000000001",
		"100000000000001",
		"100000000000001",
		"100000000000001",
		"100000000000101",
		"100000000000001",
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
		(int []){0x0000AA, 0xFF0000}
		);
	return (0);
}

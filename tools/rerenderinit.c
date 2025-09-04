/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerenderinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:58:28 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/04 16:18:34 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	drawbackground(t_globaldata *t)
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
	return ;
}

// static void	ft_drwaray3d(t_globaldata *t, double length, int index, double ray_angle, int color)
// {
// 	double	corrected_length;
// 	int		wall_height, wall_start, wall_end, y;

// 	// Fish-eye correction
// 	corrected_length = length * cos(ray_angle - t->player.angler);
// 	if (corrected_length < 0.0001)
// 		corrected_length = 0.0001;

// 	wall_height = (int)((TILE_SIZE / corrected_length) *
// 		((WIN_WIDTH / 2) / tan(FOV / 2)));

// 	if (wall_height > WIN_HEIGHT)
// 		wall_height = WIN_HEIGHT;
// 	if (wall_height < 1)
// 		wall_height = 1;

// 	wall_start = (WIN_HEIGHT / 2) - (wall_height / 2);
// 	wall_end = (WIN_HEIGHT / 2) + (wall_height / 2);

// 	for (y = wall_start; y < wall_end; y++)
// 		my_mlx_pixel_put(&t->img, index, y, color);
// }

static void	raycasting(t_globaldata *t)
{
	double (ray_angle), (ray_step);
	int (i), (plr_x), (plr_y);
	ray_step = FOV / WIN_WIDTH;
	ray_angle = t->player.angler - (FOV / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		plr_x = (int)(t->player.px / TILE_SIZE);
		plr_y = (int)(t->player.py / TILE_SIZE);

		// double rayDirX = cos(ray_angle);
		// double rayDirY = sin(ray_angle);

		// // Distance to next grid boundary in x/y
		// double deltaDistX = fabs(1 / rayDirX);
		// double deltaDistY = fabs(1 / rayDirY);

		// // Step direction and initial sideDist
		// int stepX, stepY;
		// double sideDistX, sideDistY;

		// if (rayDirX < 0)
		// {
		// 	stepX = -1;
		// 	sideDistX = (t->player.px / TILE_SIZE - mapX) * deltaDistX;
		// }
		// else
		// {
		// 	stepX = 1;
		// 	sideDistX = (mapX + 1.0 - t->player.px / TILE_SIZE) * deltaDistX;
		// }
		// if (rayDirY < 0)
		// {
		// 	stepY = -1;
		// 	sideDistY = (t->player.py / TILE_SIZE - mapY) * deltaDistY;
		// }
		// else
		// {
		// 	stepY = 1;
		// 	sideDistY = (mapY + 1.0 - t->player.py / TILE_SIZE) * deltaDistY;
		// }

		// // DDA loop
		// int hit = 0;
		// int side = 0; // 0 = vertical, 1 = horizontal
		// while (!hit)
		// {
		// 	if (sideDistX < sideDistY)
		// 	{
		// 		sideDistX += deltaDistX;
		// 		mapX += stepX;
		// 		side = 0;
		// 	}
		// 	else
		// 	{
		// 		sideDistY += deltaDistY;
		// 		mapY += stepY;
		// 		side = 1;
		// 	}
		// 	if (t->map[mapY][mapX] == '1') // wall
		// 		hit = 1;
		// }

		// // Perpendicular distance
		// double perpWallDist;
		// if (side == 0)
		// 	perpWallDist = (sideDistX - deltaDistX) * TILE_SIZE;
		// else
		// 	perpWallDist = (sideDistY - deltaDistY) * TILE_SIZE;

		// // Choose color based on wall orientation
		// int color;
		// if (side == 0) // vertical wall
		// {
		// 	if (rayDirX > 0)
		// 		color = 0xFF0000; // red (east)
		// 	else
		// 		color = 0x00FF00; // green (west)
		// }
		// else // horizontal wall
		// {
		// 	if (rayDirY > 0)
		// 		color = 0x0000FF; // blue (south)
		// 	else
		// 		color = 0xFFFF00; // yellow (north)
		// }

		// // Draw vertical slice
		// ft_drwaray3d(t, perpWallDist, i, ray_angle, color);

		ray_angle += ray_step;
	}
}

/*
  rerend this function as while, for fetch the updates of game;
*/

int	rerenderinit(t_globaldata *t)
{
	drawbackground(t);
	raycasting(t);
	mlx_put_image_to_window(t->mlx, t->win, t->img.ptr, 0, 0);
	return (0);
}

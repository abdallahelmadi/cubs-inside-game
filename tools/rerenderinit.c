/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerenderinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:58:28 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/06 17:35:59 by abdael-m         ###   ########.fr       */
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

static void	raycasting(t_globaldata *t)
{
	double (ray_angle), (ray_step), (index), (ray_dir_x), (ray_dir_y),
	(delta_dist_x), (delta_dist_y), (side_dist_x), (side_dist_y),
	(map_x), (map_y), (step_x), (step_y), (side), (perp_wall_dist),
	(texture_index);
	ray_angle = t->player.angler - (FOV / 2);
	ray_step = FOV / WIN_WIDTH;
	index = -1;
	while (++index < WIN_WIDTH)
	{
		if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		map_x = (int)(t->player.px / TILE_SIZE);
		map_y = (int)(t->player.py / TILE_SIZE);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (t->player.px - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - t->player.px) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (t->player.py - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - t->player.py) * delta_dist_y;
		}
		side = 0;
		while (1)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (t->map[(int)map_x][(int)map_y] == '1')
				break ;
		}
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);
		if (side == 0)
		{
			texture_index = 2;
			if (ray_dir_x > 0)
				texture_index = 3;
		}
		else
		{
			texture_index = 0;
			if (ray_dir_y > 0)
				texture_index = 1;
		}
		// FECTH RAYS
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerenderinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:58:28 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/05 11:43:36 by abdael-m         ###   ########.fr       */
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
	double (ray_angle), (ray_step), (ray_direction_x), (ray_direction_y),
	(delta_dist_x), (delta_dist_y), (side_dist_x), (side_dist_y), (wall_dist);

	int (i), (plr_x), (plr_y), (step_x), (step_y), (side), (texture);

	t_image (wrapper);

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
		ray_direction_x = cos(ray_angle);
		ray_direction_y = sin(ray_angle);
		delta_dist_x = fabs(1 / ray_direction_x);
		delta_dist_y = fabs(1 / ray_direction_y);
		if (ray_direction_x < 0)
		{
			step_x = -1;
			side_dist_x = (t->player.px / TILE_SIZE - plr_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (plr_x + 1.0 - t->player.px / TILE_SIZE) * delta_dist_x;
		}
		if (ray_direction_y < 0)
		{
			step_y = -1;
			side_dist_y = (t->player.py / TILE_SIZE - plr_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (plr_y + 1.0 - t->player.py / TILE_SIZE) * delta_dist_y;
		}
		side = 0;
		while (1)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				plr_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				plr_y += step_y;
				side = 1;
			}
			if (t->map[plr_y][plr_x] == '1')
				break ;
		}
		if (side == 0)
			wall_dist = (side_dist_x - delta_dist_x) * TILE_SIZE;
		else
			wall_dist = (side_dist_y - delta_dist_y) * TILE_SIZE;
		if (side == 0)
		{
			texture = 2;
			if (ray_direction_x > 0)
				texture = 3;
		}
		else
		{
			texture = 0;
			if (ray_direction_y > 0)
				texture = 1;
		}
		wrapper = t->wrapper[texture];





		// correct fisheye
		double corrected_len = wall_dist * cos(ray_angle - t->player.angler);
		if (corrected_len < 0.0001)
			corrected_len = 0.0001;

		// wall slice height
		int wall_height = (int)((TILE_SIZE / corrected_len) *
			((WIN_WIDTH / 2) / tan(FOV / 2)));
		if (wall_height > WIN_HEIGHT)
			wall_height = WIN_HEIGHT;

		int wall_start = (WIN_HEIGHT / 2) - (wall_height / 2);
		int wall_end   = (WIN_HEIGHT / 2) + (wall_height / 2);

		// find exact x in texture
		double wall_x;
		if (side == 0)
			wall_x = t->player.py / TILE_SIZE + wall_dist / TILE_SIZE * ray_direction_y;
		else
			wall_x = t->player.px / TILE_SIZE + wall_dist / TILE_SIZE * ray_direction_x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * wrapper.width);
		if ((side == 0 && ray_direction_x > 0) || (side == 1 && ray_direction_y < 0))
			tex_x = wrapper.width - tex_x - 1;

		// vertical step in texture
		double step = 1.0 * wrapper.height / wall_height;
		double tex_pos = (wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step;

		// draw vertical stripe
		for (int y = wall_start; y < wall_end; y++)
		{
			int tex_y = (int)tex_pos & (wrapper.height - 1);
			tex_pos += step;

			char *pixel = wrapper.data + (tex_y * wrapper.size_line + tex_x * (wrapper.bpp / 8));
			int color = *(int *)pixel;

			my_mlx_pixel_put(&t->img, i, y, color);
		}



		
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

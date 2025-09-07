/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerenderinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:58:28 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/07 18:25:53 by abdael-m         ###   ########.fr       */
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

static int	get_texture_color(t_image *texture, int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0) tex_x = 0;
	if (tex_x >= texture->width) tex_x = texture->width - 1;
	if (tex_y < 0) tex_y = 0;
	if (tex_y >= texture->height) tex_y = texture->height - 1;
	color = *(unsigned int *)(texture->data
			+ tex_y * texture->size_line
			+ tex_x * (texture->bpp / 8));
	return (color & 0xFFFFFF);
}

static void	raycasting(t_globaldata *t)
{
	double	ray_angle;
	double	ray_step;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	corrected_dist;
	double	wall_hit_x_in_texture;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		texture_index;
	int		perp_wall_on_screen;
	int		start_draw;
	int		end_draw;
	int		index;

	ray_angle = t->player.angler - (FOV / 2);
	ray_step = FOV / WIN_WIDTH;
	index = -1;
	while (++index < WIN_WIDTH)
	{
		if (ray_angle > 2 * PI) ray_angle -= 2 * PI;
		if (ray_angle < 0) ray_angle += 2 * PI;
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		map_x = (int)(t->player.px / TILE_SIZE);
		map_y = (int)(t->player.py / TILE_SIZE);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (t->player.px / TILE_SIZE - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - t->player.px / TILE_SIZE) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (t->player.py / TILE_SIZE - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - t->player.py / TILE_SIZE) * delta_dist_y;
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
			if (t->map[map_y][map_x] == '1')
				break ;
		}
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		if (side == 0)
			texture_index = (ray_dir_x > 0) ? 3 : 2;
		else
			texture_index = (ray_dir_y > 0) ? 1 : 0;

		corrected_dist = perp_wall_dist * cos(ray_angle - t->player.angler);
		perp_wall_on_screen = (int)(WIN_HEIGHT / corrected_dist);
		start_draw = (WIN_HEIGHT / 2) - (perp_wall_on_screen / 2);
		end_draw = (WIN_HEIGHT / 2) + (perp_wall_on_screen / 2);
		if (start_draw < 0) start_draw = 0;
		if (end_draw >= WIN_HEIGHT) end_draw = WIN_HEIGHT - 1;

		/* --------- حساب X في التكتشر --------- */
		if (side == 0)
			wall_hit_x_in_texture = t->player.py / TILE_SIZE + perp_wall_dist * ray_dir_y;
		else
			wall_hit_x_in_texture = t->player.px / TILE_SIZE + perp_wall_dist * ray_dir_x;
		wall_hit_x_in_texture -= floor(wall_hit_x_in_texture);
		int tex_x = (int)(wall_hit_x_in_texture * t->wrapper[texture_index].width);

		/* --------- حساب Y في التكتشر بالـ step --------- */
		double step = (double)t->wrapper[texture_index].height / (double)perp_wall_on_screen;
		double tex_pos = (start_draw - WIN_HEIGHT / 2.0 + perp_wall_on_screen / 2.0) * step;

		for (int y = start_draw; y < end_draw; y++)
		{
			int tex_y = (int)tex_pos;
			tex_pos += step;
			int color = get_texture_color(&t->wrapper[texture_index], tex_x, tex_y);
			my_mlx_pixel_put(&t->img, index, y, color);
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

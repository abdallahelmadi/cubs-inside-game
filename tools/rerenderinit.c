/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerenderinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:58:28 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/07 17:44:10 by abdael-m         ###   ########.fr       */
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

static int	get_texture_color(t_get_texture_color_params params, t_globaldata *t)
{
	t_image	*texture;
	int		texture_line_x_position;
	int		texture_line_y_position;
	int		color;
	double	wall_height;

	texture = &t->wrapper[params.texture_index];
	texture_line_x_position = (int)(params.wall_hit_x_in_texture * texture->width);
	if (texture_line_x_position < 0)
		texture_line_x_position = 0;
	if (texture_line_x_position >= texture->width)
		texture_line_x_position = texture->width - 1;
	wall_height = params.wall_end - params.wall_start;
	texture_line_y_position = (int)(((params.tindex - params.wall_start) / wall_height) * texture->height);
	if (texture_line_y_position < 0)
		texture_line_y_position = 0;
	if (texture_line_y_position >= texture->height)
		texture_line_y_position = texture->height - 1;
	color = *(unsigned int *)(texture->data + texture_line_y_position * texture->size_line + texture_line_x_position * (texture->bpp / 8));
	return (color);
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
	int		tindex;
	int		index;
	t_get_texture_color_params	params;
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
		{
			if (ray_dir_x > 0)
				texture_index = 3;
			else
				texture_index = 2;
		}
		else
		{
			if (ray_dir_y > 0)
				texture_index = 1;
			else
				texture_index = 0;
		}
		corrected_dist = perp_wall_dist * cos(ray_angle - t->player.angler);
		perp_wall_on_screen = (int)(WIN_HEIGHT / corrected_dist);
		start_draw = (WIN_HEIGHT / 2) - (perp_wall_on_screen / 2);
		end_draw = (WIN_HEIGHT / 2) + (perp_wall_on_screen / 2);
		if (start_draw < 0)
			start_draw = 0;
		if (end_draw >= WIN_HEIGHT)
			end_draw = WIN_HEIGHT - 1;
		tindex = start_draw - 1;
		while (++tindex < end_draw)
		{
			if (side == 0)
				wall_hit_x_in_texture = t->player.py / TILE_SIZE + perp_wall_dist * ray_dir_y;
			else
			    wall_hit_x_in_texture = t->player.px / TILE_SIZE + perp_wall_dist * ray_dir_x;
			wall_hit_x_in_texture -= floor(wall_hit_x_in_texture);
			params.tindex = tindex;
			params.wall_start = start_draw;
			params.wall_end = end_draw;
			params.texture_index = texture_index;
			params.wall_hit_x_in_texture = wall_hit_x_in_texture;
			my_mlx_pixel_put(&t->img, index, tindex, get_texture_color(params, t));
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

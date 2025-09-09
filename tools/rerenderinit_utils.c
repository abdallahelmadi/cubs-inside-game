/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerenderinit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:52:18 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/09 11:56:46 by abdael-m         ###   ########.fr       */
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

static int	get_texture_color(t_image *texture, int tex_x, int tex_y)
{
	int	color;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	color = *(unsigned int *)(texture->data
			+ tex_y * texture->size_line
			+ tex_x * (texture->bpp / 8));
	return (color & 0xFFFFFF);
}

/*
  rerenderinit util;
*/

void	rerenderinit_utils(t_globaldata *t, double *ray_angle, int line_index)
{
	double (ray_dir_x), (ray_dir_y), (delta_dist_x), (delta_dist_y),
	(side_dist_x), (side_dist_y), (perp_wall_dist), (corrected_dist),
	(perp_wall_on_screen), (wall_hit_x_in_texture), (step_texture_step),
	(tex_y);
	int (map_x), (map_y), (step_x), (step_y), (side),
	(texture_index), (start_draw), (end_draw),
	(tex_x), (tindex);
	if (*ray_angle > 2 * PI)
		*ray_angle -= 2 * PI;
	if (*ray_angle < 0)
		*ray_angle += 2 * PI;
	ray_dir_x = cos(*ray_angle);
	ray_dir_y = sin(*ray_angle);
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	map_x = (int)(t->player.px / TILE_SIZE);
	map_y = (int)(t->player.py / TILE_SIZE);
	step_x = -1;
	step_y = -1;
	if (ray_dir_x < 0)
		side_dist_x = (t->player.px / TILE_SIZE - map_x) * delta_dist_x;
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - t->player.px / TILE_SIZE) * delta_dist_x;
	}
	if (ray_dir_y < 0)
		side_dist_y = (t->player.py / TILE_SIZE - map_y) * delta_dist_y;
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - t->player.py / TILE_SIZE) * delta_dist_y;
	}
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
			texture_index = 0;
		else
			texture_index = 1;
	}
	corrected_dist = perp_wall_dist * cos(*ray_angle - t->player.angler);
	perp_wall_on_screen = (int)(WIN_HEIGHT / corrected_dist);
	start_draw = (WIN_HEIGHT / 2) - (perp_wall_on_screen / 2);
	end_draw = (WIN_HEIGHT / 2) + (perp_wall_on_screen / 2);
	if (start_draw < 0)
		start_draw = 0;
	if (end_draw >= WIN_HEIGHT)
		end_draw = WIN_HEIGHT - 1;
	if (side == 0)
		wall_hit_x_in_texture = t->player.py / TILE_SIZE \
		+ perp_wall_dist * ray_dir_y;
	else
		wall_hit_x_in_texture = t->player.px / TILE_SIZE \
		+ perp_wall_dist * ray_dir_x;
	wall_hit_x_in_texture -= floor(wall_hit_x_in_texture);
	tex_x = (int)(wall_hit_x_in_texture * t->wrapper[texture_index].width);
	step_texture_step = (double)t->wrapper[texture_index].height \
		/ (double)perp_wall_on_screen;
	tex_y = (start_draw - WIN_HEIGHT / 2.0 + perp_wall_on_screen \
		/ 2.0) * step_texture_step;
	tindex = start_draw - 1;
	while (++tindex < end_draw)
	{
		my_mlx_pixel_put(&t->img, line_index, tindex,
			get_texture_color(&t->wrapper[texture_index], tex_x, (int)tex_y));
		tex_y += step_texture_step;
	}
}

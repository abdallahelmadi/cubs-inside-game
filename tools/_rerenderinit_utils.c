/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rerenderinit_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:27:39 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/10 09:28:46 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calcule_side_dists(t_rerenderinit_utils_variables *v,
	t_globaldata *t)
{
	(*v).step_x = -1;
	(*v).step_y = -1;
	if ((*v).ray_dir_x < 0)
		(*v).side_dist_x = (t->player.px / TILE_SIZE - \
			(*v).map_x) * (*v).delta_dist_x;
	else
	{
		(*v).step_x = 1;
		(*v).side_dist_x = ((*v).map_x + 1.0 - t->player.px / TILE_SIZE) * \
			(*v).delta_dist_x;
	}
	if ((*v).ray_dir_y < 0)
		(*v).side_dist_y = (t->player.py / TILE_SIZE - (*v).map_y) * \
			(*v).delta_dist_y;
	else
	{
		(*v).step_y = 1;
		(*v).side_dist_y = ((*v).map_y + 1.0 - t->player.py / TILE_SIZE) * \
			(*v).delta_dist_y;
	}
}

void	dda_logic(t_rerenderinit_utils_variables *v, t_globaldata *t)
{
	while (1)
	{
		if ((*v).side_dist_x < (*v).side_dist_y)
		{
			(*v).side_dist_x += (*v).delta_dist_x;
			(*v).map_x += (*v).step_x;
			(*v).side = 0;
		}
		else
		{
			(*v).side_dist_y += (*v).delta_dist_y;
			(*v).map_y += (*v).step_y;
			(*v).side = 1;
		}
		if (t->map[(*v).map_y][(*v).map_x] == '1')
			break ;
	}
	if ((*v).side == 0)
		(*v).perp_wall_dist = ((*v).side_dist_x - (*v).delta_dist_x);
	else
		(*v).perp_wall_dist = ((*v).side_dist_y - (*v).delta_dist_y);
}

void	get_texture_index(t_rerenderinit_utils_variables *v)
{
	if ((*v).side == 0)
	{
		if ((*v).ray_dir_x > 0)
			(*v).texture_index = 3;
		else
			(*v).texture_index = 2;
	}
	else
	{
		if ((*v).ray_dir_y > 0)
			(*v).texture_index = 0;
		else
			(*v).texture_index = 1;
	}
}

void	fish_eye_and_texture_x_position(t_rerenderinit_utils_variables *v,
	t_globaldata *t, double *ray_angle)
{
	(*v).corrected_dist = (*v).perp_wall_dist * \
		cos(*ray_angle - t->player.angler);
	(*v).perp_wall_on_screen = (int)(WIN_HEIGHT / (*v).corrected_dist);
	(*v).start_draw = (WIN_HEIGHT / 2) - ((*v).perp_wall_on_screen / 2);
	(*v).end_draw = (WIN_HEIGHT / 2) + ((*v).perp_wall_on_screen / 2);
	if ((*v).start_draw < 0)
		(*v).start_draw = 0;
	if ((*v).end_draw >= WIN_HEIGHT)
		(*v).end_draw = WIN_HEIGHT - 1;
	if ((*v).side == 0)
		(*v).wall_hit_x_in_texture = t->player.py / TILE_SIZE \
		+ (*v).perp_wall_dist * (*v).ray_dir_y;
	else
		(*v).wall_hit_x_in_texture = t->player.px / TILE_SIZE \
		+ (*v).perp_wall_dist * (*v).ray_dir_x;
	(*v).wall_hit_x_in_texture -= floor((*v).wall_hit_x_in_texture);
}

/*
  _rerenderinit util;
*/

void	fetch_walls(t_rerenderinit_utils_variables *v,
	t_globaldata *t, int line_index)
{
	(*v).tex_x = (int)((*v).wall_hit_x_in_texture * \
		t->wrapper[(*v).texture_index].width);
	(*v).texture_step = (double)t->wrapper[(*v).texture_index].height \
		/ (double)(*v).perp_wall_on_screen;
	(*v).tex_y = ((*v).start_draw - WIN_HEIGHT / 2.0 + (*v).perp_wall_on_screen \
		/ 2.0) * (*v).texture_step;
	(*v).tindex = (*v).start_draw - 1;
	while (++((*v).tindex) < (*v).end_draw)
	{
		my_mlx_pixel_put(&t->img, line_index, (*v).tindex,
			get_texture_color(&t->wrapper[(*v).texture_index],
				(*v).tex_x, (int)(*v).tex_y));
		(*v).tex_y += (*v).texture_step;
	}
}

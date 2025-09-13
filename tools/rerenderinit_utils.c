/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rerenderinit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:52:18 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/13 11:15:10 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_texture_color(t_image *texture, int tex_x, int tex_y)
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
	return (color);
}

void	ft_memset(void *addr, char value, int size)
{
	int	index;

	index = -1;
	while (++index < size)
	{
		((char *)addr)[index] = value;
	}
}

/*
  rerenderinit util;
*/

void	rerenderinit_utils(t_globaldata *t, double *ray_angle, int line_index)
{
	t_rerenderinit_utils_variables	v;

	ft_memset(&v, 0, sizeof(v));
	if (*ray_angle > 2 * PI)
		*ray_angle -= 2 * PI;
	if (*ray_angle < 0)
		*ray_angle += 2 * PI;
	v.ray_dir_x = cos(*ray_angle);
	v.ray_dir_y = sin(*ray_angle);
	v.delta_dist_x = fabs(1 / v.ray_dir_x);
	v.delta_dist_y = fabs(1 / v.ray_dir_y);
	v.map_x = (int)(t->player.px / TILE_SIZE);
	v.map_y = (int)(t->player.py / TILE_SIZE);
	calcule_side_dists(&v, t);
	dda_logic(&v, t);
	get_texture_index(&v);
	fish_eye_and_texture_x_position(&v, t, ray_angle);
	fetch_walls(&v, t, line_index);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   releaseinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:03:42 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/13 11:23:09 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_iswall(t_globaldata *t, double currently_x, double currently_y)
{
	return (t->map[(int)(currently_y / TILE_SIZE)]
		[(int)(currently_x / TILE_SIZE)] == '1');
}

int	releaseinit(int key, t_globaldata *t)
{
	if (key >= 0 && key < 75361)
		t->keys[key] = 0;
	return (0);
}

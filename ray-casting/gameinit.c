/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:17:26 by abdael-m          #+#    #+#             */
/*   Updated: 2025/07/30 15:35:30 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	gameinit(char **map, char **textures, int *colors)
{
	t_init	init;

	init.colors = colors;
	init.textures = textures;
	init.map = map;
	init.mlx = mlx_init();
	init.win = mlx_new_window(init.mlx, WIN_WIDTH, WIN_HEIGHT, "...");
	mlx_loop(init.mlx);
}

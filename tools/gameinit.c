/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:41:51 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/03 18:54:07 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
  define globaldata and player, open window, rerend and handle moves;
*/
void	gameinit(char **map, char **textures, int *colors)
{
	t_globaldata	t;

	t.colors = colors;
	t.textures = textures;
	t.map = map;
	t.mlx = mlx_init();
	t.win = mlx_new_window(t.mlx, WIN_WIDTH, WIN_HEIGHT, "...");
	playerinit(&t);
	t.img.ptr = mlx_new_image(t.mlx, WIN_WIDTH, WIN_HEIGHT);
	t.img.data = mlx_get_data_addr(t.img.ptr, &t.img.bpp,
			&t.img.size_line, &t.img.endian);
	mlx_loop_hook(t.mlx, rerenderinit, &t);
	mlx_hook(t.win, 2, 1L << 0, pressinit, &t);
	mlx_hook(t.win, 17, 0L, exitinit, &t);
	mlx_loop(t.mlx);
}

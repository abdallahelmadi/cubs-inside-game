/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:41:51 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/13 11:16:14 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static char	*d(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian)
{
	return (mlx_get_data_addr(img_ptr, bits_per_pixel, size_line, endian));
}

static void	load_wrapper(t_globaldata *t)
{
	t->wrapper[0].ptr = mlx_xpm_file_to_image(t->mlx, t->textures[0],
			&t->wrapper[0].width, &t->wrapper[0].height);
	if (t->wrapper[0].ptr == NULL)
		exitinit(t);
	t->wrapper[0].data = d(t->wrapper[0].ptr, &t->wrapper[0].bpp,
			&t->wrapper[0].size_line, &t->wrapper[0].endian);
	t->wrapper[1].ptr = mlx_xpm_file_to_image(t->mlx, t->textures[1],
			&t->wrapper[1].width, &t->wrapper[1].height);
	if (t->wrapper[1].ptr == NULL)
		exitinit(t);
	t->wrapper[1].data = d(t->wrapper[1].ptr, &t->wrapper[1].bpp,
			&t->wrapper[1].size_line, &t->wrapper[1].endian);
	t->wrapper[2].ptr = mlx_xpm_file_to_image(t->mlx, t->textures[2],
			&t->wrapper[2].width, &t->wrapper[2].height);
	if (t->wrapper[2].ptr == NULL)
		exitinit(t);
	t->wrapper[2].data = d(t->wrapper[2].ptr, &t->wrapper[2].bpp,
			&t->wrapper[2].size_line, &t->wrapper[2].endian);
	t->wrapper[3].ptr = mlx_xpm_file_to_image(t->mlx, t->textures[3],
			&t->wrapper[3].width, &t->wrapper[3].height);
	if (t->wrapper[3].ptr == NULL)
		exitinit(t);
	t->wrapper[3].data = d(t->wrapper[3].ptr, &t->wrapper[3].bpp,
			&t->wrapper[3].size_line, &t->wrapper[3].endian);
}

/*
  define globaldata and player, open window, rerend, textures and handle moves;
*/

void	gameinit(char **map, char **textures, int *colors, t_config *config)
{
	t_globaldata	t;

	t.colors = colors;
	t.textures = textures;
	t.map = map;
	t.config = config;
	t.img.ptr = NULL;
	t.wrapper[0].ptr = NULL;
	t.wrapper[1].ptr = NULL;
	t.wrapper[2].ptr = NULL;
	t.wrapper[3].ptr = NULL;
	t.win = NULL;
	ft_memset(&(t.keys), 0, sizeof(t.keys));
	t.mlx = mlx_init();
	load_wrapper(&t);
	t.win = mlx_new_window(t.mlx, WIN_WIDTH, WIN_HEIGHT, "...");
	playerinit(&t);
	t.img.ptr = mlx_new_image(t.mlx, WIN_WIDTH, WIN_HEIGHT);
	t.img.data = mlx_get_data_addr(t.img.ptr, &t.img.bpp,
			&t.img.size_line, &t.img.endian);
	mlx_loop_hook(t.mlx, rerenderinit, &t);
	mlx_hook(t.win, 2, 1L << 0, pressinit, &t);
	mlx_hook(t.win, 3, 1L << 1, releaseinit, &t);
	mlx_hook(t.win, 17, 0L, exitinit, &t);
	mlx_loop(t.mlx);
}

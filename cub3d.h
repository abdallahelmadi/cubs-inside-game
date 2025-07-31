/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:26:19 by abdael-m          #+#    #+#             */
/*   Updated: 2025/07/31 09:17:31 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define TILE_SIZE 32
# define ROWS 10
# define COLS 15
# define WIN_WIDTH COLS * TILE_SIZE
# define WIN_HEIGHT ROWS * TILE_SIZE
# define FOV 60
# define RES 4
# define NUM_RAYS WIN_WIDTH / RES

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_init
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**textures;
	int			*colors;
	t_player	player;
}	t_init;

void	gameinit(char **map, char **textures, int *colors);\

#endif
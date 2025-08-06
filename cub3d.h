/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:49:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/08/06 11:38:18 by abdael-m         ###   ########.fr       */
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

# define TILE_SIZE 16
# define ROWS 10
# define COLS 15
# define WIN_WIDTH 240
# define WIN_HEIGHT 160

typedef struct s_player
{
	double	px;
	double	py;
	double	angler;
}	t_player;

typedef struct s_globaldata
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**textures;
	int			*colors;
	t_player	player;
}	t_globaldata;

void	gameinit(char **map, char **textures, int *colors);

#endif
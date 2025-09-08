/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:49:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/08 16:52:11 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <strings.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <cub.h>

# define TILE_SIZE 36
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define FOV 1.0471975511965977461542144610932 // (PI / 3) = 30^
# define PI 3.14159265358979323846 // PI
# define PI2 6.28318530717958647692 // PI * 2
# define PID2 1.57079632679489661923 // PI / 2

# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define SPEED 5

typedef struct s_config	t_config;

typedef struct s_get_texture_color_params
{
	int		tindex;
	int		wall_start;
	int		wall_end;
	int		texture_index;
	double	wall_hit_x_in_texture;
}	t_get_texture_color_params;

typedef struct s_player
{
	double	px;
	double	py;
	double	angler;
}	t_player;

typedef struct s_image
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_globaldata
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**textures;
	int			*colors;
	t_player	player;
	t_image		img;
	t_image		wrapper[4];
	t_config	*config;
}	t_globaldata;

void	gameinit(char **map, char **textures, int *colors, t_config *config);
void	playerinit(t_globaldata *t);
int		rerenderinit(t_globaldata *t);
int		exitinit(t_globaldata *t);
int		pressinit(int key, t_globaldata *t);

#endif
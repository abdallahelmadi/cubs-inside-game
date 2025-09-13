/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:49:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/13 11:23:17 by abdael-m         ###   ########.fr       */
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
# include <cub.h>
# include <string.h>

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

# define SPEED 0.66

typedef struct s_config	t_config;

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
	int			keys[75361];
	t_player	player;
	t_image		img;
	t_image		wrapper[4];
	t_config	*config;
}	t_globaldata;

typedef struct s_rerenderinit_utils_variables
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	corrected_dist;
	double	perp_wall_on_screen;
	double	wall_hit_x_in_texture;
	double	texture_step;
	double	tex_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		texture_index;
	int		start_draw;
	int		end_draw;
	int		tex_x;
	int		tindex;
}	t_rerenderinit_utils_variables;

void	gameinit(char **map, char **textures, int *colors, t_config *config);
void	playerinit(t_globaldata *t);
void	rerenderinit_utils(t_globaldata *t, double *ray_angle, int line_index);
int		rerenderinit(t_globaldata *t);
int		exitinit(t_globaldata *t);
int		pressinit(int key, t_globaldata *t);
int		releaseinit(int key, t_globaldata *t);
void	handle_keys(t_globaldata *t);
void	ft_memset(void *addr, char value, int size);
int		ft_iswall(t_globaldata *t, double currently_x, double currently_y);

void	fetch_walls(t_rerenderinit_utils_variables *v,
			t_globaldata *t, int line_index);
void	fish_eye_and_texture_x_position(t_rerenderinit_utils_variables *v,
			t_globaldata *t, double *ray_angle);
void	get_texture_index(t_rerenderinit_utils_variables *v);
void	dda_logic(t_rerenderinit_utils_variables *v, t_globaldata *t);
void	calcule_side_dists(t_rerenderinit_utils_variables *v,
			t_globaldata *t);
int		get_texture_color(t_image *texture, int tex_x, int tex_y);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

#endif
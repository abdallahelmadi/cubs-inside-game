/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:49:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/08/09 10:42:07 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// the define of function we will use from mlx, math, system call ...
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define TILE_SIZE 30 // size of squares
# define WIN_WIDTH 1280 // total width for window
# define WIN_HEIGHT 720 // total height for window
// 60 in angler, the view margin of player, result of (PI / 3)
# define FOV 1.0471975511965977461542144610932
/**/
# define PI 3.14159265358979323846 // value of PI
# define PI2 6.28318530717958647692 // value of PI * 2
# define PID2 1.57079632679489661923 // value of PI / 2

/*
  datatype of player, include:
  position in x and y
  and the angler of view, in first defined by the player by name of player (SENW)
*/
typedef struct s_player
{
	double	px;
	double	py;
	double	angler;
}	t_player;

/*
  some data to buffer screen image each rerender
*/
typedef struct s_image
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_image;

/*
  the global data i need to pass to function to access to player, map ... details
*/
typedef struct s_globaldata
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**textures;
	int			*colors;
	t_player	player;
	t_image		img;
}	t_globaldata;

// the function linking between parsing and ray-casting
void	gameinit(char **map, char **textures, int *colors);

// declare user data using the map of argument
void	playerinit(t_globaldata *t);

// check if c include in s
int		ft_charcmp(char c, char *s);

// the function how's rerender each time to make animation
int		rerenderinit(t_globaldata *t);

// draw 2D wall
void	ft_drawwall(int start_x, int start_y, t_globaldata *t, int color);

// draw player position
void	ft_drawplayer(t_globaldata *t);

// draw rays
void	ft_drawrays(t_globaldata *t);

// check if the position is inside wall
int		ft_iswall(t_globaldata *t, double currently_x, double currently_y);

// check play if he is colliding depending in the FOV
int		is_player_colliding(t_globaldata *t,
			double currently_x, double currently_y);

// handle the key press
int		handle_press(int key, t_globaldata *t);

// helper for handle_press function
void	ft_setplayer(double new_x, double new_y, t_globaldata *t);

// helper for handle_press function
void	ft_setfov(double angler, t_globaldata *t);

// exit and free the resources
int		exit_free(t_globaldata *t);

// helper function to set a pixel in the image buffer
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

// draw background
void	ft_drawbackground(t_globaldata *t);

// draw rays as 3D
void	ft_drwaray3d(t_globaldata *t, int length, int index);

#endif
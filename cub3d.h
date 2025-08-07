/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:49:04 by abdael-m          #+#    #+#             */
/*   Updated: 2025/08/07 12:20:38 by abdael-m         ###   ########.fr       */
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
# define ROWS 10 // the rows of window
# define COLS 15 // the coloums of window
# define WIN_WIDTH 450 // total width for window
# define WIN_HEIGHT 300 // total height for window
// 60 in angler, the view margin of player, result of (PI / 3)
# define FOV 1.0471975511965977461542144610932
/**/
# define NUM_RAYS 120 // number of rays will be fetched
# define PI 3.14159265358979323846 // value of PI
# define PI2 6.28318530717958647692 // value of PI * 2

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
}	t_globaldata;

// the function linking between parsing and ray-casting
void	gameinit(char **map, char **textures, int *colors);

#endif
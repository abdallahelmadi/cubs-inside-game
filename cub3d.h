/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:26:19 by abdael-m          #+#    #+#             */
/*   Updated: 2025/07/30 16:09:52 by abdael-m         ###   ########.fr       */
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

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct s_player
{
	int	x;
	int	y;
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

void	gameinit(char **map, char **textures, int *colors);
void	fetcher(t_init *g);
int		keypress(int key, void *g);

#endif
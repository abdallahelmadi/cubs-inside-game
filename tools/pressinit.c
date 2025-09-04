/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:20:28 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/04 15:44:58 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	ft_iswall(t_globaldata *t, double currently_x, double currently_y)
{
	return (t->map[(int)(currently_y / TILE_SIZE)]
		[(int)(currently_x / TILE_SIZE)] == '1');
}

static int	is_player_colliding(t_globaldata *t,
	double currently_x, double currently_y)
{
	double	buffer;

	buffer = 1;
	return (ft_iswall(t, currently_x + buffer, currently_y + buffer)
		|| ft_iswall(t, currently_x - buffer, currently_y + buffer)
		|| ft_iswall(t, currently_x + buffer, currently_y - buffer)
		|| ft_iswall(t, currently_x - buffer, currently_y - buffer));
}

static void	setposition(double new_x, double new_y, t_globaldata *t)
{
	if (!is_player_colliding(t, new_x, new_y))
	{
		t->player.px = new_x;
		t->player.py = new_y;
	}
}

static void	setfov(double angler, t_globaldata *t)
{
	t->player.angler = angler;
	if (t->player.angler < 0)
		t->player.angler += 2 * PI;
	else if (t->player.angler > 2 * PI)
		t->player.angler -= 2 * PI;
}

/*
  handle player press;
*/

int	pressinit(int key, t_globaldata *t)
{
	double	speed;

	speed = 4;
	if (key == 119)
		setposition(t->player.px + cos(t->player.angler) * speed,
			t->player.py + sin(t->player.angler) * speed, t);
	if (key == 115)
		setposition(t->player.px - cos(t->player.angler) * speed,
			t->player.py - sin(t->player.angler) * speed, t);
	if (key == 97)
		setposition(t->player.px + cos(t->player.angler - PID2) * speed,
			t->player.py + sin(t->player.angler - PID2) * speed, t);
	if (key == 100)
		setposition(t->player.px + cos(t->player.angler + PID2) * speed,
			t->player.py + sin(t->player.angler + PID2) * speed, t);
	if (key == 65361)
		setfov(t->player.angler - PI / 12, t);
	if (key == 65363)
		setfov(t->player.angler + PI / 12, t);
	if (key == 65307)
		exitinit(t);
	return (0);
}

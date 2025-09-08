/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:28:11 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/08 11:00:00 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
  free resources and get out cleam;
*/
int	exitinit(t_globaldata *t)
{
	mlx_destroy_image(t->mlx, t->img.ptr);
	mlx_destroy_image(t->mlx, t->wrapper[0].ptr);
	mlx_destroy_image(t->mlx, t->wrapper[1].ptr);
	mlx_destroy_image(t->mlx, t->wrapper[2].ptr);
	mlx_destroy_image(t->mlx, t->wrapper[3].ptr);
	mlx_destroy_window(t->mlx, t->win);
	mlx_destroy_display(t->mlx);
	free(t->mlx);
	exit(0);
	return (0);
}

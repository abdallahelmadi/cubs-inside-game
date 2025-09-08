/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:28:11 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/08 17:26:21 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
  free resources and get out cleam;
*/
int	exitinit(t_globaldata *t)
{
	int (status);
	status = 0;
	if (!t->img.ptr || !t->wrapper[0].ptr || !t->wrapper[1].ptr
		|| !t->wrapper[2].ptr || !t->wrapper[3].ptr)
	{
		write(2, "Error: invalid textures\n", 25);
		status = 1;
	}
	if (t->img.ptr)
		mlx_destroy_image(t->mlx, t->img.ptr);
	if (t->wrapper[0].ptr)
		mlx_destroy_image(t->mlx, t->wrapper[0].ptr);
	if (t->wrapper[1].ptr)
		mlx_destroy_image(t->mlx, t->wrapper[1].ptr);
	if (t->wrapper[2].ptr)
		mlx_destroy_image(t->mlx, t->wrapper[2].ptr);
	if (t->wrapper[3].ptr)
		mlx_destroy_image(t->mlx, t->wrapper[3].ptr);
	if (t->win)
		mlx_destroy_window(t->mlx, t->win);
	mlx_destroy_display(t->mlx);
	free(t->mlx);
	free_config(t->config);
	exit(status);
	return (0);
}

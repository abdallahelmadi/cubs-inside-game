/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:58:50 by abdael-m          #+#    #+#             */
/*   Updated: 2025/07/30 16:07:51 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	keypress(int key, void *g)
{
	t_init *init = (t_init *)g;

	if (key == 97)
		init->player.x -= 1;
	else if (key == 115)
		init->player.y += 1;
	else if (key == 100)
		init->player.x += 1;
	else if (key == 119)
		init->player.y -= 1;

	printf("x: %d, y: %d\n", init->player.x, init->player.y);
	return (0);
}

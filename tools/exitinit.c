/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdael-m <abdael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 09:28:11 by abdael-m          #+#    #+#             */
/*   Updated: 2025/09/04 10:20:50 by abdael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
  free resources and get out cleam;
*/
int	exitinit(t_globaldata *t)
{
	(void)t;
	printf("\033[0;33mDON'T FORGET TO FREE\n");
	exit(0);
	return (0);
}

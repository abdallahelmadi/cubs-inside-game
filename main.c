/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:05:27 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/12 16:05:27 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initialize_config(t_config *config)
{
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->floor_color_r = -1;
	config->floor_color_g = -1;
	config->floor_color_b = -1;
	config->floor_color = -1;
	config->ceiling_color_r = -1;
	config->ceiling_color_g = -1;
	config->ceiling_color_b = -1;
	config->ceiling_color = -1;
	config->map = NULL;
	config->map_width = 0;
	config->map_height = 0;
}

int	create_check_all(t_config *config, char *filename)
{
	if (create_map(filename, config))
	{
		return (1);
	}
	if (once_player(config->map) != 0
		|| check_walls_top_bottom(config->map, config->map_height) != 0
		|| check_walls_left_right(config->map, config->map_height) != 0
		|| check_invalid_spaces(config->map, config->map_height) != 0
		|| check_valid_characters(config->map, config->map_height) != 0)
	{
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	*config;

	if (argc != 2)
		return (write(2, "Error: Incorrect number of arguments\n", 38), 1);
	if (check_extension(argv[1]) == 0)
		return (write(2, "Error: Invalid file extension. Expected .cub\n",
				46), 1);
	config = malloc(sizeof(t_config));
	if (!config)
		return (write(2, "Error: Memory allocation failed for config\n",
				44), 1);
	initialize_config(config);
	if (create_check_all(config, argv[1]) != 0)
		return (free_config(config), 1);
	gameinit(config->map,
		(char *[]){
		config->no_texture,
		config->so_texture,
		config->we_texture,
		config->ea_texture,
		NULL
	},
		(int []){config->floor_color, config->ceiling_color},
		config);
	return (0);
}

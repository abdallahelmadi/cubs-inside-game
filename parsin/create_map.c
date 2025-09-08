/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:33:33 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/20 17:33:33 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	append_map(char ***map, char *line, int *map_height)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (*map_height + 2));
	if (!new_map)
	{
		write(2, "Error: Memory allocation failed for map\n", 40);
		exit(1);
	}
	i = 0;
	while (i < *map_height)
	{
		new_map[i] = (*map)[i];
		i++;
	}
	new_map[i] = my_strdup(line);
	new_map[i + 1] = NULL;
	free(*map);
	*map = new_map;
	(*map_height)++;
}

static int	handle_config_sec(t_config *config, char *line, int *in_map_section)
{
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
	{
		if (assign_texture(config, line) != 0)
			return (1);
	}
	else if (line[0] == 'F' || line[0] == 'C')
	{
		if (assign_colors(config, line) != 0)
			return (1);
	}
	else if (all_six_config(config) && (line[0] == '1' || line[0] == ' '))
	{
		*in_map_section = 1;
		append_map(&(config->map), line, &(config->map_height));
		if (ft_strlen(line) > config->map_width)
			config->map_width = ft_strlen(line);
	}
	else
	{
		write(2, "Error: Invalid line in configuration\n", 37);
		return (1);
	}
	return (0);
}

static int	loop_lines(int fd, t_config *config, int *in_map_section)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (skip_empty_lines(fd, &line))
		{
			if (!line)
				break ;
		}
		if (handle_config_sec(config, line, in_map_section) != 0)
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	create_map(char *filename, t_config *config)
{
	int		fd;
	int		in_map_section;

	in_map_section = 0;
	fd = open_file(filename);
	if (fd < 0)
		return (1);
	if (loop_lines(fd, config, &in_map_section) != 0)
		return (1);
	if (!in_map_section)
		return (write(2, "Error: No map found in the file\n", 32), 1);
	return (0);
}

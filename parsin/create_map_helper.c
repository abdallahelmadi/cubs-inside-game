/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:17:16 by bnafiai           #+#    #+#             */
/*   Updated: 2025/08/02 16:17:16 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: opening file\n", 20);
		return (-1);
	}
	return (fd);
}

int	skip_empty_lines(int fd, char **line)
{
	while (*line && is_line_empty(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	return (*line == NULL);
}

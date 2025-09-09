/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_col_tex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:42:05 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/20 16:42:05 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	validate_texture(char **split_texture)
{
	if (array_size(split_texture) > 1)
	{
		if (array_size(split_texture) == 2)
		{
			if (split_texture[1][0] == '\n' || split_texture[1][0] == '\r')
				return (0);
			write(2, "Error: Invalid texture format (Extra args)\n", 43);
			return (1);
		}
		write(2, "Error: Invalid texture format (Extra args)\n", 43);
		return (1);
	}
	return (0);
}

int	skip_spaces(const char *line, int index)
{
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	return (index);
}

int	valid_tex(char *line, char **texture)
{
	int		i;
	char	**split;

	i = skip_spaces(line, 2);
	split = utils_split(line + i, ' ');
	if (validate_texture(split) != 0)
	{
		free_split(split);
		return (1);
	}
	split[0][ft_strlen(split[0]) - 1] = '\0';
	*texture = my_strdup(split[0]);
	free_split(split);
	return (0);
}

int	assign_texture(t_config *config, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (valid_tex(line, &config->no_texture) != 0)
			return (1);
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (valid_tex(line, &config->so_texture) != 0)
			return (1);
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (valid_tex(line, &config->we_texture) != 0)
			return (1);
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (valid_tex(line, &config->ea_texture) != 0)
			return (1);
	}
	else
		return (write(2, "Error: Invalid texture line\n", 28), 1);
	return (0);
}

int	validate_colors(char **colors)
{
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		write(2, "Error: Invalid color format\n", 28);
		return (1);
	}
	if (colors[0][0] == ' ' || colors[1][0] == ' ' || colors[2][0] == ' '
		|| colors[0][0] == '\0' || colors[1][0] == '\0' || colors[2][0] == '\0'
		|| colors[0][0] == '\n' || colors[1][0] == '\n' || colors[2][0] == '\n')
	{
		write(2, "Error: Invalid color format\n", 28);
		return (1);
	}
	if (check_valid_colors(colors) != 0)
		return (1);
	if (check_range_rgb(ft_atoi(colors[0])) != 0
		|| check_range_rgb(ft_atoi(colors[1])) != 0
		|| check_range_rgb(ft_atoi(colors[2])) != 0)
	{
		return (1);
	}
	return (0);
}

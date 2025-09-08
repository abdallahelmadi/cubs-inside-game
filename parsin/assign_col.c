/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_col.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:50:13 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/30 18:50:13 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	colors_f(t_config *config, char *line)
{
	int		i;
	char	**split_colors;

	if (check_for_commas(line) != 2)
	{
		write(2, "Error : Invalid color line\n", 27);
		return (1);
	}
	i = skip_spaces(line, 2);
	split_colors = utils_split(line + i, ',');
	if (validate_colors(split_colors) != 0)
	{
		free_split(split_colors);
		return (1);
	}
	config->floor_color_r = ft_atoi(split_colors[0]);
	config->floor_color_g = ft_atoi(split_colors[1]);
	config->floor_color_b = ft_atoi(split_colors[2]);
	config->floor_color = create_rgb(config->floor_color_r,
			config->floor_color_g, config->floor_color_b);
	free_split(split_colors);
	return (0);
}

int	colors_c(t_config *config, char *line)
{
	int		i;
	char	**split_ceiling_colors;

	if (check_for_commas(line) != 2)
	{
		write(2, "Error : Invalid color line\n", 27);
		return (1);
	}
	i = skip_spaces(line, 2);
	split_ceiling_colors = utils_split(line + i, ',');
	if (validate_colors(split_ceiling_colors) != 0)
	{
		free_split(split_ceiling_colors);
		return (1);
	}
	config->ceiling_color_r = ft_atoi(split_ceiling_colors[0]);
	config->ceiling_color_g = ft_atoi(split_ceiling_colors[1]);
	config->ceiling_color_b = ft_atoi(split_ceiling_colors[2]);
	config->ceiling_color = create_rgb(config->ceiling_color_r,
			config->ceiling_color_g, config->ceiling_color_b);
	free_split(split_ceiling_colors);
	return (0);
}

int	assign_colors(t_config *config, char *line)
{
	if (line[0] == 'F')
	{
		if (colors_f(config, line) != 0)
			return (1);
	}
	else if (line[0] == 'C')
	{
		if (colors_c(config, line) != 0)
			return (1);
	}
	else
	{
		write(2, "Error : Invalid color line\n", 27);
		return (1);
	}
	return (0);
}

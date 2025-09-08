/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:54 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/12 16:07:54 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <cub3d.h>

# define BUFFER_SIZE 1

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color_r;
	int		floor_color_g;
	int		floor_color_b;
	int		floor_color;
	int		ceiling_color_r;
	int		ceiling_color_g;
	int		ceiling_color_b;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
}	t_config;
//get_next_line part
char	*get_next_line(int fd);
char	*my_strjoin(char *s1, char *s2);
char	*my_strdup(char *s);
char	*my_strchar(char *str, int c);
size_t	my_strlen(char *s);
//helper functions
int		ft_strlen(const char *str);
int		ft_atoi(char *str);
int		check_range_rgb(int color);
void	free_split(char **split);
int		is_line_empty(char *line);
char	**utils_split(const char *string, char c);
int		all_six_config(t_config *config);
int		check_valid_colors(char **colors);
int		array_size(char **arr);
void	free_config(t_config *config);
int		create_rgb(int r, int g, int b);
//extension check
int		check_extension(char *filename);
//map check
int		once_player(char **map);
int		check_walls_top_bottom(char **map, int map_height);
int		check_walls_left_right(char **map, int map_height);
int		check_invalid_spaces(char **map, int map_height);
int		check_valid_characters(char **map, int map_height);
//assign colors and textures
int		skip_spaces(const char *line, int index);
int		check_for_commas(char *str);
int		check_valid_colors(char **colors);
int		validate_colors(char **colors);
int		assign_texture(t_config *config, char *line);
int		assign_colors(t_config *config, char *line);
//for rgb colors
int		create_rgb(int r, int g, int b);
//map creation
int		open_file(char *filename);
int		skip_empty_lines(int fd, char **line);
int		create_map(char *filename, t_config *config);
//check walls helpers
int		check_right_walls(char **map, int len, int i);
int		check_left_walls(char **map, int len, int i);
int		check_bottom_walls(char **map, int map_height);
int		check_top_walls(char **map, int map_height);
#endif

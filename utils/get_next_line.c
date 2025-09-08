/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:04:04 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/12 18:04:04 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	*read_fd(int fd, char *stored)
{
	char	*str;
	ssize_t	sread;
	char	*new_one;

	str = malloc((size_t)BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	sread = read(fd, str, BUFFER_SIZE);
	if (sread <= 0)
	{
		free(str);
		return (NULL);
	}
	str[sread] = '\0';
	new_one = my_strjoin(stored, str);
	free(stored);
	free(str);
	return (new_one);
}

static char	*get_line(char *stored)
{
	char	*newline_ptr;
	size_t	index;
	char	*line;
	size_t	i;

	if (!stored || !*stored)
		return (NULL);
	newline_ptr = my_strchar(stored, '\n');
	if (!newline_ptr)
		index = my_strlen(stored);
	else
		index = newline_ptr - stored + 1;
	line = malloc(index + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < index)
	{
		line[i] = stored[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_stored(char *stored)
{
	char	*newline;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	while (stored[i] != '\0' && stored[i] != '\n')
		i++;
	len = my_strlen(stored) - i + 1;
	newline = malloc(len + 1);
	if (!newline)
		return (NULL);
	j = 0;
	if (stored[i] == '\n')
		i++;
	while (stored[i] != '\0')
	{
		newline[j] = stored[i];
		i++;
		j++;
	}
	newline[j] = '\0';
	free(stored);
	return (newline);
}

char	*get_next_line(int fd)
{
	static char		*stored;
	char			*line;
	char			*new_stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!my_strchar(stored, '\n'))
	{
		new_stored = read_fd(fd, stored);
		if (!new_stored)
			break ;
		stored = new_stored;
	}
	line = get_line(stored);
	if (!line)
		return (NULL);
	stored = update_stored(stored);
	if (stored && *stored == '\0')
	{
		free(stored);
		stored = NULL;
	}
	return (line);
}

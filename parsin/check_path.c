/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnafiai <bnafiai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:30:09 by bnafiai           #+#    #+#             */
/*   Updated: 2025/07/12 16:30:09 by bnafiai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_extension(char *filename)
{
	int	length_filename;

	length_filename = ft_strlen(filename);
	if (length_filename < 5)
		return (0);
	if (filename[length_filename - 1] == 'b'
		&& filename[length_filename - 2] == 'u'
		&& filename[length_filename - 3] == 'c'
		&& filename[length_filename - 4] == '.')
	{
		return (1);
	}
	return (0);
}

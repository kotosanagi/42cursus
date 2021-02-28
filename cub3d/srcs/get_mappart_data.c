/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mappart_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:30:34 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/27 22:13:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_mappart_data(int fd, char **line, t_info *info)
{
	int	ret;
	int	start;
	int	end;
	int	i;

	ret = 1;
	start = 0;
	end = 0;
	i = 0;
	while (ret > 0 && i < MAP_HEIGHT)
	{
		ret = get_next_line(fd, line);
		if ((end == 1) && (ft_strncmp(*line, "", 1) != 0))
			error_free_line("No allowed separated map\n", info, *line, fd);
		if ((start == 1) && (ft_strncmp(*line, "", 1) == 0))
			end = 1;
		if ((start == 0) && (ft_strncmp(*line, "", 1) != 0))
			start = 1;
		if ((start == 1) && (end == 0))
		{
			if (ft_strlen(*line) > MAP_WIDTH - 1)
				error_free_line("width of map is too much\n", info, *line, fd);
			info->map[i++] = ft_strdup(*line);
		}
		if (ret == 0)
			end = 1;
		safe_free(*line);
	}
	if (info->map[0] == NULL)
		error_fd_close("doesn't find map\n", info, fd);
	if (i >= MAP_HEIGHT)
		error_fd_close("height of map is too much\n", info, fd);
	info->map_h = i;
}
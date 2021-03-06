/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mappart_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:30:34 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 20:48:42 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	reverse_map(char **map, int map_h)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < map_h / 2)
	{
		tmp = map[i];
		map[i] = map[map_h - i - 1];
		map[map_h - i - 1] = tmp;
		i++;
	}
}

static void	inspect_mapdata(int fd, char **line, t_info *info, t_mapdata *md)
{
	md->ret = get_next_line(fd, line);
	if ((md->end == 1) && (ft_strncmp(*line, "", 1) != 0))
		error_free_line("No allowed separated map\n", info, *line, fd);
	if ((md->start == 1) && (ft_strncmp(*line, "", 1) == 0))
		md->end = 1;
	if ((md->start == 0) && (ft_strncmp(*line, "", 1) != 0))
		md->start = 1;
	if ((md->start == 1) && (md->end == 0))
	{
		if (ft_strlen(*line) > MAP_WIDTH - 1)
			error_free_line("width of map is too much\n", info, *line, fd);
		info->map[md->i] = ft_strdup(*line);
		md->i += 1;
	}
	if (md->ret == 0)
		md->end = 1;
}

void		get_mappart_data(int fd, char **line, t_info *info)
{
	t_mapdata	md;

	md.ret = 1;
	md.start = 0;
	md.end = 0;
	md.i = 0;
	while (md.ret > 0 && md.i < MAP_HEIGHT)
	{
		inspect_mapdata(fd, line, info, &md);
		safe_free(*line);
	}
	if (info->map[0] == NULL)
		error_fd_close("doesn't find map\n", info, fd);
	if (md.i >= MAP_HEIGHT)
		error_fd_close("height of map is too much\n", info, fd);
	info->map_h = md.i;
	reverse_map(info->map, info->map_h);
}

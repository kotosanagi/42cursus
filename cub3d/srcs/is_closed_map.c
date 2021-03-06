/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:00:26 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 20:34:27 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	flood_fill(char tmp_map[MAP_HEIGHT][MAP_WIDTH],
int y, int x, int *close)
{
	if (y == 0 || x == 0 ||
		y >= MAP_HEIGHT - 2 || x >= MAP_WIDTH - 2 ||
		tmp_map[y][x] == '\0' || tmp_map[y] == NULL)
	{
		*close = 0;
		return ;
	}
	tmp_map[y][x] = '#';
	if (tmp_map[y - 1][x] != '1' && tmp_map[y - 1][x] != '#')
		flood_fill(tmp_map, y - 1, x, close);
	if (tmp_map[y + 1][x] != '1' && tmp_map[y + 1][x] != '#')
		flood_fill(tmp_map, y + 1, x, close);
	if (tmp_map[y][x - 1] != '1' && tmp_map[y][x - 1] != '#')
		flood_fill(tmp_map, y, x - 1, close);
	if (tmp_map[y][x + 1] != '1' && tmp_map[y][x + 1] != '#')
		flood_fill(tmp_map, y, x + 1, close);
	return ;
}

void		is_closed_map(t_info *info)
{
	char	tmp_map[MAP_HEIGHT][MAP_WIDTH];
	int		y;
	int		x;
	int		close;

	y = 0;
	while (y < info->map_h)
	{
		x = 0;
		while (info->map[y][x] != '\0' && x < MAP_WIDTH)
		{
			if (info->map[y][x] == '1')
				tmp_map[y][x] = '1';
			else if (ft_strchr("EWSN", info->map[y][x]))
				tmp_map[y][x] = 'p';
			else
				tmp_map[y][x] = '0';
			x++;
		}
		tmp_map[y++][x] = '\0';
	}
	close = 1;
	flood_fill(tmp_map, (int)info->pos_y, (int)info->pos_x, &close);
	if (close == 0)
		error_free_exit("it's not closed map\n", info);
}

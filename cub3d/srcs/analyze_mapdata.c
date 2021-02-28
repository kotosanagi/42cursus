/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_mapdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:52:51 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/28 18:19:28 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player2(char c, t_info *info)
{
	if (c == 'S')
	{
		info->dir_x = 1.0;
		info->dir_y = 0.0;
		info->plane_x = 0.0;
		info->plane_y = -0.66;
	}
	else if (c == 'N')
	{
		info->dir_x = -1.0;
		info->dir_y = 0.0;
		info->plane_x = 0.0;
		info->plane_y = 0.66;
	}
	else
		error_free_exit("set player error\n", info);
}

void	set_player(char c, t_info *info, int y, int x)
{
	if (info->pos_x != -2.0)
		error_free_exit("one player only allowed\n", info);//////
	info->pos_x = (double)x + 0.5;
	info->pos_y = (double)y + 0.5;
	if (c == 'E')
	{
		info->dir_x = 0.0;
		info->dir_y = 1.0;
		info->plane_x = 0.66;
		info->plane_y = 0.0;
	}
	else if (c == 'W')
	{
		info->dir_x = 0.0;
		info->dir_y = -1.0;
		info->plane_x = -0.66;
		info->plane_y = 0.0;
	}
	else
		set_player2(c, info);
}

void	analyze_mapdata(t_info *info)
{
	// what do I want do?
	// 	*to get pos_x/y
	// 	*to get dir_x/y
	// 	*to get plane_x/y
	//		->only one E/W/S/N is arrowed

	// 	*is valid map (flood fill)
	// 	*count sprites
	// 	info->map to info->world_map
	int y;
	int x;

	y = 0;
	while (y < info->map_h)
	{
		x = 0;
		while (info->map[y][x] != '\0')
		{
			if (info->map[y][x] == '1')
				info->world_map[y][x] = 1;
			else if (info->map[y][x] == '2')
				info->num_sprite++;
			else if (ft_strchr("WESN", info->map[y][x]))
				set_player(info->map[y][x], info, y, x);//if double player is here, do exit
			else if (info->map[y][x] == '0' || info->map[y][x] == ' ')
				;
			else
				error_free_exit("invalid character in the map\n", info);
			x++;
		}
		y++;
	}
printf("no dust in the map\n");
	is_closed_map(info);
}
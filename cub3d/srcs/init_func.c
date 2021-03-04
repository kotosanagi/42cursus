/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:38:45 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/04 06:20:54 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_info(t_info *info)
{
	int i;
	int j;

// read from mapfiles (which mean these are need to modify when read mapfile correctly//
	info->r_width = -1;
	info->r_height = -1;
	info->east_path = NULL;
	info->west_path = NULL;
	info->south_path = NULL;
	info->north_path = NULL;
	info->sprite_path = NULL;

	info->pos_x = -2.0;
	info->pos_y = -2.0;
	info->dir_x = -2.0;
	info->dir_y = -2.0;
	info->plane_x = -2.0;
	info->plane_y = -2.0;

	info->floor_red = -1;
	info->floor_green = -1;
	info->floor_blue = -1;
	info->ceiling_red = -1;
	info->ceiling_green = -1;
	info->ceiling_blue = -1;

	info->floor_color = 0;
	info->ceiling_color = 0;
	info->num_sprite = 0;

// default //
	i = 0;
	while (i < MAP_HEIGHT)
		info->map[i++] = NULL;

	info->save_flg = 0;
	info->key_w = 0;
	info->key_s = 0;
	info->key_d = 0;
	info->key_a = 0;
	info->key_ar_r = 0;
	info->key_ar_l = 0;
	info->key_ar_u = 0;
	info->key_ar_d = 0;
	info->key_esc = 0;
	info->move_speed = 0.008;
	info->rot_speed = 0.006;
	info->map_h = 0;

	info->sp = NULL;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
			info->world_map[i][j++] = 0;
		i++;
	}

	info->sprite_order = NULL;
	info->sprite_distance = NULL;
	info->buf_malloc_flg = 0;

	info->tex[0].w = 0;
	i = 0;
	while (i < 5)
		info->tex[i++].addr = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_wall2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:48:45 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 15:57:47 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	choose_texture(t_raycasting *rc, t_info *info)
{
	if (rc->side == EW)
	{
		if (rc->map_x < info->pos_x)
			rc->tex_num = WEST_TEXTURE;
		else
			rc->tex_num = EAST_TEXTURE;
	}
	else
	{
		if (rc->map_y < info->pos_y)
			rc->tex_num = SOUTH_TEXTURE;
		else
			rc->tex_num = NORTH_TEXTURE;
	}
}

void	get_wall_tex_x(t_raycasting *rc, t_info *info)
{
	if (rc->side == EW)
		rc->wall_x = info->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = info->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_x = (int)(rc->wall_x * (double)TEX_WIDTH);
	if (rc->side == EW && rc->ray_dir_x > 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	if (rc->side == NS && rc->ray_dir_y < 0)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
}

void	store_wall_tex(t_raycasting *rc, t_info *info)
{
	rc->step = 1.0 * TEX_HEIGHT / rc->line_height;
	rc->tex_pos = (rc->draw_start - info->r_height
	/ 2 + rc->line_height / 2) * rc->step;
	rc->y = rc->draw_start;
	while (rc->y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos & (TEX_HEIGHT - 1);
		rc->tex_pos += rc->step;
		rc->color = info->tex[rc->tex_num].addr[TEX_HEIGHT
		* rc->tex_y + rc->tex_x];
		info->buf[rc->y][rc->x] = rc->color;
		rc->y += 1;
	}
}

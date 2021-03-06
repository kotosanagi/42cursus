/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:54:37 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 15:58:31 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calc_delta_dist(t_raycasting *rc, t_info *info)
{
	rc->camera_x = 2 * rc->x / (double)info->r_width - 1;
	rc->ray_dir_x = info->dir_x + info->plane_x * rc->camera_x;
	rc->ray_dir_y = info->dir_y + info->plane_y * rc->camera_x;
	rc->map_x = (int)info->pos_x;
	rc->map_y = (int)info->pos_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
}

static void	calc_side_dist(t_raycasting *rc, t_info *info)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (info->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - info->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (info->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - info->pos_y) * rc->delta_dist_y;
	}
}

static void	get_hit_wall_info(t_raycasting *rc, t_info *info)
{
	rc->hit = 0;
	while (!rc->hit)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = EW;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = NS;
		}
		if (info->world_map[rc->map_x][rc->map_y] == 1)
			rc->hit = 1;
	}
}

static void	get_wall_size(t_raycasting *rc, t_info *info)
{
	if (rc->side == EW)
		rc->perp_wall_dist = (rc->map_x - info->pos_x +
		(1 - rc->step_x) / 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - info->pos_y +
		(1 - rc->step_y) / 2) / rc->ray_dir_y;
	rc->line_height = (int)(info->r_height / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + info->r_height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + info->r_height / 2;
	if (rc->draw_end > info->r_height)
		rc->draw_end = info->r_height - 1;
}

void		store_wall(t_raycasting *rc, t_info *info)
{
	rc->x = 0;
	while (rc->x < info->r_width)
	{
		calc_delta_dist(rc, info);
		calc_side_dist(rc, info);
		get_hit_wall_info(rc, info);
		get_wall_size(rc, info);
		choose_texture(rc, info);
		get_wall_tex_x(rc, info);
		store_wall_tex(rc, info);
		info->z_buffer[rc->x] = rc->perp_wall_dist;
		rc->x += 1;
	}
}

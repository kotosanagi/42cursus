/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 07:22:12 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 18:35:00 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	key_update_arrow_l(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	if (info->key_ar_l)
	{
		old_dir_x = info->dir_x;
		info->dir_x = info->dir_x * cos(info->rot_speed) - info->dir_y
		* sin(info->rot_speed);
		info->dir_y = old_dir_x * sin(info->rot_speed) + info->dir_y
		* cos(info->rot_speed);
		old_plane_x = info->plane_x;
		info->plane_x = info->plane_x * cos(info->rot_speed)
		- info->plane_y * sin(info->rot_speed);
		info->plane_y = old_plane_x * sin(info->rot_speed)
		+ info->plane_y * cos(info->rot_speed);
	}
}

static void	key_update_arrow_r(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	if (info->key_ar_r)
	{
		old_dir_x = info->dir_x;
		info->dir_x = info->dir_x * cos(-info->rot_speed) - info->dir_y
		* sin(-info->rot_speed);
		info->dir_y = old_dir_x * sin(-info->rot_speed) + info->dir_y
		* cos(-info->rot_speed);
		old_plane_x = info->plane_x;
		info->plane_x = info->plane_x * cos(-info->rot_speed)
		- info->plane_y * sin(-info->rot_speed);
		info->plane_y = old_plane_x * sin(-info->rot_speed)
		+ info->plane_y * cos(-info->rot_speed);
	}
	key_update_arrow_l(info);
}

static void	key_update_da(t_info *info)
{
	if (info->key_d)
	{
		if (!info->world_map[(int)(info->pos_x + info->plane_x
		* info->move_speed)][(int)(info->pos_y)])
			info->pos_x += info->plane_x * info->move_speed;
		if (!info->world_map[(int)(info->pos_x)][(int)(info->pos_y
		+ info->plane_y * info->move_speed)])
			info->pos_y += info->plane_y * info->move_speed;
	}
	if (info->key_a)
	{
		if (!info->world_map[(int)(info->pos_x - info->plane_x
		* info->move_speed)][(int)(info->pos_y)])
			info->pos_x -= info->plane_x * info->move_speed;
		if (!info->world_map[(int)(info->pos_x)][(int)(info->pos_y
		- info->plane_y * info->move_speed)])
			info->pos_y -= info->plane_y * info->move_speed;
	}
	key_update_arrow_r(info);
}

static void	key_update_ws(t_info *info)
{
	if (info->key_w)
	{
		if (!info->world_map[(int)(info->pos_x + info->dir_x
		* info->move_speed)][(int)(info->pos_y)])
			info->pos_x += info->dir_x * info->move_speed;
		if (!info->world_map[(int)(info->pos_x)][(int)(info->pos_y
		+ info->dir_y * info->move_speed)])
			info->pos_y += info->dir_y * info->move_speed;
	}
	if (info->key_s)
	{
		if (!info->world_map[(int)(info->pos_x - info->dir_x
		* info->move_speed)][(int)(info->pos_y)])
			info->pos_x -= info->dir_x * info->move_speed;
		if (!info->world_map[(int)(info->pos_x)][(int)(info->pos_y
		- info->dir_y * info->move_speed)])
			info->pos_y -= info->dir_y * info->move_speed;
	}
	key_update_da(info);
}

void		key_update(t_info *info)
{
	if (info->key_esc)
		exit_successful(info);
	if (info->key_ar_u && info->key_ar_d)
	{
		info->move_speed = 0.008;
		info->rot_speed = 0.006;
	}
	else if (info->key_ar_u && !(info->key_ar_d))
	{
		info->move_speed = 0.043;
		info->rot_speed = 0.026;
	}
	else if (!(info->key_ar_u) && info->key_ar_d)
	{
		info->move_speed = 0.003;
		info->rot_speed = 0.002;
	}
	else if (!(info->key_ar_u) && !(info->key_ar_d))
	{
		info->move_speed = 0.008;
		info->rot_speed = 0.006;
	}
	key_update_ws(info);
}

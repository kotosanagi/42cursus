/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:26:56 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 18:27:52 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	sort_sprites_distance(t_raycasting *rc, t_info *info)
{
	rc->i = 0;
	while (rc->i < info->num_sprite)
	{
		info->sprite_order[rc->i] = rc->i;
		info->sprite_distance[rc->i] =
		((info->pos_x - info->sp[rc->i].x)
		* (info->pos_x - info->sp[rc->i].x)
		+ (info->pos_y - info->sp[rc->i].y)
		* (info->pos_y - info->sp[rc->i].y));
		rc->i += 1;
	}
	sort_sprites(info->sprite_order,
	info->sprite_distance, info->num_sprite, info);
}

static void	get_sprite_screen_x(t_raycasting *rc, t_info *info)
{
	rc->sprite_x = info->sp[info->sprite_order[rc->i]].x - info->pos_x;
	rc->sprite_y = info->sp[info->sprite_order[rc->i]].y - info->pos_y;
	rc->inv_det = 1.0
	/ (info->plane_x * info->dir_y - info->dir_x * info->plane_y);
	rc->transform_x = rc->inv_det
	* (info->dir_y * rc->sprite_x - info->dir_x * rc->sprite_y);
	rc->transform_y = rc->inv_det
	* (-info->plane_y * rc->sprite_x + info->plane_x * rc->sprite_y);
	rc->sprite_screen_x = (int)((info->r_width / 2)
	* (1 + rc->transform_x / rc->transform_y));
}

static void	calc_sprite_size(t_raycasting *rc, t_info *info)
{
	rc->sprite_height = (int)fabs(info->r_height / rc->transform_y);
	rc->draw_start_y = -rc->sprite_height / 2 + info->r_height / 2;
	if (rc->draw_start_y < 0)
		rc->draw_start_y = 0;
	rc->draw_end_y = rc->sprite_height / 2 + info->r_height / 2;
	if (rc->draw_end_y >= info->r_height)
		rc->draw_end_y = info->r_height - 1;
	rc->sprite_width = (int)fabs(info->r_height / rc->transform_y);
	rc->draw_start_x = -rc->sprite_width / 2 + rc->sprite_screen_x;
	if (rc->draw_start_x < 0)
		rc->draw_start_x = 0;
	rc->draw_end_x = rc->sprite_width / 2 + rc->sprite_screen_x;
	if (rc->draw_end_x >= info->r_width)
		rc->draw_end_x = info->r_width - 1;
}

static void	store_stripe_tex(t_raycasting *rc, t_info *info)
{
	rc->tex_x = (int)((256 * (rc->stripe
	- (-rc->sprite_width / 2 + rc->sprite_screen_x))
	* TEX_WIDTH / rc->sprite_width) / 256);
	if (rc->transform_y > 0 && rc->stripe > 0 && rc->stripe < info->r_width
	&& rc->transform_y < info->z_buffer[rc->stripe])
	{
		rc->y = rc->draw_start_y;
		while (rc->y < rc->draw_end_y)
		{
			rc->d = rc->y * 256 - info->r_height
			* 128 + rc->sprite_height * 128;
			rc->tex_y = ((rc->d * TEX_HEIGHT) / rc->sprite_height) / 256;
			rc->color = info->tex[SPRITE_TEXTURE].addr[TEX_WIDTH
			* rc->tex_y + rc->tex_x];
			if (rc->color & 0x00FFFFFF)
				info->buf[rc->y][rc->stripe] = rc->color;
			rc->y += 1;
		}
	}
}

void		store_sprite(t_raycasting *rc, t_info *info)
{
	sort_sprites_distance(rc, info);
	rc->i = 0;
	while (rc->i < info->num_sprite)
	{
		get_sprite_screen_x(rc, info);
		calc_sprite_size(rc, info);
		rc->stripe = rc->draw_start_x;
		while (rc->stripe < rc->draw_end_x)
		{
			store_stripe_tex(rc, info);
			rc->stripe += 1;
		}
		rc->i += 1;
	}
}

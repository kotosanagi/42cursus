/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:49:18 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 20:21:28 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	store_ceiling_floor(t_raycasting *rc, t_info *info)
{
	rc->y = 0;
	while (rc->y < info->r_height)
	{
		rc->x = 0;
		while (rc->x < info->r_width)
		{
			if (rc->y < info->r_height / 2)
				rc->color = info->ceiling_color;
			else
				rc->color = info->floor_color;
			info->buf[rc->y][rc->x] = rc->color;
			rc->x += 1;
		}
		rc->y += 1;
	}
}

void		calc_func(t_info *info)
{
	t_raycasting rc;

	store_ceiling_floor(&rc, info);
	store_wall(&rc, info);
	store_sprite(&rc, info);
}

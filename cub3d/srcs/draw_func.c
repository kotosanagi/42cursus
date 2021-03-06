/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:44:34 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 11:45:15 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_func(t_info *info)
{
	int y;
	int x;

	y = 0;
	while (y < info->r_height)
	{
		x = 0;
		while (x < info->r_width)
		{
			info->img.data[y * info->r_width + x] = info->buf[y][x];//0305
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 19:36:35 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/03 05:57:58 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_sprite	set_sprite(int y, int x)
{
	t_sprite new_sprite;

	new_sprite.y = (double)y + 0.5;
	new_sprite.x = (double)x + 0.5;
	return (new_sprite);
}

void			get_sprite_info(t_info *info)
{
	int i;
	int y;
	int x;

	if (info->num_sprite == 0)
		return ;
	if (!(info->sp = (t_sprite *)malloc(sizeof(t_sprite) * info->num_sprite)))
		error_free_exit("can't allocate sprite\n", info);
	i = 0;
	y = 0;
	while (y < info->map_h)
	{
		x = 0;
		while (info->map[y][x])
		{
			if (info->map[y][x] == '2')
				info->sp[i++] = set_sprite(y, x);
			x++;
		}
		y++;
	}
	if (!(info->sprite_order = (int *)malloc(sizeof(int) * info->num_sprite)))
		error_free_exit("can't allocate sprite_order\n", info);
	if (!(info->sprite_distance = (double *)malloc(sizeof(double) * info->num_sprite)))
		error_free_exit("can't allocate sprite_distance\n", info);
}
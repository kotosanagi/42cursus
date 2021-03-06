/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:10:33 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 20:05:42 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		safe_free(void *p)
{
	free(p);
	p = NULL;
}

void		error_exit(char *message)
{
	printf("Error\n");
	printf("%s", message);
	exit(EXIT_FAILURE);
}

static void	error_free_exit2(char *msg, t_info *info)
{
	int i;

	i = 0;
	if (info->tex[0].w > 0)
	{
		while (i < 5)
			safe_free(info->tex[i++].addr);
	}
	safe_free(info->sprite_order);
	safe_free(info->sprite_distance);
	error_exit(msg);
}

void		error_free_exit(char *msg, t_info *info)
{
	int	i;

	safe_free(info->east_path);
	safe_free(info->west_path);
	safe_free(info->south_path);
	safe_free(info->north_path);
	safe_free(info->sprite_path);
	i = 0;
	while (info->map[i])
		safe_free(info->map[i++]);
	if (info->num_sprite > 0)
		safe_free(info->sp);
	if (info->buf_malloc_flg == 1)
	{
		i = info->r_height - 1;
		while (i >= 0)
			safe_free(info->buf[i--]);
		safe_free(info->buf);
	}
	error_free_exit2(msg, info);
}

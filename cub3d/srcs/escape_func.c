/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:37:12 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 20:27:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			close_window(int keycode, t_info *info)
{
	if (keycode == K_ESC)
		mlx_destroy_window(info->mlx, info->win);
	return (0);
}

int			close_window_redx(void)
{
	printf("thank you for playing!\n");
	exit(EXIT_SUCCESS);
	return (0);
}

static void	exit_successful2(t_info *info)
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
	printf("thank you for playing!\n");
	exit(EXIT_SUCCESS);
}

void		exit_successful(t_info *info)
{
	int	i;

	i = 0;
	safe_free(info->east_path);
	safe_free(info->west_path);
	safe_free(info->south_path);
	safe_free(info->north_path);
	safe_free(info->sprite_path);
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
	exit_successful2(info);
}

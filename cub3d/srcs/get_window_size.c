/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 05:55:38 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 08:23:47 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	compare_resolusion(t_info *info)
// {
// 	int	window_w;
// 	int window_h;
// 	mlx_get_screen_size(info->mlx, &window_w, &window_h);
// // printf("r_height:%d\n", info->r_height);
// // printf("r_width :%d\n", info->r_width);
// // printf("window_w:%d\n", window_w);
// // printf("window_h:%d\n", window_h);
// 	info->r_height = (int)fmin(info->r_height, window_h);
// 	info->r_width = (int)fmin(info->r_width, window_w);
// // printf("r_height:%d\n", info->r_height);
// // printf("r_width :%d\n", info->r_width);
// }

void	get_window_size(t_info *info)
{
	int	window_w;
	int window_h;

	if (!(info->mlx = mlx_init()))
		error_free_exit("can't exec mlx_init()\n", info);
// compare_resolusion(info);/////////////////
	mlx_get_screen_size(info->mlx, &window_w, &window_h);
// printf("r_height:%d\n", info->r_height);
// printf("r_width :%d\n", info->r_width);
// printf("window_w:%d\n", window_w);
// printf("window_h:%d\n", window_h);
	info->r_height = (int)fmin(info->r_height, window_h);
	info->r_width = (int)fmin(info->r_width, window_w);
	info->r_height = (int)fmax(info->r_height, 192);
	info->r_width = (int)fmax(info->r_width, 256);
// printf("r_height:%d\n", info->r_height);
// printf("r_width :%d\n", info->r_width);
	if (!(info->z_buffer = (double *)malloc(sizeof(double) * info->r_width)))
		error_free_exit("can't allocate z_buffer\n", info);
}

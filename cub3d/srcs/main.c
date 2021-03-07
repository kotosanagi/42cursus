/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 04:57:59 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/07 16:53:35 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	main_loop(t_info *info)
{
	key_update(info);
	calc_func(info);
	draw_func(info);
	return (0);
}

int			main(int argc, char *argv[])
{
	t_info	info;

	init_info(&info);
	is_correct_arg(argc, argv, &info);
	get_mapfile_info(argv[1], &info);
	analyze_mapdata(&info);
	get_sprite_info(&info);
	get_window_size(&info);
	set_buf(&info);
	load_texture(&info);
	if (info.save_flg == 1)
		create_bmp(&info);
	info.win = mlx_new_window(info.mlx, info.r_width, info.r_height, "cub3D");
	info.img.img = mlx_new_image(info.mlx, info.r_width, info.r_height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp,
	&info.img.size_l, &info.img.endian);
	mlx_hook(info.win, 2, 1L << 0, close_window, &info);
	mlx_hook(info.win, 33, 1L << 17, close_window_redx, &info);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &info);
	mlx_loop(info.mlx);
	return (0);
}

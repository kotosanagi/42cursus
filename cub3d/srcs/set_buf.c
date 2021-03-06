/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:58:41 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 11:00:58 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_buf(t_info *info)
{
	int i;
	int j;

	if (!(info->buf = (int **)malloc(sizeof(int *) * info->r_height)))
		error_free_exit("1st buf malloc error\n", info);
	i = 0;
	while (i < info->r_height)
	{
		if (!(info->buf[i++] = (int *)malloc(sizeof(int) * info->r_width)))
			error_free_exit("2nd buf malloc error\n", info);
	}
	i = 0;
	while (i < info->r_height)// for (int i = 0; i < info->r_height; i++)
	{
		j = 0;
		while (j < info->r_width)// for (int j = 0; j < info->r_width; j++)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	info->buf_malloc_flg = 1;
}

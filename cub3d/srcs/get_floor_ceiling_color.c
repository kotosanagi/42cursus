/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor_ceiling_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:39:34 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 19:44:32 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_floor_ceiling_color(t_info *info)
{
	info->floor_color = (info->floor_red << 16)
	+ (info->floor_green << 8) + info->floor_blue;
	info->ceiling_color = (info->ceiling_red << 16)
	+ (info->ceiling_green << 8) + info->ceiling_blue;
}

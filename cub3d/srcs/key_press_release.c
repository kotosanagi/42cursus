/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_release.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 08:17:50 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 09:19:51 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int key, t_info *info)
{
	if (key == K_ESC)
		info->key_esc = 1;
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_AR_R)
		info->key_ar_r = 1;
	else if (key == K_AR_L)
		info->key_ar_l = 1;
	else if (key == K_AR_U)
		info->key_ar_u = 1;
	else if (key == K_AR_D)
		info->key_ar_d = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		info->key_esc = 1;
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_AR_R)
		info->key_ar_r = 0;
	else if (key == K_AR_L)
		info->key_ar_l = 0;
	else if (key == K_AR_U)
		info->key_ar_u = 0;
	else if (key == K_AR_D)
		info->key_ar_d = 0;
	return (0);
}

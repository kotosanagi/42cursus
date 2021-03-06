/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapfile_info_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:33:58 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 19:41:07 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_enough_8elements(t_info *info)
{
	if (!info)
		return (0);
	if (info->r_width == -1 ||
		info->east_path == NULL ||
		info->west_path == NULL ||
		info->south_path == NULL ||
		info->north_path == NULL ||
		info->sprite_path == NULL ||
		info->floor_red == -1 ||
		info->ceiling_red == -1)
		return (0);
	return (1);
}

int		cnt_elem(char **elem)
{
	int i;

	i = 0;
	if (!elem)
		return (0);
	while (elem[i])
		i++;
	return (i);
}

int		is_num(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

int		is_correct_rgb(t_info *info, char **elem, char **rgb)
{
	if (cnt_elem(rgb) != 3)
	{
		free_elem(rgb);
		error_free_elem_exit("F or C color needs 3 numbers\n", info, elem);
	}
	else if (!(is_num(rgb[0]) || !(is_num(rgb[1]) || !(is_num(rgb[2])))))
	{
		free_elem(rgb);
		error_free_elem_exit("F or C color needs positive nums\n", info, elem);
	}
	else if ((rgb[0][0] == '0' && ft_strlen(rgb[0]) != 1)
			|| (rgb[1][0] == '0' && ft_strlen(rgb[1]) != 1)
			|| (rgb[2][0] == '0' && ft_strlen(rgb[2]) != 1))
	{
		free_elem(rgb);
		error_free_elem_exit("F/C need to start without zero\n", info, elem);
	}
	else if (ft_strlen(rgb[0]) > 3 ||
	ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 3)
	{
		free_elem(rgb);
		error_free_elem_exit("F/C read too large num\n", info, elem);
	}
	return (1);
}

int		cnt_str_c(char *str, char c)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}

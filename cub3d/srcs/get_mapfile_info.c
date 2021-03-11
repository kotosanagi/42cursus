/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapfile_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:15:14 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/12 07:20:41 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int		is_mapfile_elem4(t_info *info, char **elem)
{
	char **rgb;

	if (ft_strncmp(elem[0], "C", 2) == 0 && info->ceiling_red < 0 &&
	cnt_elem(elem) == 2 && cnt_str_c(elem[1], ',') == 2)
	{
		rgb = ft_split(elem[1], ',');
		is_correct_rgb(info, elem, rgb);
		if (!(is_num(rgb[0])) || !(is_num(rgb[1])) || !(is_num(rgb[2])))
			error_free_elem_exit("C only positive integer\n", info, elem);
		info->ceiling_red = ft_atoi(rgb[0]);
		info->ceiling_green = ft_atoi(rgb[1]);
		info->ceiling_blue = ft_atoi(rgb[2]);
		free_elem(rgb);
		if (255 < info->ceiling_red || 255 < info->ceiling_green ||
		255 < info->ceiling_blue)
			error_free_elem_exit("C allows 0~255\n", info, elem);
	}
	else
		error_free_elem_exit("map file is invalid\n", info, elem);
	return (1);
}

static int		is_mapfile_elem3(t_info *info, char **elem)
{
	char **rgb;

	if (ft_strncmp(elem[0], "F", 2) == 0 && info->floor_red < 0 &&
	cnt_elem(elem) == 2 && cnt_str_c(elem[1], ',') == 2)
	{
		rgb = ft_split(elem[1], ',');
		is_correct_rgb(info, elem, rgb);
		if (!(is_num(rgb[0])) || !(is_num(rgb[1])) || !(is_num(rgb[2])))
			error_free_elem_exit("F only positive integer\n", info, elem);
		info->floor_red = ft_atoi(rgb[0]);
		info->floor_green = ft_atoi(rgb[1]);
		info->floor_blue = ft_atoi(rgb[2]);
		free_elem(rgb);
		if (255 < info->floor_red || 255 < info->floor_green ||
		255 < info->floor_blue)
			error_free_elem_exit("F allows 0~255\n", info, elem);
	}
	else
		is_mapfile_elem4(info, elem);
	return (1);
}

static int		is_mapfile_elem2(t_info *info, char **elem)
{
	if ((ft_strncmp(elem[0], "EA", 3) == 0 && !info->east_path &&
	cnt_elem(elem) == 2))
		info->east_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "WE", 3) == 0 && !info->west_path &&
	cnt_elem(elem) == 2))
		info->west_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "SO", 3) == 0 && !info->south_path &&
	cnt_elem(elem) == 2))
		info->south_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "NO", 3) == 0 && !info->north_path &&
	cnt_elem(elem) == 2))
		info->north_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "S", 2) == 0 && !info->sprite_path &&
	cnt_elem(elem) == 2))
		info->sprite_path = ft_strdup(elem[1]);
	else
		is_mapfile_elem3(info, elem);
	return (1);
}

static int		is_mapfile_elem(t_info *info, char **elem)
{
	if (!*elem)
		return (0);
	if (!(ft_strncmp(elem[0], "R", 2)) && info->r_width < 0 &&
	cnt_elem(elem) == 3)
	{
		if (!(is_num(elem[1])) || !(is_num(elem[2])))
			error_free_elem_exit("R needs only positive integer\n", info, elem);
		if (elem[1][0] == '0' || elem[2][0] == '0')
			error_free_elem_exit("R needs only positive integer\n", info, elem);
		info->r_width = (ft_strlen(elem[1]) > 4 ||
		ft_atoi(elem[1]) > 2560) ? 2560 : ft_atoi(elem[1]);
		info->r_height = (ft_strlen(elem[2]) > 4 ||
		ft_atoi(elem[2]) > 1440) ? 1440 : ft_atoi(elem[2]);
	}
	else
		is_mapfile_elem2(info, elem);
	return (1);
}

void			get_mapfile_info(char *path, t_info *info)
{
	int		fd;
	char	*line;
	char	**elem;
	int		gnl_ret;

	if ((fd = open(path, O_RDONLY)) == -1)
		error_exit("can't open the file...\nplease check the path of file\n");
	while (!(is_enough_8elements(info)))
	{
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret == -1)
			error_free_exit("expect the path is not file\n", info);
		elem = ft_split(line, ' ');
		safe_free(line);
		is_mapfile_elem(info, elem);
		if ((gnl_ret == 0) && !(is_enough_8elements(info)))
			error_free_elem_exit("map elements is not enough\n", info, elem);
		free_elem(elem);
	}
	get_floor_ceiling_color(info);
	get_mappart_data(fd, &line, info);
	close(fd);
}

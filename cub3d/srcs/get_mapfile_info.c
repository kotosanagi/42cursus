/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapfile_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:15:14 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/28 16:00:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_enough_8elements(t_info *info)
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

void	get_floor_ceiling_color(t_info *info)// exec after get file info (end of read_file func)
{
	info->floor_color = (info->floor_red << 16) + (info->floor_green << 8) + info->floor_blue;
	info->ceiling_color = (info->ceiling_red << 16) + (info->ceiling_green << 8) + info->ceiling_blue;
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
	else if (ft_strlen(rgb[0]) > 3 || ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 3)
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

int		is_mapfile_elem4(t_info *info, char **elem)
{
	char **rgb;

	if (ft_strncmp(elem[0], "C", 2) == 0  && info->ceiling_red < 0 &&
	cnt_elem(elem) == 2 && cnt_str_c(elem[1], ',') == 2)
	{
		rgb = ft_split(elem[1], ',');
		is_correct_rgb(info, elem, rgb);
		info->ceiling_red = ft_atoi(rgb[0]);
		info->ceiling_green = ft_atoi(rgb[1]);
		info->ceiling_blue = ft_atoi(rgb[2]);
		free_elem(rgb);
		if (255 < info->ceiling_red || 255 < info->ceiling_green ||
		255 < info->ceiling_blue)
			error_free_elem_exit("C arrows 0~255\n", info, elem);
	}
	else
		error_free_elem_exit("map file is invalid\n", info, elem);
	return (1);
}

int		is_mapfile_elem3(t_info *info, char **elem)
{
	char **rgb;

	if (ft_strncmp(elem[0], "F", 2) == 0 && info->floor_red < 0 &&
	cnt_elem(elem) == 2 && cnt_str_c(elem[1], ',') == 2)
	{
		rgb = ft_split(elem[1], ',');
		is_correct_rgb(info, elem, rgb);
		info->floor_red = ft_atoi(rgb[0]);
		info->floor_green = ft_atoi(rgb[1]);
		info->floor_blue = ft_atoi(rgb[2]);
		free_elem(rgb);
		if (255 < info->floor_red || 255 < info->floor_green ||
		255 < info->floor_blue)
			error_free_elem_exit("F arrows 0~255\n", info, elem);
	}
	else
		is_mapfile_elem4(info, elem);
	return (1);
}

int		is_mapfile_elem2(t_info *info, char **elem)
{
	if ((ft_strncmp(elem[0], "EA", 3) == 0 && !info->east_path &&
	cnt_elem(elem) == 2))
		info->east_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "WE", 3) == 0  && !info->west_path &&
	cnt_elem(elem) == 2))
		info->west_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "SO", 3) == 0  && !info->south_path &&
	cnt_elem(elem) == 2))
		info->south_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "NO", 3) == 0  && !info->north_path &&
	cnt_elem(elem) == 2))
		info->north_path = ft_strdup(elem[1]);
	else if ((ft_strncmp(elem[0], "S", 2) == 0  && !info->sprite_path &&
	cnt_elem(elem) == 2))
		info->sprite_path = ft_strdup(elem[1]);
	else
		is_mapfile_elem3(info, elem);
	return (1);
}

int		is_mapfile_elem(t_info *info, char **elem)
{
	if (!*elem)
		return (0);
	if (!(ft_strncmp(elem[0], "R", 2)) && info->r_width < 0 &&
	cnt_elem(elem) == 3)
	{
		if (!(is_num(elem[1])) || !(is_num(elem[2])))
			error_free_elem_exit("R needs only positive number\n", info, elem);
		if (elem[1][0] == '0' || elem[2][0] == '0')
			error_free_elem_exit("R needs only positive number\n", info, elem);
		info->r_width = (ft_strlen(elem[1]) > 5 ||
		ft_atoi(elem[1]) > 10000) ? 10000 : ft_atoi(elem[1]);
		info->r_height = (ft_strlen(elem[2]) > 4 ||
		ft_atoi(elem[2]) > 10000) ? 10000 : ft_atoi(elem[2]);
	}
	else
		is_mapfile_elem2(info, elem);
	return (1);
}

void	get_mapfile_info(char *path, t_info *info)
{
	int		fd;
	char	*line;
	char	**elem;
	int		gnl_ret;

	if ((fd = open(path, O_RDONLY)) == -1)
		error_exit("can't open the file...\nplease check the path of file\n");
printf("success open file : fd:%d\n", fd);///

	while (!(is_enough_8elements(info)))
	{
		gnl_ret = get_next_line(fd, &line);
		if (gnl_ret == -1)
			error_exit("expect the path is not file\n");
		elem = ft_split(line, ' ');
		safe_free(line);
		is_mapfile_elem(info, elem);


// DEBUG_print_info(info);


		if ((gnl_ret == 0) && !(is_enough_8elements(info)))
			error_free_elem_exit("map elements is not enough\n", info, elem);
		free_elem(elem);
	}

	get_floor_ceiling_color(info);
// DEBUG_print_info(info);
	get_mappart_data(fd, &line, info);
DEBUG_print_MAPPPPPP(info);


printf("escape!\n");
	close(fd);
}
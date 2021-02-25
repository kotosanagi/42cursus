/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mapfile_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 17:15:14 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/25 22:42:41 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_enough_8elements(t_info *info)
{
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
	while (elem[i])
		i++;
	return (i);
}

int		is_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

int		is_mapfile_elem(t_info *info, char **elem)
{
	if (!*elem)
		return (0);
	if (!(ft_strncmp(elem[0], "R", 2)) && info->r_width < 0 && cnt_elem(elem) == 3)
	{
		if (!(is_number(elem[1])) || !(is_number(elem[2])))
			error_free_elem_exit("R needs only positive number\n", info, elem);
		if (elem[1][0] == '0' || elem[2][0] == '0')
			error_free_elem_exit("R needs only positive number\n", info, elem);
		info->r_width = (ft_strlen(elem[1]) > 5 || ft_atoi(elem[1]) > 1920) ? 1920 : ft_atoi(elem[1]);
		info->r_height = (ft_strlen(elem[2]) > 4 || ft_atoi(elem[2]) > 996) ? 996 : ft_atoi(elem[2]);
	}
	else
		printf("go to next checker~~~!!\n");
	return 1;
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
		if (!(is_mapfile_elem(info, elem)))
			error_free_elem_exit("mapfile elememt is wrong\n", info, elem);

printf("-------\n");
printf("r_width :%d\n", info->r_width);
printf("r_height:%d\n", info->r_height);

printf("east  :%s\n", info->east_path);
printf("west  :%s\n", info->west_path);
printf("south :%s\n", info->south_path);
printf("north :%s\n", info->north_path);
printf("sprite:%s\n", info->sprite_path);

printf("pos_x  :%f\n", info->pos_x);
printf("pos_y  :%f\n", info->pos_y);
printf("dir_x  :%f\n", info->dir_x);
printf("dir_y  :%f\n", info->dir_y);
printf("plane_x:%f\n", info->plane_x);
printf("plane_y:%f\n", info->plane_y);

printf("floor_red  :%d\n", info->floor_red);
printf("floor_green:%d\n", info->floor_green);
printf("floor_blue :%d\n", info->floor_blue);
printf("ceiling_red  :%d\n", info->ceiling_red);
printf("ceiling_green:%d\n", info->ceiling_green);
printf("ceiling_blue :%d\n", info->ceiling_blue);

printf("floor_color  :%x\n", info->floor_color);
printf("ceiling_color:%x\n", info->ceiling_color);
printf("num_sprite:%d\n", info->num_sprite);



printf("-------\n");



		if ((gnl_ret == 0) && !(is_enough_8elements(info)))
			error_free_elem_exit("map elements is not enough\n", info, elem);
		free_elem(elem);
	}
	printf("escape!\n");
}
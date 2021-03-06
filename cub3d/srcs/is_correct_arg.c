/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:31:15 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 19:22:05 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	is_cub_extension(char *filename)
{
	int name_len;

	name_len = (int)ft_strlen(filename);
	if (name_len <= 4)
		error_exit("filename is short\n");
	else if (strncmp(filename + name_len - 4, ".cub", 5))
		error_exit("filename is not \".cub\" extension\n");
}

void		is_correct_arg(int argc, char *argv[], t_info *info)
{
	char *filename;

	if (argc < 2)
		error_exit("please add map file path on next argument\n");
	else if (argc > 3)
		error_exit("too much argument!\n");
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			error_exit("second argument is not \"--save\"\n");
		else
			info->save_flg = 1;
	}
	if (ft_strrchr(argv[1], '/'))
		filename = ft_strrchr(argv[1], '/') + 1;
	else
		filename = argv[1];
	is_cub_extension(filename);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:10:33 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/25 21:30:41 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	safe_free(void *p)
{
	free(p);
	p = NULL;
}

void	error_exit(char *message)
{
	printf("Error\n");
	printf("%s", message);
	exit(EXIT_FAILURE);
}

void	error_free_exit(char *msg, t_info *info)
{
	int	i;

	i = 0;
	safe_free(info->east_path);
	safe_free(info->west_path);
	safe_free(info->south_path);
	safe_free(info->north_path);
	safe_free(info->sprite_path);
	while (info->map[i])
		safe_free(info->map[i++]);

	error_exit(msg);
}

void	free_elem(char **elem)
{
	int i;

	i = 0;
	while (elem[i] != NULL)
		safe_free(elem[i++]);
	safe_free(elem);
}

void	error_free_elem_exit(char *msg, t_info *info, char **elem)
{
	free_elem(elem);
	error_free_exit(msg, info);
}
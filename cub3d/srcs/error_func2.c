/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:05:26 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 20:05:39 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	error_free_line(char *msg, t_info *info, char *str, int fd)
{
	close(fd);
	safe_free(str);
	error_free_exit(msg, info);
}

void	error_fd_close(char *msg, t_info *info, int fd)
{
	close(fd);
	error_free_exit(msg, info);
}

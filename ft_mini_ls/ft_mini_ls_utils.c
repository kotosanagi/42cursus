/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:36:56 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/03 22:49:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

long		get_modified_time(char *filename, char *path)
{
	struct stat	*buf;
	long		time;

	buf = (struct stat *)malloc(sizeof(struct stat));
	if (stat(filename, buf) == -1)
	{
		perror(path);
		return (-1);
	}
	else
		time = buf->st_mtime;
	free(buf);
	buf = NULL;
	return (time);
}

t_filelist	*make_filelist(struct dirent *dir2, char *path)
{
	t_filelist	*new;

	if (!(new = (t_filelist *)malloc(sizeof(t_filelist))))
		return (NULL);
	new->filename = dir2->d_name;
	new->modified_time = get_modified_time(new->filename, path);
	if (new->modified_time == -1)
	{
		perror(path);
		return (NULL);
	}
	return (new);
}

void		ft_putstr(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

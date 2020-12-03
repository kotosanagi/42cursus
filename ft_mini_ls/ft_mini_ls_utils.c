/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:36:56 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/04 01:49:57 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

long		get_modified_time(char *filename)
{
	struct stat	*buf;
	long		time;

	buf = (struct stat *)malloc(sizeof(struct stat));
	if (stat(filename, buf) == -1)
		return (-1);
	else
		time = buf->st_mtime;
	free(buf);
	buf = NULL;
	return (time);
}

t_filelist	*make_filelist(struct dirent *dir2)
{
	t_filelist	*new;

	if (!(new = (t_filelist *)malloc(sizeof(t_filelist))))
		return (NULL);
	new->filename = dir2->d_name;
	new->modified_time = get_modified_time(new->filename);
	if (new->modified_time == -1)
		return (NULL);
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

void		swap_filelist(t_filelist **lst, int *i)
{
	t_filelist	*tmp;

	tmp = lst[*i];
	lst[*i] = lst[*i + 1];
	lst[*i + 1] = tmp;
	*i = 0;
}

int			put_error(int i)
{
	if (i == E_ARG)
		write(2, "don't execute with commandline arguments\n", 41);
	else if (i == E_MALLOC)
		write(2, "fail to allocate memory\n", 24);
	return (-1);
}

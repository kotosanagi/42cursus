/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 23:36:16 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/04 01:24:26 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

t_filelist	**allocate_lst(t_filelist **lst, int *len)
{
	int				i;
	struct dirent	*dir;
	DIR				*dp;

	i = 0;
	if (!(dp = opendir(".")))
		return (NULL);
	while ((dir = readdir(dp)) != NULL)
		i++;
	free(lst);
	if (!(lst = (t_filelist **)malloc(sizeof(t_filelist *) * i)))
		return (NULL);
	*len = i;
	closedir(dp);
	return (lst);
}

t_filelist	**get_fileinfo(t_filelist **lst)
{
	DIR				*dp;
	struct dirent	*dir;
	int				i;

	i = 0;
	if (!(dp = opendir(".")))
		return (NULL);
	while ((dir = readdir(dp)) != NULL)
	{
		lst[i] = make_filelist(dir);
		i++;
	}
	closedir(dp);
	return (lst);
}

void		sort_filelist(int len, t_filelist **lst)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (lst[i]->modified_time > lst[i + 1]->modified_time)
			swap_filelist(lst, &i);
		else
			i++;
	}
}

void		write_filename(t_filelist **lst, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (lst[i]->filename[0] != '.')
		{
			ft_putstr(lst[i]->filename);
			write(1, "\n", 1);
		}
		i++;
	}
}

int			main(int argc, char *argv[])
{
	t_filelist	**lst;
	int			len;

	(void)argv;
	if (argc != 1)
		return (put_error(E_ARG));
	if (!(lst = (t_filelist **)malloc(1)))
		return (put_error(E_MALLOC));
	lst = allocate_lst(lst, &len);
	get_fileinfo(lst);
	sort_filelist(len, lst);
	write_filename(lst, len);
	return (1);
}

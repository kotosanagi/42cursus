/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:44:35 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/21 22:44:52 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_newline(int fd, char **line, char **st_arr, char *buf)
{
	int		ret;
	size_t	len;
	char	*tmp_line;
	char	*tmp_buf;

	ret = 0;
	len = ft_strchr_len(buf, '\n');
	if (!(tmp_line = ft_strnjoin(*line, buf, len)))
		return (-1);
	free(*line);
	*line = tmp_line;
	tmp_buf = NULL;
	if (buf[len] == '\n')
	{
		if (!(tmp_buf = ft_strdup(buf + len + 1)))
			return (-1);
		ret = 1;
	}
	free(st_arr[fd]);
	st_arr[fd] = tmp_buf;
	return (ret);
}

int	read_fd(int fd, char **line, char **st_arr)
{
	ssize_t	read_len;
	char	*buf;
	int		ret;

	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	ret = 0;
	while (ret == 0 && (read_len = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_len] = '\0';
		ret = find_newline(fd, line, st_arr, buf);
	}
	free(buf);
	if (read_len == -1)
		return (free_all(line, st_arr, fd));
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*st_arr[MAX_FD];
	int			ret;

	ret = 0;
	if (fd < 0 || MAX_FD <= fd || !line)
		return (-1);
	if (!(*line = (char *)malloc(1)))
		return (-1);
	*line[0] = '\0';
	if (st_arr[fd] != NULL)
		ret = find_newline(fd, line, st_arr, st_arr[fd]);
	if (ret == 0)
		ret = read_fd(fd, line, st_arr);
	return (ret);
}

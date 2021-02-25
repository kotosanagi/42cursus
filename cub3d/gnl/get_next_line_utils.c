/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:16:31 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/25 17:49:59 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strchr_len(char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnjoin(char *s1, char *s2, size_t len_s2)
{
	char	*ret;
	size_t	len_s1;
	size_t	i;
	size_t	s_count;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen_gnl(s1);
	if (!(ret = (char *)malloc(len_s1 + len_s2 + 1)))
		return (NULL);
	i = 0;
	s_count = 0;
	while (s1[s_count])
		ret[i++] = s1[s_count++];
	s_count = 0;
	while (s_count < len_s2)
		ret[i++] = s2[s_count++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strdup_gnl(char *s1)
{
	char	*arr;
	size_t	len;
	size_t	i;

	len = ft_strlen_gnl(s1);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

int		free_all_gnl(char **line, char **st_arr, int fd)
{
	free(*line);
	*line = NULL;
	free(st_arr[fd]);
	st_arr[fd] = NULL;
	return (-1);
}

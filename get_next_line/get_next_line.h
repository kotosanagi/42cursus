/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:13:23 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/20 06:14:20 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define MAX_FD	 30

int		get_next_line(int fd, char **line);
int		read_fd(int fd, char **line, char **st_arr);
int		find_newline(int fd, char **line, char **st_arr, char *buf);
size_t	ft_strchr_len(char *s, char c);
size_t	ft_strlen(char *s);
char	*ft_strnjoin(char *s1, char *s2, size_t len_s2);
char	*ft_strdup(char *s1);
int		free_all(char **line, char **st_arr, int fd);

#endif

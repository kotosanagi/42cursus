/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:13:23 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/25 17:46:55 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define BUFFER_SIZE 2048

int		get_next_line(int fd, char **line);
int		read_fd(int fd, char **line, char **st_arr);
int		find_newline(int fd, char **line, char **st_arr, char *buf);
size_t	ft_strchr_len(char *s, char c);
size_t	ft_strlen_gnl(char *s);
char	*ft_strnjoin(char *s1, char *s2, size_t len_s2);
char	*ft_strdup_gnl(char *s1);
int		free_all_gnl(char **line, char **st_arr, int fd);

#endif

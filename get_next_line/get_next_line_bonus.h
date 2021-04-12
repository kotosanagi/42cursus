/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 22:45:11 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/06 22:52:44 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

int		get_next_line(int fd, char **line);
int		read_fd(int fd, char **line, char **st_arr);
int		find_newline(int fd, char **line, char **st_arr, char *buf);
size_t	ft_strchr_len(char *s, char c);
size_t	ft_strlen(char *s);
char	*ft_strnjoin(char *s1, char *s2, size_t len_s2);
char	*ft_strdup(char *s1);
int		free_all(char **line, char **st_arr, int fd);

#endif

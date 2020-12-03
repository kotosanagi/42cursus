/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:41:42 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/03 22:48:28 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include <stdio.h>///////////
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct	s_filelist
{
	char	*filename;
	long	modified_time;
}				t_filelist;

t_filelist		**allocate_lst(DIR *dp, t_filelist **lst, int *len);
t_filelist		**get_fileinfo(DIR *dp2, t_filelist **lst);
void			sort_filelist(int len, t_filelist **lst);
void			write_filename(t_filelist **lst, int len);
long			get_modified_time(char *filename, char *path);
t_filelist		*make_filelist(struct dirent *dir2, char *path);
void			ft_putstr(char *str);

#endif

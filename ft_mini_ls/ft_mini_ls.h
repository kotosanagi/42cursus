/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:41:42 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/04 01:40:02 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_filelist
{
	char			*filename;
	long			modified_time;
}				t_filelist;

typedef enum	e_error
{
	E_ARG,
	E_MALLOC
}				t_error;

t_filelist		**allocate_lst(t_filelist **lst, int *len);
t_filelist		**get_fileinfo(t_filelist **lst);
void			sort_filelist(int len, t_filelist **lst);
void			write_filename(t_filelist **lst, int len);
long			get_modified_time(char *filename);
t_filelist		*make_filelist(struct dirent *dir2);
void			ft_putstr(char *str);
int				put_error(int i);
void			swap_filelist(t_filelist **lst, int *i);

#endif

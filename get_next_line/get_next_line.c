/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:12:18 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/18 17:16:24 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>//////


//st_arr の、\nまでをlineにくっつける。st_arrは更新。\nがあったなら1、ないなら0を、エラーなら-1を返す。
int	find_newline(int fd, char **line, char **st_arr, char *buf)
{
	int ret;
	size_t len;
	char *tmp_line;
	char *tmp_buf;

	ret = 0;
	len = ft_strchr_len(buf, '\n');//search '\n' from buf
	if (!(tmp_line = ft_strnjoin(*line, buf, len)))//line に bufのlen文字分 をくっつける
		return (-1);
	free(*line);
	*line = tmp_line;
	tmp_buf = NULL;//この初期化がないと6行下のfree(st_arr[fd])がallocatedされてないやつはfreeできませんってなる。ガチで謎。
	if (buf[len] == '\n')
	{
		if (!(tmp_buf = ft_strdup(buf + len + 1)))// \n以降の文字列をいったん作る
			return (-1);
		ret = 1;
	}
	free(st_arr[fd]);//いったんさっきまでのstatic_arrayの内容は忘れる
	st_arr[fd] = tmp_buf;// static_array に tmp_bufをしまう
	return (ret);
}

//readして、そこに\nがあればそれをlineにくっつける関数
int	read_from_fd(int fd, char **line, char **st_arr)
{
	ssize_t	read_len;
	char *buf;
	int ret;

	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	ret = 0;
	while (ret == 0 && fd >= 0 && (read_len = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[BUFFER_SIZE] = '\0';
		ret = find_newline(fd, line, st_arr, buf);// \n check from (bufに\nがあるかチェックする。あるならlineにbufの\n手前までくっつけて、\0をくっつける)
	}
	free(buf);
	if (read_len == -1)
		return (free_all(line, st_arr, fd));
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char *st_arr[MAX_FD];
	int ret;

	ret = 0;
	if (fd < 0 || MAX_FD <= fd || !line)
		return (-1);
	if (!(*line = (char *)malloc(1)))
		return (-1);
	*line[0] = '\0';
	if (st_arr[fd] != NULL)
		ret = find_newline(fd, line, st_arr, st_arr[fd]);//st_arrの中に\nがあれば、そこまでlineにくっつける。st_arrの\n以降は新しくst_arrにいれる。
	if (ret == 0)// if \n is not found by find_newline()
		ret = read_from_fd(fd, line, st_arr);
	return (ret);

	// error check
	// search \n from st_arr
	// if (\n wasn't found from st_arr)
	// while (buf_flag)
	//     read from fd to buf(BUFFER_SIZE bytes)
	//     search \n from buf
	//     if (\n was found from buf)
	//         buf_flag = 0;
	// *line = st_arr + buf + \0
	// set next st_arr

	//if (error)
	//	return (-1);
	//else if (\n was found)
	//	return (1);
	//else if (reached EOF)
	//	return (0);
}


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝

void	put_GNL(char *file, int (*f)(int, char **)){
	char *line;
	int fd;

	fd = open(file, O_RDONLY);
	// fd = open("test00.txt", O_RDONLY);

	int ret ,i = 0;

	while ((ret = f(fd, &line) > 0))
	{
		printf("line %2d, ret:%2d, %s\n", ++i, ret, line);
	}
	printf("line %2d, ret:%2d, %s\n", ++i, ret, line);
	close(fd);
}

#include <time.h>
int main(){

	// char *line;
	// int fd;
	// int ret;

	// fd = open("test00.txt", O_RDONLY);
	// while ((ret = get_next_line(fd, &line)) > 0)
	// {
	// 	printf("ret:%d, %s\n", ret, line);
	// }
	// printf("ret:%d, %s\n", ret, line);

	// close(fd);

	put_GNL("test00.txt", get_next_line);
	// put_GNL("test01.txt", get_next_line);
	// put_GNL("test02.txt", get_next_line);
	// put_GNL("test03.txt", get_next_line);

	// clock_t t1, t2;
	// char *line;
	// int fd;

	// fd = open("test03.txt", O_RDONLY);
	// t1 = clock();
	// get_next_line(fd, &line);
	// t2 = clock();
	// close(fd);
	// printf("time : %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}
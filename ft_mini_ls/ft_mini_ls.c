/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 23:36:16 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/03 23:07:30 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

t_filelist	**allocate_lst(DIR *dp, t_filelist **lst, int *len)//count_file
{									//↑このlstはリターンするわけだから、できたらこれなしで作りたい
	int i;
	struct dirent *dir;

	i = 0;
	while ((dir = readdir(dp)) != NULL)
		i++;
	free(lst);
	if (!(lst = (t_filelist **)malloc(sizeof(t_filelist *) * i)))
		return (NULL);////NULLでいいのかな？
	*len = i;
	return (lst);//できたらリターンするのはlstではなく、この関数内で作ったt_filelist **retみたいなやつを返したい
}

t_filelist	**get_fileinfo(DIR *dp2, t_filelist **lst)
{
	struct dirent	*dir2;
	int		i;

	i = 0;
	while ((dir2 = readdir(dp2)) != NULL)
	{
		lst[i] = make_filelist(dir2, ".");
		i++;
	}
	return (lst);
}

void	sort_filelist(int len, t_filelist **lst)
{
	int			i;
	t_filelist	*tmp;

	i = 0;
	while (i < len - 1)
	{
		if (lst[i]->modified_time > lst[i + 1]->modified_time)
		{
			tmp = lst[i];
			lst[i] = lst[i + 1];
			lst[i + 1] = tmp;
			i = 0;
		}
		else if (lst[i]->modified_time == lst[i + 1]->modified_time &&
				lst[i]->filename < lst[i + 1]->filename)
		{
			tmp = lst[i];
			lst[i] = lst[i + 1];
			lst[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	write_filename(t_filelist **lst, int len)
{
	int i;

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

int	main(int argc, char *argv[])
{
	DIR *dp;
	DIR *dp2;
	t_filelist	**lst;
	int len;

	(void)argv;
	if (argc != 1)
		return (-1);///error処理の関数とか呼び出す？
	if (!(dp = opendir(".")))
		return (-1);///error処理の関数とか呼び出す？
	if (!(lst = (t_filelist **)malloc(1)))
		return (-1);///error処理の関数とか呼び出す？
	lst = allocate_lst(dp, lst, &len);//count_file
	closedir(dp);
	if (!(dp2 = opendir(".")))
		return (-1);///error処理の関数とか呼び出す？
	get_fileinfo(dp2, lst);//lst[i]に1個ずつしまってはmodified_timeも取ってくる関数
	closedir(dp2);
	sort_filelist(len, lst);
	write_filename(lst, len);
	return (1);////
}

/*

lstの確保
それぞれに読み込む
並べ替え
ドット以外出力
＝＝ここまで終わった＝＝
諸々エラー処理

printf("lst[0] : modified_time: %ld name: %s\n", lst[0]->modified_time, lst[0]->filename);
printf("lst[1] : modified_time: %ld name: %s\n", lst[1]->modified_time, lst[1]->filename);
printf("lst[2] : modified_time: %ld name: %s\n", lst[2]->modified_time, lst[2]->filename);
printf("lst[3] : modified_time: %ld name: %s\n", lst[3]->modified_time, lst[3]->filename);
printf("lst[4] : modified_time: %ld name: %s\n", lst[4]->modified_time, lst[4]->filename);
printf("lst[5] : modified_time: %ld name: %s\n", lst[5]->modified_time, lst[5]->filename);
printf("lst[6] : modified_time: %ld name: %s\n", lst[6]->modified_time, lst[6]->filename);
printf("lst[7] : modified_time: %ld name: %s\n", lst[7]->modified_time, lst[7]->filename);
printf("lst[8] : modified_time: %ld name: %s\n", lst[8]->modified_time, lst[8]->filename);
printf("lst[9] : modified_time: %ld name: %s\n", lst[9]->modified_time, lst[9]->filename);
printf("lst[10]: modified_time: %ld name: %s\n", lst[10]->modified_time, lst[10]->filename);
printf("lst[11]: modified_time: %ld name: %s\n", lst[11]->modified_time, lst[11]->filename);
printf("lst[12]: modified_time: %ld name: %s\n", lst[12]->modified_time, lst[12]->filename);
printf("lst[13]: modified_time: %ld name: %s\n", lst[13]->modified_time, lst[13]->filename);
printf("lst[14]: modified_time: %ld name: %s\n", lst[14]->modified_time, lst[14]->filename);
printf("lst[15]: modified_time: %ld name: %s\n\n", lst[15]->modified_time, lst[15]->filename);
*/
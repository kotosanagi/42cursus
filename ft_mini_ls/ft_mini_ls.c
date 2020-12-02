/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 23:36:16 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/03 08:29:42 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>////
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct	s_filelist
{
		char	*filename;
		long	modified_time;
}		t_filelist;

long	get_modified_time(char *filename, char *path)
{
	struct stat	*buf;
	long		time;

	buf = (struct stat *)malloc(sizeof(struct stat));
	if (stat(filename, buf) == -1)
	{
		perror(path);
		return (-1);
	}
	else
		time = buf->st_mtime;//なんか編集時間ではなさげ、、、、
	free(buf);
	buf = NULL;
	return (time);
}

t_filelist	**allocate_lst(DIR *dp, t_filelist **lst, int *len)//count_file
{									//↑このlstはリターンするわけだから、できたらこれなしで作りたい
	int i;
	struct dirent *dir;

	i = 0;
	while ((dir = readdir(dp)) != NULL)
	{
		if (dir->d_ino == 0)///skip remove file???
			continue;
		// (void)printf("\n====debug zone====\n");
		// (void)printf("ino     : %llu\n", dir->d_ino);
		// (void)printf("seekoff : %llu\n", dir->d_seekoff);
		// (void)printf("reclen  : %hu\n", dir->d_reclen);
		// (void)printf("namlen  : %hu\n", dir->d_namlen);
		// (void)printf("type    : %hhu\n", dir->d_type);
		// (void)printf("name    : %s\n", dir->d_name);
		// (void)printf("========\n");
		i++;
	}
	free(lst);
	if (!(lst = (t_filelist **)malloc(sizeof(t_filelist *) * i)))
		return (NULL);////NULLでいいのかな？
	*len = i;
	return (lst);//できたらリターンするのはlstではなく、この関数内で作ったt_filelist **retみたいなやつを返したい
}


t_filelist	*make_filelist(struct dirent *dir2, char *path)
{
	t_filelist	*new;

	if(!(new = (t_filelist *)malloc(sizeof(t_filelist))))
		return (NULL);
	new->filename = dir2->d_name;
	new->modified_time = get_modified_time(new->filename, path);
	if (new->modified_time == -1)
	{
		perror(path);
		return (NULL);
	}
//printf("new->filename: %s\t", new->filename);
//printf("new->modified_time: %ld\n", new->modified_time);
	return (new);
}

t_filelist	**read_dir(DIR *dp2, t_filelist **lst)///readdirと紛らわしいから名前変える
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

// void	sort_time(t_filelist **lst, int len)//timeの情報を基にバブルソート
// {
// 	int i;




// }

int	main(int argc, char *argv[])
{
	DIR *dp;
	DIR *dp2;
	struct dirent *dir;// = NULL;///
	t_filelist	**lst;
	int len;

	(void)argv;

	if (argc != 1)
		return (-1);///error処理の関数とか呼び出す？
	if (!(dp = opendir(".")))
		return (-1);///error処理の関数とか呼び出す？
	dir = NULL;
	if (!(lst = (t_filelist **)malloc(1)))
		return (-1);///error処理の関数とか呼び出す？
	lst = allocate_lst(dp, lst, &len);//count_file
	closedir(dp);
	
	if (!(dp2 = opendir(".")))
		return (-1);///error処理の関数とか呼び出す？
	// i = 0;
	read_dir(dp2, lst);//lst[i]に1個ずつしまってはmodified_timeも取ってくる関数
	// sort_time(lst, len);// mmodified_timeをもとにdir_arrをバブルソートする関数();////並べ替え関数
	// ドットで始まるやつ以外を出力する関数();///
	// closedir(dp2);
printf("lst[0] : modified_time: %ld name: %s,\n", lst[0]->modified_time, lst[0]->filename);
printf("lst[1] : modified_time: %ld name: %s,\n", lst[1]->modified_time, lst[1]->filename);
printf("lst[2] : modified_time: %ld name: %s,\n", lst[2]->modified_time, lst[2]->filename);
printf("lst[3] : modified_time: %ld name: %s,\n", lst[3]->modified_time, lst[3]->filename);
printf("lst[4] : modified_time: %ld name: %s,\n", lst[5]->modified_time, lst[4]->filename);
printf("lst[5] : modified_time: %ld name: %s,\n", lst[6]->modified_time, lst[5]->filename);
printf("lst[6] : modified_time: %ld name: %s,\n", lst[7]->modified_time, lst[6]->filename);
printf("lst[7] : modified_time: %ld name: %s,\n", lst[8]->modified_time, lst[7]->filename);
printf("lst[8] : modified_time: %ld name: %s,\n", lst[9]->modified_time, lst[8]->filename);
printf("lst[9] : modified_time: %ld name: %s,\n", lst[10]->modified_time, lst[9]->filename);
printf("lst[10]: modified_time: %ld name: %s,\n", lst[11]->modified_time, lst[10]->filename);
// printf("lst[11]: modified_time: %ld name: %s,\n", lst[12]->modified_time, lst[11]->filename);



	return (1);////
}

/*

lstの確保
それぞれに読み込む
＝＝ここまで終わった＝＝
並べ替え
ドット以外出力
諸々エラー処理

*/
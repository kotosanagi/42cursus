#include "get_next_line.h"


int treat_eof(int *is_eof, char **line)
{
	*is_eof = 0;
	*line = (char *)malloc(1);
	*line[0] = '\0';
	return 0;
}

int treat_empty(char *st_arr, char **line)
{
	free(st_arr);
	st_arr = NULL;
	*line = (char *)malloc(1);
	*line[0] = '\0';
	return 0;
}

int treat_error(char *st_arr, char **line)
{
	free(st_arr);
	st_arr = NULL;
	*line = NULL;
	return -1;
}

int treat_end(char *st_arr, long long int start, long long int end, int *is_eof)
{
	free(st_arr);
	st_arr = NULL;
	if (start == end)
		*is_eof = 1;
	else 
		*is_eof = 0;
	return *is_eof;
}


int get_next_line(char **line)
{
	static char *st_arr;
	static long long int start;
	static long long int end;
	static int is_eof;

	int read_len;

	if (is_eof)
		return treat_eof(&is_eof, line);
	if (!st_arr)
	{
		if (!(st_arr = (char *)malloc(100000000000)))
			return -1;
		read_len = read(0, st_arr, 10000);
		if (!read_len)
			return treat_empty(st_arr, line);
		if (read_len < 0)
			return treat_error(st_arr, line);
		end = read_len;
		while ((read_len = read(0, st_arr+end, 10000)) > 0)
			end += read_len;
	}
	int len = 0;
	while (st_arr[start + len] != '\n' && start + len < end)
		len++;
	char *ret_arr;
	if (!(ret_arr = (char *)malloc(len + 1)))
		return treat_error(st_arr, line);
	int i = 0;
	while (st_arr[start + i] != '\n' && start + i < end)
	{
		ret_arr[i] = st_arr[start + i];
		i++;
	}
	ret_arr[i] ='\0';
	*line = ret_arr;
	start += (i + 1);
	if (start >= end)
		return treat_end(st_arr, start, end, &is_eof);
	return 1;
}
	








#ifdef TEST

#include <stdio.h>

int main(){
	int ret;
	char *line;

	while ((ret = get_next_line(&line)) > 0)
		printf("ret:%d, line:%s\n", ret, line);
	printf("ret:%d, line:%s\n", ret, line);
		
	return 0;
}	


#endif

#include <unistd.h>

int is_apper(char *s, int point)
{
	int i = 0;
	while (i < point)
	{
		if (s[i] == s[point])
			return 1;
		i++;
	}
	return 0;
}

int is_exist(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return 1;
		i++;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		write(1, "\n", 1);
		return 1;
	}
	int i = 0;
	while (argv[1][i])
	{
		if (!is_apper(argv[1], i) && is_exist(argv[2], argv[1][i]))
			write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return 1;
}


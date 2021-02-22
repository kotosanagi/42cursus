/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:09:32 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/10 14:40:49 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int i;
	int ret;

	if (s == NULL)
		return (0);
	ret = 0;
	i = 0;
	while (s[i])
	{
		if ((ret == 0) && (s[i] != c))
			ret++;
		else if ((s[i] != c) && (s[i - 1] == c))
			ret++;
		i++;
	}
	return (ret);
}

static int	word_len(char const *s, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] && (s[i] != c))
	{
		i++;
		len++;
	}
	return (len);
}

static char	**free_all(char **ret, int i)
{
	while (i > 0)
		free(ret[--i]);
	free(ret);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	int		words_count;
	int		i;
	int		j;

	words_count = count_words(s, c);
	if (!s || !(ret = (char **)malloc(sizeof(char *) * (words_count + 1))))
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		ret[i] = (char *)malloc(sizeof(char) * (word_len(s, c) + 1));
		if (ret[i] == NULL)
			return (free_all(ret, i));
		while (*s == c)
			s++;
		j = 0;
		while (*s && (*s != c))
			ret[i][j++] = *s++;
		ret[i][j] = '\0';
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

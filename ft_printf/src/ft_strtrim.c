/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:58:46 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/10 14:33:00 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_setchar(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (is_setchar((char)s1[start], set))
		start++;
	while (is_setchar((char)s1[end - 1], set) && (start < end))
		end--;
	ret = (char *)malloc(sizeof(char) * (end - start + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s1 + start, end - start + 1);
	return (ret);
}

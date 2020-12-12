/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:52:28 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/10 14:30:05 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ret;
	int		i;
	int		s_count;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	s_count = 0;
	while (s1[s_count])
		ret[i++] = s1[s_count++];
	s_count = 0;
	while (s2[s_count])
		ret[i++] = s2[s_count++];
	ret[i] = '\0';
	return (ret);
}

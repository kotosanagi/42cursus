/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:08:27 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/09 08:58:32 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*arr_s1;
	const unsigned char	*arr_s2;
	size_t				i;

	arr_s1 = (const unsigned char *)s1;
	arr_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (arr_s1[i] != arr_s2[i])
			return (arr_s1[i] - arr_s2[i]);
		i++;
	}
	return (0);
}

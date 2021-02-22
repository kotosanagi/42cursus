/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:08:29 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/06 07:09:25 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*arr_s;
	size_t				i;

	arr_s = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (arr_s[i] == (unsigned char)c)
			return ((void *)arr_s + i);
		i++;
	}
	return (NULL);
}

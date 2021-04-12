/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:08:31 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/06 11:31:07 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*arr_dst;
	const unsigned char	*arr_src;

	arr_dst = (unsigned char *)dst;
	arr_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		arr_dst[i] = arr_src[i];
		if (arr_src[i] == (unsigned char)c)
		{
			return (arr_dst + i + 1);
		}
		i++;
	}
	return (NULL);
}

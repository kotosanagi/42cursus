/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:08:25 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/06 11:27:13 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*arr_dst;
	const unsigned char	*arr_src;

	if (!dst && !src)
		return (NULL);
	arr_dst = (unsigned char *)dst;
	arr_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		arr_dst[i] = arr_src[i];
		i++;
	}
	return (dst);
}

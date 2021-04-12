/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:08:23 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/06 11:58:28 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*arr_dst;
	const unsigned char	*arr_src;

	if (!dst && !src)
		return (NULL);
	arr_dst = (unsigned char *)dst;
	arr_src = (const unsigned char *)src;
	if (arr_dst < arr_src)
	{
		i = 0;
		while (i < len)
		{
			arr_dst[i] = arr_src[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			arr_dst[len] = arr_src[len];
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 09:55:32 by skotoyor          #+#    #+#             */
/*   Updated: 2021/05/26 08:44:12 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	char	first;
	char	second;

	if ((unsigned char)c < 0x80)
		write(fd, &c, 1);
	else
	{
		first = ((((unsigned char)c & 0xc0) >> 6) | 0xc0);
		second = (((unsigned char)c & 0x3f) | 0x80);
		write(fd, &first, 1);
		write(fd, &second, 1);
	}
}

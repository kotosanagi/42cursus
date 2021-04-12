/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:25:09 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/06 17:07:06 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_positive_nbr(unsigned int num, int fd)
{
	if (num / 10 == 0)
	{
		ft_putchar_fd(num + '0', fd);
		return ;
	}
	ft_put_positive_nbr(num / 10, fd);
	ft_putchar_fd(num % 10 + '0', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int positive_num;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		positive_num = -n;
	}
	else
		positive_num = n;
	ft_put_positive_nbr(positive_num, fd);
}

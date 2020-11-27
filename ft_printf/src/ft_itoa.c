/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:30:20 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/09 18:27:36 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit(unsigned int n)
{
	int digit;

	digit = 1;
	if (n < 10)
		return (digit);
	while (n >= 10)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char		*ft_itoa(int n)
{
	unsigned int	digit;
	char			*ret;
	int				i;
	unsigned int	tmp;

	tmp = (n < 0) ? -n : n;
	digit = get_digit(tmp);
	ret = (char *)malloc(sizeof(char) * (((n < 0) ? 1 : 0) + digit + 1));
	if (ret == NULL)
		return (NULL);
	if (n < 0)
		ret[0] = '-';
	i = (n < 0) ? digit : digit - 1;
	while (tmp >= 10)
	{
		ret[i] = tmp % 10 + '0';
		tmp /= 10;
		i--;
	}
	ret[i] = tmp + '0';
	ret[(n < 0) ? digit + 1 : digit] = '\0';
	return (ret);
}

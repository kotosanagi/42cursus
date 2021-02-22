/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:34:29 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/06 15:53:55 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ispm(int c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int	ft_isspace(int c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static int	ft_isinlong(int pn, const char *str)
{
	int digit;

	digit = 0;
	while (ft_isdigit(str[digit]))
		digit++;
	if ((pn == 1) &&
	((digit > 19) ||
	((digit == 19) && (ft_strncmp(str, "9223372036854775807", 19) > 0))))
		return (-1);
	else if ((pn == -1) &&
	((digit > 19) ||
	((digit == 19) && (ft_strncmp(str, "9223372036854775808", 19) > 0))))
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	int res;
	int i;
	int pn;

	res = 0;
	i = 0;
	pn = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_ispm(str[i]))
	{
		if (str[i] == '-')
			pn = -1;
		i++;
	}
	if (ft_isinlong(pn, str + i) != 1)
		return (ft_isinlong(pn, str + i));
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (pn * res);
}

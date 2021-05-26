/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:30:20 by skotoyor          #+#    #+#             */
/*   Updated: 2021/05/27 08:42:18 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static void	ft_strrev(char *str)
{
	size_t	len;
	size_t	i;
	char	tmp;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		ng_flg;
	size_t	len;

	ng_flg = (n < 0);
	ret = ft_calloc(11 + ng_flg, sizeof(*ret));
	if (!ret)
		return (NULL);
	if (n == 0)
		ret[0] = '0';
	len = 0;
	while (n != 0)
	{
		ret[len++] = '0' + ft_abs(n % 10);
		n = (n / 10);
	}
	if (ng_flg)
		ret[len] = '-';
	ft_strrev(ret);
	return (ret);
}

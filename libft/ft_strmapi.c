/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 09:16:12 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/10 14:47:27 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < (unsigned int)ft_strlen(s))
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

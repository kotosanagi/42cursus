/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:16:29 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:17:22 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	put_conv_percent(t_content *content)
{
	int i;
	int put_len;

	i = 1;
	put_len = 0;
	if (content->flag[E_MINUS])
	{
		put_len += put_char_count('%');
		while (i++ < content->width)
			put_len += put_char_count(' ');
	}
	else if (content->flag[E_ZERO])
	{
		while (i++ < content->width)
			put_len += put_char_count('0');
		put_len += put_char_count('%');
	}
	else
	{
		while (i++ < content->width)
			put_len += put_char_count(' ');
		put_len += put_char_count('%');
	}
	return (put_len);
}

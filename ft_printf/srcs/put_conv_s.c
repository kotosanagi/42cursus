/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:57:06 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:15:26 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ret;

	i = 0;
	if (!(ret = (char *)malloc(n + 1)))
		return (NULL);
	while (i < n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	*set_str(char *tmp_str, t_content *content)
{
	char *str;

	if (tmp_str == NULL)
	{
		if (content->prec >= 0)
			str = ft_strndup("(null)", content->prec);
		else
			str = ft_strndup("(null)", 6);
	}
	else
	{
		if (content->prec >= 0)
			str = ft_strndup(tmp_str, content->prec);
		else
			str = tmp_str;
	}
	return (str);
}

static int	write_string(int s_len, t_content *content, char *str)
{
	int put_len;
	int i;

	put_len = 0;
	if (s_len >= content->width)
		put_len += write(1, str, s_len);
	else
	{
		i = 0;
		if (content->flag[E_MINUS])
		{
			put_len += write(1, str, s_len);
			while (i++ < content->width - s_len)
				put_len += put_char_count(' ');
		}
		else
		{
			while (i++ < content->width - s_len)
				put_len += put_char_count(' ');
			put_len += write(1, str, s_len);
		}
	}
	return (put_len);
}

int			put_conv_s(va_list *ap, t_content *content)
{
	int		s_len;
	char	*str;
	int		put_len;
	char	*tmp_str;

	tmp_str = va_arg(*ap, char*);
	put_len = 0;
	str = set_str(tmp_str, content);
	s_len = (int)ft_strlen(str);
	put_len += write_string(s_len, content, str);
	return (put_len);
}

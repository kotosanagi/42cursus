/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:27:11 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:43:28 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			put_char_count(char c)
{
	return (write(1, &c, 1));
}

int			put_notconv_count(char *str, int put_str_len)
{
	return (write(1, str, put_str_len));
}

int			putnbr_narr_uxxp(unsigned long long n,
char *n_arr, t_content *content)
{
	int ret_printed;

	ret_printed = 0;
	if (n / content->num_base == 0)
	{
		ret_printed += put_char_count(n_arr[n]);
		return (ret_printed);
	}
	ret_printed += putnbr_narr_uxxp(n / content->num_base, n_arr, content);
	ret_printed += put_char_count(n_arr[n % content->num_base]);
	return (ret_printed);
}

static int	put_space_normal_ptn(t_content *content, int offset)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	if (content->num_int < 0)
	{
		while (i++ < content->width - content->prec - 1 - offset)
			ret += put_char_count(' ');
	}
	else
	{
		while (i++ < content->width - content->prec - offset)
			ret += put_char_count(' ');
	}
	return (ret);
}

int			put_space(t_content *content, int offset)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	if (content->flag[E_ZERO] == true &&
	content->width > content->num_digits && content->prec < 0)
		return (ret);
	if (content->prec == 0 && content->num_int == 0)
	{
		while (i++ < content->width - offset)
			ret += put_char_count(' ');
	}
	else if (content->prec < content->num_digits)
	{
		while (i++ < content->width - content->num_digits - offset)
			ret += put_char_count(' ');
	}
	else
		ret += put_space_normal_ptn(content, offset);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:05:58 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:17:47 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	putnbr_numarr_di(long num, char *num_arr, t_content *content)
{
	int ret;

	ret = 0;
	if (num / (long)content->num_base == 0)
	{
		ret += put_char_count(num_arr[num]);
		return (ret);
	}
	ret += putnbr_numarr_di(num / (long)content->num_base, num_arr, content);
	ret += put_char_count(num_arr[num % (long)content->num_base]);
	return (ret);
}

static int	putnbr_di_minus_zero(t_content *content, char *num_arr)
{
	int		ret_printed;
	int		i;
	long	abs_num;
	int		abs_num_len;

	ret_printed = 0;
	i = 0;
	if (content->num_int < 0)
		ret_printed += put_char_count('-');
	abs_num_len = (content->num_int < 0) ?
	content->num_digits - 1 : content->num_digits;
	if (content->prec > abs_num_len)
	{
		while (i++ < content->prec - abs_num_len)
			ret_printed += put_char_count('0');
	}
	else if (content->flag[E_ZERO] == true && content->prec < 0)
	{
		while (i++ < content->width - content->num_digits)
			ret_printed += put_char_count('0');
	}
	abs_num = (content->num_int < 0) ?
	(long)content->num_int * -1 : (long)content->num_int;
	ret_printed += putnbr_numarr_di(abs_num, num_arr, content);
	return (ret_printed);
}

int			put_conv_di(va_list *ap, t_content *content)
{
	char	*num_arr;
	int		put_len;

	num_arr = get_base_info("0123456789", content);
	content->num_int = va_arg(*ap, int);
	content->num_digits = get_digits(content);
	put_len = 0;
	if (content->prec == 0 && content->num_int == 0)
		put_len += put_space(content, 0);
	else if (content->width <= content->num_digits)
		put_len += putnbr_di_minus_zero(content, "0123456789");
	else if (content->flag[E_MINUS])
	{
		put_len += putnbr_di_minus_zero(content, "0123456789");
		put_len += put_space(content, 0);
	}
	else
	{
		put_len += put_space(content, 0);
		put_len += putnbr_di_minus_zero(content, "0123456789");
	}
	return (put_len);
}

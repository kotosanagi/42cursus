/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:00:47 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:17:59 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	putnumber_prec_p(t_content *content, char *num_arr)
{
	unsigned long long	tmp_num;
	int					abs_num_len;
	int					ret_printed;

	ret_printed = content->num_digits;
	abs_num_len = content->num_digits;
	tmp_num = content->num_ptr;
	while (content->prec > abs_num_len)
	{
		write(1, "0", 1);
		ret_printed++;
		abs_num_len++;
	}
	putnbr_narr_uxxp(tmp_num, num_arr, content);
	return (ret_printed);
}

static void	write_address(int *put_len, t_content *content, char *base_str)
{
	if (content->prec == 0 && content->num_ptr == 0)
	{
		*put_len += put_space(content, 2);
		*put_len += write(1, "0x", 2);
	}
	else if (content->width <= content->num_digits)
	{
		*put_len += write(1, "0x", 2);
		*put_len += putnumber_prec_p(content, base_str);
	}
	else if (content->flag[E_MINUS])
	{
		*put_len += write(1, "0x", 2);
		*put_len += putnumber_prec_p(content, base_str);
		*put_len += put_space(content, 2);
	}
	else
	{
		*put_len += put_space(content, 2);
		*put_len += write(1, "0x", 2);
		*put_len += putnumber_prec_p(content, base_str);
	}
}

int			put_conv_p(va_list *ap, t_content *content, char *base_str)
{
	char	*num_arr;
	int		put_len;

	num_arr = get_base_info(base_str, content);
	content->num_ptr = (unsigned long long)(va_arg(*ap, void *));
	content->num_digits = get_digits(content);
	put_len = 0;
	write_address(&put_len, content, base_str);
	return (put_len);
}

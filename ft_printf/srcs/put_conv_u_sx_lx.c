/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_conv_u_sx_lx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:10:02 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:16:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	putnumber_prec_u_sx_lx(t_content *content, char *num_arr)
{
	unsigned long long	tmp_num;
	int					num_len;
	int					ret_printed;

	ret_printed = 0;
	num_len = content->num_digits;
	tmp_num = content->num_uint;
	if (content->flag[E_ZERO] && content->prec < 0)
	{
		while (content->width > num_len++)
			ret_printed += put_char_count('0');
	}
	else
	{
		while (content->prec > num_len++)
			ret_printed += put_char_count('0');
	}
	ret_printed += putnbr_narr_uxxp(tmp_num, num_arr, content);
	return (ret_printed);
}

int			put_conv_u_sx_lx(va_list *ap, t_content *content, char *base_str)
{
	char	*num_arr;
	int		put_len;

	num_arr = get_base_info(base_str, content);
	content->num_uint = va_arg(*ap, unsigned int);
	content->num_digits = get_digits(content);
	put_len = 0;
	if (content->prec == 0 && content->num_uint == 0)
		put_len += put_space(content, 0);
	else if (content->width <= content->num_digits)
		put_len += putnumber_prec_u_sx_lx(content, base_str);
	else if (content->flag[E_MINUS])
	{
		put_len += putnumber_prec_u_sx_lx(content, base_str);
		put_len += put_space(content, 0);
	}
	else
	{
		put_len += put_space(content, 0);
		put_len += putnumber_prec_u_sx_lx(content, base_str);
	}
	return (put_len);
}

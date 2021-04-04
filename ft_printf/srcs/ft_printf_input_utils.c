/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_input_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:08:07 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/19 17:45:06 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_flag(char c, t_content *content)
{
	if (c == '-')
	{
		content->flag[E_MINUS] = true;
		return (1);
	}
	if (content->width < 0 && content->prec < 0 && c == '0')
	{
		content->flag[E_ZERO] = true;
		return (1);
	}
	return (0);
}

int		is_width(char c, t_content *content, va_list *ap)
{
	int ret;
	int tmp;

	ret = 1;
	if (content->prec < 0 && c == '*')
	{
		tmp = va_arg(*ap, int);
		content->width = (tmp < 0) ? -tmp : tmp;
		if (tmp < 0)
		{
			content->flag[E_MINUS] = true;
			content->flag[E_ZERO] = false;
		}
	}
	else if (content->width < 0 && content->prec < 0 && '1' <= c && c <= '9')
		content->width = c - '0';
	else if ((content->prec < 0) && ('0' <= c && c <= '9'))
		content->width = ((content->width * 10) + (c - '0'));
	else
		ret = 0;
	return (ret);
}

int		is_prec(char c, t_content *content, va_list *ap)
{
	int ret;
	int tmp;

	ret = 1;
	if (content->prec < 0 && c == '.')
		content->prec = 0;
	else if (content->prec == 0 && c == '*')
	{
		tmp = va_arg(*ap, int);
		content->prec = (tmp < 0) ? -1 : tmp;
	}
	else if (content->prec >= 0 && '0' <= c && c <= '9')
		content->prec = (content->prec * 10) + (c - '0');
	else
		ret = 0;
	return (ret);
}

char	*get_base_info(char *base_num_ptn, t_content *content)
{
	int tmp_base;

	tmp_base = 0;
	while (base_num_ptn[tmp_base])
		tmp_base++;
	content->num_base = tmp_base;
	return (base_num_ptn);
}

int		get_digits(t_content *content)
{
	int			digits;
	long long	tmp_num;

	if (content->conv == E_INTEGER || content->conv == E_DECIMAL)
		tmp_num = (long long)content->num_int;
	else if (content->conv == E_POINTER)
		tmp_num = content->num_ptr;
	else
		tmp_num = (long long)content->num_uint;
	if (content->conv == E_INTEGER || content->conv == E_DECIMAL)
		tmp_num = (tmp_num < 0) ? -tmp_num : tmp_num;
	digits = 0;
	while (tmp_num >= (long long)content->num_base)
	{
		digits++;
		tmp_num /= content->num_base;
	}
	digits++;
	if (content->num_int < 0)
		digits++;
	return (digits);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:08:07 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/08 07:34:22 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_char_count(char c, int *printed_len)
{
	write(1, &c, 1);
	*printed_len += 1;
}

void	put_notconv_count(char *str, int i, int *printed_len)
{
	write(1, str, i);
	*printed_len += i;
}

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
	if (content->prec < 0 && c == '*')//'*'がきたら対応したつもり
	{
		tmp = va_arg(*ap, int);
		content->width = (tmp < 0) ? -tmp : tmp;
		if (tmp < 0)
			content->flag[E_MINUS] = true;
	}
	else if (content->width < 0 && (content->prec < 0) && ('1' <= c && c <= '9'))//widthがまだデフォかつ、precがデフォかつ、0以外の数字
		content->width = c - '0';
	else if ((content->prec < 0) && ('0' <= c && c <= '9'))//precがデフォかつ、数字
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
	//とりあえず.がきたら、precは0にして良い。-とかはあとで考える。
	if (content->prec < 0 && c == '.')
		content->prec = 0;
	else if (content->prec == 0 && c == '*')
	{
		tmp = va_arg(*ap, int);
		content->prec = (tmp < 0) ? -1 : tmp;// tmpが負なら-1のまま
	}
	else if (content->prec >= 0 && '0' <= c && c <= '9')
		content->prec = (content->prec * 10) + (c - '0');
	else
		ret = 0;
	return (ret);
}

int		is_conversion(char c, t_content *content)
{
	if (c == 'c')
		content->conv = E_CHAR;
	else if (c == 's')
		content->conv = E_STRING;
	else if (c == 'p')
		content->conv = E_POINTER;
	else if (c == 'd')
		content->conv = E_DECIMAL;
	else if (c == 'i')
		content->conv = E_INTEGER;
	else if (c == 'u')
		content->conv = E_UNSIGNED;
	else if (c == 'x')
		content->conv = E_XDECIMAL_SMALL;
	else if (c == 'X')
		content->conv = E_XDECIMAL_LARGE;
	else if (c == '%')
		content->conv = E_PERCENT;
	return (content->conv);
}

void	init_content(t_content *content)
{
	content->flag[E_MINUS] = false;
	content->flag[E_ZERO] = false;
	content->width = -1;
	content->prec = -1;
	content->conv = E_NOT_CONV;
	content->num_int = 0;
	content->num_digits = 0;
	content->num_base = 0;
}

void	put_conv_percent(t_content *content, int *printed_len)
{
	int i;

	i = 1;
	if (content->flag[E_MINUS])//左寄せ空白埋め
	{
		write(1, "%%", 1);
		while (i++ < content->width)
			write(1, " ", 1);
	}
	else if (content->flag[E_ZERO])//右寄せゼロ埋め
	{
		while (i++ < content->width)
			write(1, "0", 1);
		write(1, "%%", 1);
	}
	else//右寄せ空白埋め
	{
		while (i++ < content->width)
			write(1, " ", 1);
		write(1, "%%", 1);
	}
	if (content->width <= 1)
		*printed_len += 1;
	else
		*printed_len += content->width;
}

void	put_conv_c(va_list *ap, t_content *content, int *printed_len)
{
	int i;
	char c;

	i = 1;
	c = (char)va_arg(*ap, int);
	if (content->flag[E_MINUS])//左寄せ空白埋め
	{
		write(1, &c, 1);
		while (i++ < content->width)
			write(1, " ", 1);
	}
	else//右寄せ空白埋め
	{
		while (i++ < content->width)
			write(1, " ", 1);
		write(1, &c, 1);
	}
	
	if (content->width <= 1)
		*printed_len += 1;
	else
		*printed_len += content->width;
}

char *ft_strndup(char *str, int n)
{
	int i;
	char *ret;

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

void	put_conv_s(va_list *ap, t_content *content, int *printed_len)
{
	int s_len;
	char *str;
	int i;

	if (content->prec >= 0)
		str = ft_strndup(va_arg(*ap, char*), content->prec);
	else
		str = va_arg(*ap, char*);
	s_len = (int)ft_strlen(str);
	if (s_len >= content->width)
	{
		write(1, str, s_len);
		*printed_len += s_len;
	}
	else
	{
		i = 0;
		if (content->flag[E_MINUS])
		{
			write(1, str, s_len);
			while (i++ < content->width - s_len)
				write(1, " ", 1);
		}
		else
		{
			while (i++ < content->width - s_len)
				write(1, " ", 1);
			write(1, str, s_len);
		}
		*printed_len += content->width;
	}
}

char	*get_base_info(char *base_num_ptn, t_content *content)//桁数
{
	int tmp_base;

	tmp_base = 0;
	while (base_num_ptn[tmp_base])
		tmp_base++;
	content->num_base = tmp_base;
	return (base_num_ptn);
}


// void	put_num_cnt(char *num_arr, t_content *content, int *printed_len)
// {
	
// }

int		get_digits(t_content *content)//数字部分だけ考慮する
{
	int digits;
	long tmp_num;

	tmp_num = (long)content->num_int;
	tmp_num = (tmp_num < 0) ? -tmp_num : tmp_num;
	digits = 0;
	while (tmp_num > content->num_base)
	{
		digits++;
		tmp_num /= content->num_base;
	}
	digits++;
	return (digits);
}

void	put_conv_di(va_list *ap, t_content *content, int *printed_len)
{//構造体の情報を基に10進数に変換して、出力した文字数をprinted_lenに足す
//
//
	char *num_arr;

	num_arr = get_base_info("0123456789", content);
	content->num_int = va_arg(*ap, int);
	content->num_digits = get_digits(content);

	// put_num_cnt(num_arr, content, printed_len);
	(void)printed_len;
}

void	put_string_or_nbr(va_list *ap, t_content *content, int *printed_len)
{
	if (content->conv == E_CHAR)
		put_conv_c(ap, content, printed_len);
	else if (content->conv == E_STRING)
		put_conv_s(ap, content, printed_len);
	// if (content->conv == E_POINTER)

	// else if ((content->conv == E_DECIMAL) || (content->conv == E_INTEGER))
	// 	put_conv_di(ap, content, printed_len);
	// if (content->conv == E_UNSIGNED)

	// if (content->conv == E_XDECIMAL_SMALL)

	// if (content->conv == E_XDECIMAL_LARGE)

	else if (content->conv == E_PERCENT)
		put_conv_percent(content, printed_len);
}




int main(){
	char *str;
	t_content content;

	init_content(&content);

	str = get_base_info("0123456789", &content);
	printf("%s\n",str);
	printf("%d\n", content.num_base);

	content.num_int = 0;
	int digits = get_digits(&content);
	printf("%d\n", digits);
}

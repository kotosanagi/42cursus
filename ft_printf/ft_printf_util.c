/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:08:07 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/12 08:44:38 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int		put_char_count(char c, int *printed_len)
int		put_char_count(char c)
{
	return (write(1, &c, 1));
	// *printed_len += 1;
}

// void	put_notconv_count(char *str, int put_str_len, int *printed_len)
int	put_notconv_count(char *str, int put_str_len)
{
	return (write(1, str, put_str_len));
	// *printed_len += put_str_len;
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
	content->num_uint = 0;////////////////////////////////////////////////
	content->num_digits = 0;
	content->num_base = 0;
}

// void	put_conv_percent(t_content *content, int *printed_len)
int		put_conv_percent(t_content *content)
{
	int i;
	int put_len;

	i = 1;
	put_len = 0;
	if (content->flag[E_MINUS])//左寄せ空白埋め
	{
		put_len += put_char_count('%');
		// write(1, "%%", 1);
		while (i++ < content->width)
			put_len += put_char_count(' ');
			// write(1, " ", 1);
	}
	else if (content->flag[E_ZERO])//右寄せゼロ埋め
	{
		while (i++ < content->width)
			put_len += put_char_count('0');
			// write(1, "0", 1);
		put_len += put_char_count('%');
		// write(1, "%%", 1);
	}
	else//右寄せ空白埋め
	{
		while (i++ < content->width)
			put_len += put_char_count(' ');
			// write(1, " ", 1);
		put_len += put_char_count('%');
		// write(1, "%%", 1);
	}
	if (content->width <= 1)
		put_len++;
		// *printed_len += 1;
	// else
	// 	*printed_len += content->width;
	return (put_len);
}

// void	put_conv_c(va_list *ap, t_content *content, int *printed_len)
int		put_conv_c(va_list *ap, t_content *content)
{
	int i;
	char c;
	int put_len;

	i = 1;
	put_len = 0;
	c = (char)va_arg(*ap, int);
	if (content->flag[E_MINUS])//左寄せ空白埋め
	{
		// write(1, &c, 1);
		put_len += put_char_count(c);
		while (i++ < content->width)
			put_len += put_char_count(' ');
			// write(1, " ", 1);
	}
	else//右寄せ空白埋め
	{
		while (i++ < content->width)
			put_len += put_char_count(' ');
			// write(1, " ", 1);
		put_len += put_char_count(c);
		// write(1, &c, 1);
	}
	
	// if (content->width <= 1)
	// 	*printed_len += 1;
	// else
	// 	*printed_len += content->width;
	return (put_len);
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

// void	put_conv_s(va_list *ap, t_content *content, int *printed_len)
int		put_conv_s(va_list *ap, t_content *content)
{
	int s_len;
	char *str;
	int i;
	int put_len;

	put_len = 0;
	if (content->prec >= 0)
		str = ft_strndup(va_arg(*ap, char*), content->prec);
	else
		str = va_arg(*ap, char*);
	s_len = (int)ft_strlen(str);
	if (s_len >= content->width)
	{
		write(1, str, s_len);
		put_len += s_len;
	}
	else
	{
		i = 0;
		if (content->flag[E_MINUS])
		{
			write(1, str, s_len);
			put_len += s_len;
			while (i++ < content->width - s_len)
				put_len += put_char_count(' ');
				// write(1, " ", 1);
		}
		else
		{
			while (i++ < content->width - s_len)
				put_len += put_char_count(' ');
				// write(1, " ", 1);
			write(1, str, s_len);
			put_len += s_len;
		}
		// *printed_len += content->width;
	}
	return (put_len);
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

void	putnbr_numarr_di(int num, char *num_arr, t_content *content)
{
	if (num / content->num_base == 0)
	{
		write(1, &num_arr[num], 1);
		return ;
	}
	putnbr_numarr_di(num / content->num_base, num_arr, content);
	write(1, &num_arr[num % content->num_base], 1);
}

void	putnbr_numarr_u(unsigned int num, char *num_arr, t_content *content)
{
	if (num / content->num_base == 0)
	{
		write(1, &num_arr[num], 1);
		return ;
	}
	putnbr_numarr_u(num / content->num_base, num_arr, content);
	write(1, &num_arr[num % content->num_base], 1);
}

// int		putnumber_prec_di(t_content *content)//precを考慮した、いい感じのputnumber(とりま10進数で)
int		putnumber_prec_di(t_content *content, char *num_arr)//precを考慮した、いい感じのputnumber
{//必要な要素 num_int, prec, 
	int tmp_num;
	int abs_num_len;
	int ret_printed;

	ret_printed = content->num_digits;
	// abs_num_len = (content->num_int < 0) ? content->num_digits - 1 : content->num_digits;
	if (content->num_int < 0)
	{
		write(1, "-", 1);
		abs_num_len = content->num_digits - 1;
		tmp_num = -content->num_int;
	}
	else
	{
		abs_num_len = content->num_digits;
		tmp_num = content->num_int;
	}
	while (content->prec > abs_num_len)//0ume 
	{
		write(1, "0", 1);
		ret_printed++;
		abs_num_len++;
	}
	putnbr_numarr_di(tmp_num, num_arr, content);
	return (ret_printed);
}

int		putnumber_prec_u(t_content *content, char *num_arr)//precを考慮した、いい感じのputnumber
{//必要な要素 num_int, prec, 
	unsigned int tmp_num;
	int abs_num_len;
	int ret_printed;

	ret_printed = content->num_digits;
	abs_num_len = content->num_digits;
	tmp_num = content->num_uint;
	while (content->prec > abs_num_len)//0ume 
	{
		write(1, "0", 1);
		ret_printed++;
		abs_num_len++;
	}
	putnbr_numarr_u(tmp_num, num_arr, content);
	return (ret_printed);
}


int		get_digits(t_content *content)//数字部分だけ考慮する
{
	int digits;
	long tmp_num;

	if (content->conv == E_INTEGER || content->conv == E_DECIMAL)
		tmp_num = (long)content->num_int;
	else
		tmp_num = (long)content->num_uint;
	tmp_num = (tmp_num < 0) ? -tmp_num : tmp_num;
	digits = 0;
	while (tmp_num > (long)content->num_base)
	{
		digits++;
		tmp_num /= content->num_base;
	}
	digits++;
	if (content->num_int < 0)
		digits++;
	return (digits);
}

int		put_space(t_content *content)
{
	int num_space;
	int i;
	int put_len;

	if (content->prec > content->num_digits)
	{
		num_space = content->width - content->prec;
		if (content->num_int < 0)
			num_space--;
	}
	// else if (content->prec == 0)///3.0d  0対応
	else if (content->prec == 0 && content->num_int == 0 && content->num_uint == 0)///3.0d  0対応
		num_space = content->width;///
	else
		num_space = content->width - content->num_digits;
	i = 0;
	put_len = 0;
	// if (content->prec < 0)//precが指定されていないのであれば0埋め//4d 12対応。ダメならこれに戻す
	// if (content->prec < 0 && content->width <= content->num_digits)//precが指定されていないのであれば0埋め
	if (content->prec < 0 && ((content->width <= content->num_digits) || (content->flag[E_ZERO])))//precが指定されていないのであれば0埋め
	{//                                                                   ^ここ 08d 42対応//ダメなら消す
		while (i++ < num_space)
			put_len += put_char_count('0');
			// write(1, "0", 1);
	}
	// else if (content->prec < 0 && content->flag[E_ZERO])//08d 42対応//必要なさそうなので削除予定
	// {
	// 	while (i++ < num_space)
	// 		write(1, "0", 1);
	// }
	else//precが指定されているのであれば空白埋め
	{
		while (i++ < num_space)
			put_len += put_char_count(' ');
			// write(1, " ", 1);
	}
	return (put_len);
}

// void	put_conv_di(va_list *ap, t_content *content, int *printed_len)
int		put_conv_di(va_list *ap, t_content *content)
{//構造体の情報を基に10進数に変換して、出力した文字数をprinted_lenに足す
	char *num_arr;
	// int tmp_printed_len;
	int put_len;

	num_arr = get_base_info("0123456789", content);
	content->num_int = va_arg(*ap, int);
	content->num_digits = get_digits(content);
	put_len = 0;
	if (content->prec == 0 && content->num_int == 0)
		put_len += put_space(content);		// return ;
	else if (content->width <= content->num_digits)
		put_len += putnumber_prec_di(content, "0123456789");//put_nbr()を、prec的な表現で表す感じ
	else if (content->flag[E_MINUS])//widthの方が大きくて左寄せ
	{
		put_len += putnumber_prec_di(content, "0123456789");//put_nbr()を、prec的な表現で表す感じ
		put_len += put_space(content);
	}
	else
	{
		put_len += put_space(content);
		put_len += putnumber_prec_di(content, "0123456789");//put_nbr()を、prec的な表現で表す感じ
	}
	return (put_len);
	// *printed_len += tmp_printed_len;
}

int		put_conv_u_sx_lx(va_list *ap, t_content *content, char *base_str)
{//構造体の情報を基に10進数に変換して、出力した文字数をprinted_lenに足す
	char *num_arr;
	// int tmp_printed_len;
	int put_len;

	num_arr = get_base_info(base_str, content);
	content->num_uint = va_arg(*ap, unsigned int);//////////////////////////////////////////
	content->num_digits = get_digits(content);
	put_len = 0;
	if (content->prec == 0 && content->num_uint == 0)
		put_len += put_space(content);		// return ;
	else if (content->width <= content->num_digits)
		put_len += putnumber_prec_u(content, base_str);//put_nbr()を、prec的な表現で表す感じ
	else if (content->flag[E_MINUS])//widthの方が大きくて左寄せ
	{
		put_len += putnumber_prec_u(content, base_str);//put_nbr()を、prec的な表現で表す感じ
		put_len += put_space(content);
	}
	else
	{
		put_len += put_space(content);
		put_len += putnumber_prec_u(content, base_str);//put_nbr()を、prec的な表現で表す感じ
	}
	return (put_len);
	// *printed_len += tmp_printed_len;
}



// void	put_string_or_nbr(va_list *ap, t_content *content, int *printed_len)
int		put_string_or_nbr(va_list *ap, t_content *content)
{
	int put_len;

	put_len = 0;
	if (content->conv == E_CHAR)
		put_len += put_conv_c(ap, content);// put_len += put_conv_c(ap, content, printed_len);
	else if (content->conv == E_STRING)
		put_len += put_conv_s(ap, content);//put_conv_s(ap, content, printed_len);
	// if (content->conv == E_POINTER)

	else if ((content->conv == E_DECIMAL) || (content->conv == E_INTEGER))
		put_len += put_conv_di(ap, content);// put_conv_di(ap, content, printed_len);
	else if (content->conv == E_UNSIGNED)
		put_len += put_conv_u_sx_lx(ap, content, "0123456789");
	else if (content->conv == E_XDECIMAL_SMALL)
		put_len += put_conv_u_sx_lx(ap, content, "0123456789abcdef");
	else if (content->conv == E_XDECIMAL_LARGE)
		put_len += put_conv_u_sx_lx(ap, content, "0123456789ABCDEF");

	else if (content->conv == E_PERCENT)
		put_len += put_conv_percent(content);//put_conv_percent(content, printed_len);
	return (put_len);
}




// int main(){
// 	// char *str;
// 	t_content content;

// 	init_content(&content);

// 	// str = get_base_info("0123456789", &content);
// 	// printf("%s\n",str);
// 	// printf("%d\n", content.num_base);

// 	// content.num_int = 0;
// 	// int digits = get_digits(&content);
// 	// printf("%d\n", digits);



// 	ft_printf("[%08d]\n", 52);
// 	printf("[%08d]\n", 52);

// 	ft_printf("[%08.5d]\n", 52);
// 	printf("[%08.5d]\n", 52);
// 	// printf("\n\n\n");
// 	// putnumber_prec_di(&content);
// }

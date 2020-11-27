/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:10:08 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/27 22:07:08 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



int		process_percent(char *str, int *printed_len)
{
	(void)printed_len;

	int i;
	t_content	content;

	init_content(&content);

	i = 1;
	while (str[i])
	{
		// if (is_flag(str[i], content))//-があったら0は無視する
		// 	;//????
		// else if (is_width(str[i], content))
		// 	;//????
		// else if (is_prec(str[i], content))
		// 	;//????
		if (is_conversion(str[i], &content))////else if
			break;//????
		else
			break;////?????
		i++;
	}
	// if (content->conv == E_NOT_CONV)
	// 	put_something();////
	// else
	// 	put_string_or_nbr();////
	// *printed_len += len_put_something();

printf("\n====content debug===\n");
	printf("flag[0]:%d\n", content.flag[0]);
	printf("flag[1]:%d\n", content.flag[1]);
	printf("width  :%d\n", content.width);
	printf("prec   :%d\n", content.prec);
	printf("conv   :%d\n", content.conv);
printf("====================\n");
	return (i);
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	int printed_len;
	int i;

	char *tmp_format;
	tmp_format = (char *)format;

	va_start(ap, format);
	printed_len = 0;
	i = 0;
	while (format[i])
	{
		// if (format[i] != '%' && format[i] != '\0')
		if (format[i] != '%')
		{
			put_char_count(format[i], &printed_len);
			i++;
		}
		else
			i += process_percent(tmp_format + i, &printed_len);//処理が終わった時にiを足す作業必要
	}
	va_end(ap);
	return (printed_len);
}

int main () {///
	int x;
	x = ft_printf("koto%s", 42);//process_percentにて、iを進める処理が必要

	printf("\nft_printf's ret : %d\n", x);
}


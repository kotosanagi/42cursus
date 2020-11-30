/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:10:08 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/30 22:16:48 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		process_percent(va_list *ap, char *str, int *printed_len)
{
	(void)ap;
	(void)printed_len;
	int i;
	t_content	content;

	init_content(&content);
	i = 1;
	while (str[i])
	{
		if (is_flag(str[i], &content))//-があったら0は無視する
			;
		else if (is_width(str[i], &content, ap))
			;
		else if (is_prec(str[i], &content, ap))//精度が0かつ「0」を出力の場合は、空文字列が出力される。
			;//????
		else if (is_conversion(str[i], &content))
		{
			i++;
			break ;//????
		}
		else
			break ;////?????
		i++;
	}

	// if (content.conv == E_NOT_CONV)
	// 	put_notconv_count(str, i, printed_len);//////len_put_somethingは、strをi文字分出力かな。。。
	// else
	// {
	// 	put_string_or_nbr(ap, &content, printed_len);////contentを元に、va_argを吐き出すって感じかな。。。
	// // *printed_len += len_put_something();//content->conv見て,数えるの判断かな。。。
	// }
printf("\n====content debug===\n");
	printf("flag[E_MINUS] : %2d\n", content.flag[E_MINUS]);
	printf("flag[E_ZERO]  : %2d\n", content.flag[E_ZERO]);
	printf("width         : %2d\n", content.width);
	printf("prec          : %2d\n", content.prec);
	printf("conv          : %2d\n", content.conv);
printf("i:%d\n",i);
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
		if (format[i] == '%')
			i += process_percent(&ap, tmp_format + i, &printed_len);//処理が終わった時にiを足す作業必要
		else
		{
			put_char_count(format[i], &printed_len);
			i++;
		}
	}
	va_end(ap);
	return (printed_len);
}

int main () {///

	int x, y;
	// x = printf("koto%-23mocomoco", 52);
	// printf("\n\nft_printf's ret : %d\n\n", x);
	// y = ft_printf("koto%-23mocomoco", 52);
	// printf("\n\nft_printf's ret : %d\n\n", y);

	// x = ft_printf("koto%*%mocomoco", 4, 52);
	// printf("\n\nft_printf's ret : %d\n\n", x);
	// y = printf("koto%*dmocomoco", 4, 52);
	// printf("\n\nft_printf's ret : %d\n\n", y);
	
	
	// x = ft_printf("koto%-10.*dmocomoco", 5, 42);
	// printf("\n\nft_printf's ret : %d\n\n\n\n", x);
	// y = printf("koto%-10.*dmocomoco", 5, 42);
	// printf("\n\nft_printf's ret : %d\n\n", y);
	
	// x = ft_printf("koto%*.*dmocomoco",-4, 10, 42);
	// printf("\n\nft_printf's ret : %d\n\n\n\n", x);
	// y = printf("koto%*.*dmocomoco",-4, 10, 42);
	// printf("\n\nft_printf's ret : %d\n\n", y);

	// x = ft_printf("koto%-23%mocomoco");
	// printf("\n\nft_printf's ret : %d\n\n\n\n", x);
	// y = printf("koto%-23%mocomoco");
	// printf("\n\nft_printf's ret : %d\n\n", y);

	// x = ft_printf("koto%5.*dmocomoco", -78, 52);
	// printf("\n\nft_printf's ret : %d\n\n\n\n", x);
	// y = printf("koto%5.*dmocomoco",-78, 52);
	// printf("\n\nft_printf's ret : %d\n\n", y);

	// x = ft_printf("%.0d", 0);
	// printf("\n\nft_printf's ret : %d\n\n\n\n", x);
	// y = printf("%.0d", 0);
	// printf("\n\nft_printf's ret : %d\n\n", y);

	x = ft_printf("%.0d", 0);
	printf("\n\nft_printf's ret : %d\n\n\n\n", x);
	y = printf("%.0d", 0);
	printf("\n\nft_printf's ret : %d\n\n", y);

}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:10:08 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/10 15:28:02 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		process_percent(va_list *ap, char *str, int *printed_len)
{
	// (void)ap;
	// (void)printed_len;
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

	if (content.conv == E_NOT_CONV)// put_notconv_count(str, i, printed_len);//////convが指定されなかった時、そのまま出力する。printed_lenに出力した文字数を足す
		*printed_len += put_notconv_count(str, i);//////convが指定されなかった時、そのまま出力する。printed_lenに出力した文字数を足す
	else
		*printed_len += put_string_or_nbr(ap, &content);////contentを元に、va_argを吐き出す。printed_lenに出力した文字数を足す
		// put_string_or_nbr(ap, &content, printed_len);////contentを元に、va_argを吐き出す。printed_lenに出力した文字数を足す
// printf("\n====content debug===\n");
// 	printf("flag[E_MINUS] : %2d\n", content.flag[E_MINUS]);
// 	printf("flag[E_ZERO]  : %2d\n", content.flag[E_ZERO]);
// 	printf("width         : %2d\n", content.width);
// 	printf("prec          : %2d\n", content.prec);
// 	printf("conv          : %2d\n", content.conv);
// 	printf("num_int       : %2d\n", content.num_int);
// 	printf("num_digits    : %2d\n", content.num_digits);
// 	printf("num_base      : %2d\n", content.num_base);
// printf("i:%d\n",i);
// printf("====================\n");
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
		// if (format[i] != '%' && format[i] != '\0')//このコメントアウト、覚えてない。。。。
		if (format[i] == '%')
			i += process_percent(&ap, tmp_format + i, &printed_len);//処理が終わった時にiを足す作業必要
		else
		{
			// put_char_count(format[i], &printed_len);
			printed_len += put_char_count(format[i]);
			i++;
		}
	}
	va_end(ap);
	return (printed_len);
}




int main () {///

	int x, y;
// printf("========  c  =======\n\n");
	
// 	printf("%%c 'c'\n");
// 	x = ft_printf("ft:[%c]", 'c');
// 	printf("\n");
// 	y = printf("og:[%c]", 'c');
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);

// 	printf("%%4c 'c'\n");
// 	x = ft_printf("ft:[%4c]", 'c');
// 	printf("\n");
// 	y = printf("og:[%4c]", 'c');
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);

// 	printf("%%-3c 'c'\n");
// 	x = ft_printf("ft:[%-3c]", 'c');
// 	printf("\n");
// 	y = printf("og:[%-3c]", 'c');
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);

	// printf("%%0c 'c'\n");
	// x = ft_printf("ft:[%0c]", 'c');
	// printf("\n");
	// y = printf("og:[%0c]", 'c');//そもそもやっちゃダメっぽい
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("%%.0c 'c'\n");
	// x = ft_printf("ft:[%.0c]", 'c');
	// printf("\n");
	// y = printf("og:[%.0c]", 'c');//そもそもやっちゃダメっぽい
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("%%05c 'c'\n");
	// x = ft_printf("ft:[%05c]", 'c');
	// printf("\n");
	// y = printf("og:[%05c]", 'c');//そもそもやっちゃダメっぽい
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);


// printf("========  not_conv  =======\n\n");


// 	x = ft_printf("ft:[koto%*dmocomoco]", 4, 52);
// 	printf("\n");
// 	y = printf("og:[koto%*dmocomoco]", 4, 52);
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);
	
// 	x = ft_printf("ft:[koto%-10.*dmocomoco]", 5, 42);
// 	printf("\n");
// 	y = printf("og:[koto%-10.*dmocomoco]", 5, 42);
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);
	
// 	x = ft_printf("ft:[koto%*.*dmocomoco]",-4, 10, 42);
// 	printf("\n");
// 	y = printf("og:[koto%*.*dmocomoco]",-4, 10, 42);
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);


	// x = printf("koto%-23mocomoco", 52);//そもそもやっちゃダメっぽい
	// printf("\n");
	// y = ft_printf("koto%-23mocomoco", 52);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);


// printf("========  percent?  =======\n\n");

// 	x = ft_printf("ft:[koto%-23%mocomoco]");
// 	printf("\n");
// 	y = printf("og:[koto%-23%mocomoco]");
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);


// printf("========  ???  =======\n\n");

// 	x = ft_printf("ft:[koto%5.*dmocomoco]", -78, 52);
// 	printf("\n");
// 	y = printf("og:[koto%5.*dmocomoco]",-78, 52);
// 	printf("\nft ret : %d\n", x-5);
// 	printf("og ret : %d\n\n", y-5);



	// x = ft_printf("ft:[%03.2%]");
	// printf("\n");
	// y = printf("og:[%03.2%]");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%-3%]");
	// printf("\n");
	// y = printf("og:[%-3%]");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%0000010.2%]");
	// printf("\n");
	// y = printf("og:[%0000010.2%]");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%-4%]");
	// printf("\n");
	// y = printf("og:[%-4%]");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%-4%]");
	// printf("\n");
	// y = printf("og:[%-4%]");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%---0004.2%]");
	// printf("\n");
	// y = printf("og:[%---0004.2%]");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%-4c]", 'x');
	// printf("\n");
	// y = printf("og:[%-4c]", 'x');
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);


	// x = ft_printf("ft:[%03%]");
	// printf("\n");
	// y = printf("og:[%03s]","ko");//やっちゃダメっぽい
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("========  string  =======\n\n");

	// x = ft_printf("ft:[%-6.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-6.s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);
	
	// x = ft_printf("ft:[%-6.3s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-6.3s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);
	
	// x = ft_printf("ft:[%4.3s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4.3s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%3.0s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%3.0s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// x = ft_printf("ft:[%20.0s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%20.0s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);



	printf("======di=======\n");


	// printf("*d  3 40\n");
	// x = ft_printf("ft:[%*d]",3, 40);
	// printf("\n");
	// y = printf("og:[%*d]",3, 40);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".*d  3 40\n");
	// x = ft_printf("ft:[%.*d]",3, 40);
	// printf("\n");
	// y = printf("og:[%.*d]",3, 40);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("*.*d 4 3 40\n");
	// x = ft_printf("ft:[%*.*d]", 4, 3, 40);
	// printf("\n");
	// y = printf("og:[%*.*d]", 4, 3, 40);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("d 12345678\n");
	// x = ft_printf("ft:[%d]", 12345678);
	// printf("\n");
	// y = printf("og:[%d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("4d 12345678\n");
	// x = ft_printf("ft:[%4d]", 12345678);
	// printf("\n");
	// y = printf("og:[%4d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("4d 12\n");
	// x = ft_printf("ft:[%4d]", 12);
	// printf("\n");
	// y = printf("og:[%4d]", 12);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("-4d 12\n");
	// x = ft_printf("ft:[%-4d]", 12);
	// printf("\n");
	// y = printf("og:[%-4d]", 12);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.15d 12\n");
	// x = ft_printf("ft:[%4.15d]", 12);
	// printf("\n");
	// y = printf("og:[%4.15d]", 12);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.d 12345678\n");
	// x = ft_printf("ft:[%4.d]", 12345678);
	// printf("\n");
	// y = printf("og:[%4.d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.10d 12345678\n");
	// x = ft_printf("ft:[%4.10d]", 12345678);
	// printf("\n");
	// y = printf("og:[%4.10d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);


	// printf("4.0d 12345678\n");
	// x = ft_printf("ft:[%4.0d]", 12345678);
	// printf("\n");
	// y = printf("og:[%4.0d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.9d 12345678\n");
	// x = ft_printf("ft:[%4.9d]", 12345678);
	// printf("\n");
	// y = printf("og:[%4.9d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("02d 12345678\n");
	// x = ft_printf("ft:[%02d]", 12345678);
	// printf("\n");
	// y = printf("og:[%02d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("-4d 12345678\n");
	// x = ft_printf("ft:[%-4d]", 12345678);
	// printf("\n");
	// y = printf("og:[%-4d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("0.3d 12345678\n");
	// x = ft_printf("ft:[%0.3d]", 12345678);
	// printf("\n");
	// y = printf("og:[%0.3d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("-.3d 12345678\n");
	// x = ft_printf("ft:[%-.3d]", 12345678);
	// printf("\n");
	// y = printf("og:[%-.3d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("-.0d 12345678\n");
	// x = ft_printf("ft:[%-.0d]", 12345678);
	// printf("\n");
	// y = printf("og:[%-.0d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".0d 12345678\n");
	// x = ft_printf("ft:[%.0d]", 12345678);
	// printf("\n");
	// y = printf("og:[%.0d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("0d 12345678\n");
	// x = ft_printf("ft:[%0d]", 12345678);
	// printf("\n");
	// y = printf("og:[%0d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".20d 12345678\n");
	// x = ft_printf("ft:[%.20d]", 12345678);
	// printf("\n");
	// y = printf("og:[%.20d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("-.20d 12345678\n");
	// x = ft_printf("ft:[%-.20d]", 12345678);
	// printf("\n");
	// y = printf("og:[%-.20d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("d 2147483647\n");
	// x = ft_printf("ft:[%d]", 2147483647);
	// printf("\n");
	// y = printf("og:[%d]", 2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("d -2147483647\n");
	// x = ft_printf("ft:[%d]", -2147483647);
	// printf("\n");
	// y = printf("og:[%d]", -2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("15d 2147483647\n");
	// x = ft_printf("ft:[%15d]", 2147483647);
	// printf("\n");
	// y = printf("og:[%15d]", 2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("15d -2147483647\n");
	// x = ft_printf("ft:[%15d]", -2147483647);
	// printf("\n");
	// y = printf("og:[%15d]", -2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);
	
	// printf("15.13d 2147483647\n");
	// x = ft_printf("ft:[%15.13d]", 2147483647);
	// printf("\n");
	// y = printf("og:[%15.13d]", 2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("15.13d -2147483647\n");
	// x = ft_printf("ft:[%15.13d]", -2147483647);
	// printf("\n");
	// y = printf("og:[%15.13d]", -2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);
	
	// printf("15.15d 2147483647\n");
	// x = ft_printf("ft:[%15.15d]", 2147483647);
	// printf("\n");
	// y = printf("og:[%15.15d]", 2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("15.15d -2147483647\n");
	// x = ft_printf("ft:[%15.15d]", -2147483647);
	// printf("\n");
	// y = printf("og:[%15.15d]", -2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);
	
	// printf("15.14d 2147483647\n");
	// x = ft_printf("ft:[%15.14d]", 2147483647);
	// printf("\n");
	// y = printf("og:[%15.14d]", 2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("15.14d -2147483647\n");
	// x = ft_printf("ft:[%15.14d]", -2147483647);
	// printf("\n");
	// y = printf("og:[%15.14d]", -2147483647);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);




	// printf("-10.20d 12345678\n");
	// x = ft_printf("ft:[%-10.20d]", 12345678);
	// printf("\n");
	// y = printf("og:[%-10.20d]", 12345678);
	// printf("\nft ret : %d\n", x-5);//////retがおかしい
	// printf("og ret : %d\n\n", y-5);

	// printf("-30.20d 12345678\n");
	// x = ft_printf("ft:[%-30.20d]", 12345678);
	// printf("\n");
	// y = printf("og:[%-30.20d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("30.20d 12345678\n");
	// x = ft_printf("ft:[%30.20d]", 12345678);
	// printf("\n");
	// y = printf("og:[%30.20d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".3d 12345678\n");
	// x = ft_printf("ft:[%.3d]", 12345678);
	// printf("\n");
	// y = printf("og:[%.3d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".d 12345678\n");
	// x = ft_printf("ft:[%.d]", 12345678);
	// printf("\n");
	// y = printf("og:[%.d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("13.4d 12345678\n");
	// x = ft_printf("ft:[%13.4d]", 12345678);
	// printf("\n");
	// y = printf("og:[%13.4d]", 12345678);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".0d 0\n");
	// x = ft_printf("ft:[%.0d]", 0);
	// printf("\n");
	// y = printf("og:[%.0d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("7.5d 123\n");
	// x = ft_printf("ft:[%7.5d]", 123);
	// printf("\n");
	// y = printf("og:[%7.5d]", 123);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);



	// printf("7.5d\n");
	// x = ft_printf("ft:[%7.5d]", -123);
	// printf("\n");
	// y = printf("og:[%7.5d]", -123);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("-7.5d\n");
	// x = ft_printf("ft:[%-7.5d]", -123);
	// printf("\n");
	// y = printf("og:[%-7.5d]", -123);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("7.2d\n");
	// x = ft_printf("ft:[%7.2d]", 123);
	// printf("\n");
	// y = printf("og:[%7.2d]", 123);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("7.2d\n");
	// x = ft_printf("ft:[%7.2d]", -123);
	// printf("\n");
	// y = printf("og:[%7.2d]", -123);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("-7.2d\n");
	// x = ft_printf("ft:[%-7.2d]", -123);
	// printf("\n");
	// y = printf("og:[%-7.2d]", -123);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".0d\n");
	// x = ft_printf("ft:[%.0d]", 0);
	// printf("\n");
	// y = printf("og:[%.0d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("3.0d\n");
	// x = ft_printf("ft:[%3.0d]", 0);//空白を3つ出したい
	// printf("\n");
	// y = printf("og:[%3.0d]", 0);
	// printf("\nft ret : %d\n", x-5);//returnは3
	// printf("og ret : %d\n\n", y-5);
	

	// printf(".1d\n");
	// x = ft_printf("ft:[%.1d]", 0);
	// printf("\n");
	// y = printf("og:[%.1d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("3.1d\n");
	// x = ft_printf("ft:[%3.1d]", 0);
	// printf("\n");
	// y = printf("og:[%3.1d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("08d  42\n");
	// x = ft_printf("ft:[%08d]", 42);/////////////////////dame....
	// printf("\n");
	// y = printf("og:[%08d]", 42);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("08.5d  42\n");
	// x = ft_printf("ft:[%08.5d]", 42);
	// printf("\n");
	// y = printf("og:[%08.5d]", 42);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);
	
	// printf("5.5d  42\n");
	// x = ft_printf("ft:[%5.5d]", 42);
	// printf("\n");
	// y = printf("og:[%5.5d]", 42);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);
	
	printf("5.5d  -42\n");
	x = ft_printf("ft:[%5.5d]", -42);
	printf("\n");
	y = printf("og:[%5.5d]", -42);
	printf("\nft ret : %d\n", x-5);
	printf("og ret : %d\n\n", y-5);


	// x = ft_printf(".0d", 0);
	// printf("\n");
	// y = printf(".0d", 0);//			そもそもダメみたい
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);




printf("\n\n\n\n\n\n\n\n~~~~~~~~~~~~~~~\nしきり\n~~~~~~~~~~~~\n\n\n\n\n\n\n");



// printf("=========  p  ========\n")


	// x = ft_printf("ft:[%p]", "koto");
	// printf("\n");
	// y = printf("og:[%p]", "koto");
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);



//flag[minus]がtrueなら左寄せ
//flag[minus]がfalseなら右寄せ

//widthが桁数よりも小さければ、widthは無視で出力
//widthが桁数よりも大きければ、出力文字数はwidthになるように出力


}


// char str[] = "kotoyori";
// printf("10.5s : [%10.5s]\n",str);//[     kotoy]
// printf("8.5s  : [%8.5s]\n",str); //[   kotoy]
// printf("3.5s  : [%3.5s]\n",str); //[kotoy]




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:10:08 by skotoyor          #+#    #+#             */
/*   Updated: 2020/12/08 07:29:56 by skotoyor         ###   ########.fr       */
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

	if (content.conv == E_NOT_CONV)
		put_notconv_count(str, i, printed_len);//////convが指定されなかった時、そのまま出力する。printed_lenに出力した文字数を足す
	else
		put_string_or_nbr(ap, &content, printed_len);////contentを元に、va_argを吐き出す。printed_lenに出力した文字数を足す
// printf("\n====content debug===\n");
// 	printf("flag[E_MINUS] : %2d\n", content.flag[E_MINUS]);
// 	printf("flag[E_ZERO]  : %2d\n", content.flag[E_ZERO]);
// 	printf("width         : %2d\n", content.width);
// 	printf("prec          : %2d\n", content.prec);
// 	printf("conv          : %2d\n", content.conv);
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
			put_char_count(format[i], &printed_len);
			i++;
		}
	}
	va_end(ap);
	return (printed_len);
}



/*
int main () {///

	int x, y;
	// x = printf("koto%-23mocomoco", 52);
	// printf("\n");
	// y = ft_printf("koto%-23mocomoco", 52);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("koto%*%mocomoco", 4, 52);
	// printf("\n");
	// y = printf("koto%*dmocomoco", 4, 52);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);
	
	
	// x = ft_printf("koto%-10.*dmocomoco", 5, 42);
	// printf("\n");
	// y = printf("koto%-10.*dmocomoco", 5, 42);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);
	
	// x = ft_printf("koto%*.*dmocomoco",-4, 10, 42);
	// printf("\n");
	// y = printf("koto%*.*dmocomoco",-4, 10, 42);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("koto%-23%mocomoco");
	// printf("\n");
	// y = printf("koto%-23%mocomoco");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("koto%5.*dmocomoco", -78, 52);
	// printf("\n");
	// y = printf("koto%5.*dmocomoco",-78, 52);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf(".0d", 0);
	// printf("\n");
	// y = printf(".0d", 0);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%20d]", 40);
	// printf("\n");
	// y = printf("og:[%20d]", 40);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%p]", "koto");
	// printf("\n");
	// y = printf("og:[%p]", "koto");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%03%]");
	// printf("\n");
	// y = printf("og:[%03s]","ko");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%03.2%]");
	// printf("\n");
	// y = printf("og:[%-3%]");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%0000010.2]");
	// printf("\n");
	// y = printf("og:[%0000010.2%]");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%-4%]");
	// printf("\n");
	// y = printf("og:[%-4%]");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%-4%]");
	// printf("\n");
	// y = printf("og:[%-4%]");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%---0004.2%]");
	// printf("\n");
	// y = printf("og:[%---0004.2%]");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%-4c]", 'x');
	// printf("\n");
	// y = printf("og:[%-4c]", 'x');
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

	// x = ft_printf("ft:[%-6.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-6.s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);
	
	// x = ft_printf("ft:[%-6.3s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-6.3s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);
	
	// x = ft_printf("ft:[%4.3s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4.3s]", "kotoyori shota");
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y);

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



	//printf("======di=======\n");


	// printf("d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("4d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.15d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4.15d]", 12);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4.d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.10d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4.10d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.0d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4.0d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("4.9d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%4.9d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("02d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%02d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("-4d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-4d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("0.3d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%0.3d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("-.3d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-.3d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("-.0d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-.0d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf(".0d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%.0d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("0d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%0d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf(".20d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%.20d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("-.20d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-.20d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("-10.20d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-10.20d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	// printf("-30.20d\n");
	// x = ft_printf("ft:[%s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%-30.20d]", 12345678);
	// printf("\nft ret : %d\n", x);
	// printf("og ret : %d\n\n", y-5);

	printf("30.20d\n");
	x = ft_printf("ft:[%s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%30.20d]", 12345678);
	printf("\nft ret : %d\n", x);
	printf("og ret : %d\n\n", y-5);

	printf(".3d\n");
	x = ft_printf("ft:[%s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%.3d]", 12345678);
	printf("\nft ret : %d\n", x);
	printf("og ret : %d\n\n", y-5);

	printf(".d\n");
	x = ft_printf("ft:[%s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%.d]", 12345678);
	printf("\nft ret : %d\n", x);
	printf("og ret : %d\n\n", y-5);

	printf("13.4d\n");
	x = ft_printf("ft:[%s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%13.4d]", 12345678);
	printf("\nft ret : %d\n", x);
	printf("og ret : %d\n\n", y-5);

	// printf(".0d\n");
	// x = ft_printf("ft:[%.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%.0d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("7.5d\n");
	// x = ft_printf("ft:[%.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%7.5d]", 123);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	printf("7.5d\n");
	x = ft_printf("ft:[%.s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%7.5d]", -123);
	printf("\nft ret : %d\n", x-5);
	printf("og ret : %d\n\n", y-5);

	printf("-7.5d\n");
	x = ft_printf("ft:[%.s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%-7.5d]", -123);
	printf("\nft ret : %d\n", x-5);
	printf("og ret : %d\n\n", y-5);

	printf("7.2d\n");
	x = ft_printf("ft:[%.s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%7.2d]", 123);
	printf("\nft ret : %d\n", x-5);
	printf("og ret : %d\n\n", y-5);

	printf("7.2d\n");
	x = ft_printf("ft:[%.s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%7.2d]", -123);
	printf("\nft ret : %d\n", x-5);
	printf("og ret : %d\n\n", y-5);

	printf("-7.2d\n");
	x = ft_printf("ft:[%.s]", "kotoyori shota");
	printf("\n");
	y = printf("og:[%-7.2d]", -123);
	printf("\nft ret : %d\n", x-5);
	printf("og ret : %d\n\n", y-5);

	// printf(".0d\n");
	// x = ft_printf("ft:[%.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%.0d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("3.0d\n");
	// x = ft_printf("ft:[%.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%3.0d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf(".1d\n");
	// x = ft_printf("ft:[%.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%7.2d]", 0);
	// printf("\nft ret : %d\n", x-5);
	// printf("og ret : %d\n\n", y-5);

	// printf("3.1d\n");
	// x = ft_printf("ft:[%.s]", "kotoyori shota");
	// printf("\n");
	// y = printf("og:[%7.2d]", 0);
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



*/
#ifdef TEST
#include <stdio.h>
#endif

#include <unistd.h>
#include <stdarg.h>
//#include <libstd.h>

typedef enum	e_conv
{
	E_NOTCONV,
	E_STRING,
	E_DECIMAL,
	E_XSMALL
}				t_conv;

typedef struct	e_content
{
	int width;
	int prec;
	int conv;
}				t_content;

void init_content(t_content *content)
{
	content->width = -1;
	content->prec = -1;
	content->conv = E_NOTCONV;
}

int is_width(char c, t_content *content)
{
	if ('0' <= c && c <= '9' && content->prec < 0)
	{
		if (content->width < 0)
		{
			content->width = c - '0';
			return 1;
		}
		content->width = (content->width * 10) + (c - '0');
		return 1;
	}
	return 0;
}

int is_prec(char c, t_content *content)
{
	if (c == '.' && content->prec < 0)
	{
		content->prec = 0;
		return 1;
	}
	if ('0' <= c && c <= '9' && content->prec >= 0)
	{
		content->prec = (content->prec * 10) + (c - '0');
		return 1;
	}
	return 0;
}

int is_conv(char c, t_content *content)
{
	if (c == 's')
	{
		content->conv = E_STRING;
		return 1;
	}
	if (c == 'd')
	{
		content->conv = E_DECIMAL;
		return 1;
	}
	if (c == 'x')
	{
		content->conv = E_XSMALL;
		return 1;
	}
	return 0;
}

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

int put_conv_s(va_list *ap, t_content *content)
{
	int printed_len = 0;
	char *str = (char *)va_arg(*ap, char *);
	if (!str)
		str = "(null)";
	int s_len = ft_strlen(str);
	int len;

	if (content->prec < 0)
		len = s_len;
	else
		len = (s_len < content->prec) ? s_len : content->prec;

	int space_len = content->width - len;

	while (space_len-- > 0)
		printed_len += write(1, " ", 1);
	
	int i = 0;
	while (i < len)
		printed_len += write(1, &str[i++], 1);

	return printed_len;
}

int get_digit(long tmp_num, long base)
{
	long n = (tmp_num < 0) ? -tmp_num : tmp_num;
	int digit = 0;
	while (n/base != 0)
	{
		digit++;
		n /= base;
	}
	digit++;
	return digit;
}

int put_nbr(char *num_arr, long base, long tmp_num)
{
	int printed_len = 0;
	long n = (tmp_num < 0) ? -tmp_num : tmp_num;

	if (n/base == 0)
	{
		printed_len += write(1, &num_arr[n], 1);
		return printed_len;
	}
	printed_len += put_nbr(num_arr, base, n/base);
	printed_len += write(1, &num_arr[n%base], 1);

	return printed_len;
}

int put_conv_d(va_list *ap, t_content *content)
{
	int printed_len = 0;
	int int_num = (int)va_arg(*ap, int);
	int abs_digit = get_digit((long)int_num, 10);
	int zeronum_len = (abs_digit > content->prec) ? abs_digit : content->prec;
	int space_len;

	if (int_num < 0)
		space_len = content->width - zeronum_len - 1;
	else
		space_len = content->width - zeronum_len;
	
	if (content->width <= 0 && !content->prec && !int_num)
		return 0;
	
	while (space_len-- > 0)
		printed_len += write(1, " ", 1);
	
	if (int_num < 0)
		printed_len += write(1, "-", 1);

	while (zeronum_len-- > abs_digit)
		printed_len += write(1, "0", 1);

	if (!content->prec && !int_num)
		printed_len += write(1, " ", 1);
	else
		printed_len += put_nbr("0123456789", 10, (long)int_num);

	return printed_len;
}

int put_conv_x(va_list *ap, t_content *content)
{
	int printed_len = 0;
	unsigned int int_num = (unsigned int)va_arg(*ap, unsigned int);
	int abs_digit = get_digit((long)int_num, 16);
	int zeronum_len = (abs_digit > content->prec) ? abs_digit : content->prec;
	int space_len;

	if (int_num < 0)
		space_len = content->width - zeronum_len - 1;
	else
		space_len = content->width - zeronum_len;
	
	if (content->width <= 0 && !content->prec && !int_num)
		return 0;
	
	while (space_len-- > 0)
		printed_len += write(1, " ", 1);
	
	if (int_num < 0)
		printed_len += write(1, "-", 1);

	while (zeronum_len-- > abs_digit)
		printed_len += write(1, "0", 1);

	if (!content->prec && !int_num)
		printed_len += write(1, " ", 1);
	else
		printed_len += put_nbr("0123456789abcdef", 16, (long)int_num);

	return printed_len;
}

int put_sdx(va_list *ap, char *str, int *i)
{
	int printed_len = 0;
	int i_sdx = 1;
	t_content content;

	init_content(&content);

	while (str[i_sdx])
	{
		if (is_width(str[i_sdx], &content))
			;
		else if (is_prec(str[i_sdx], &content))
			;
		else if (is_conv(str[i_sdx++], &content))
			break;
		i_sdx++;
	}

//(void)ap;
//printf("\n===debug zone===\n");
//printf("width:%d\n", content.width);
//printf("prec :%d\n", content.prec);
//printf("conv :%d\n", content.conv);
//printf("i_sdx:%d\n", i_sdx);
//printf("===end debug zone===\n\n");
	if (content.conv == E_STRING)
		printed_len += put_conv_s(ap, &content);
	else if (content.conv == E_DECIMAL)
		printed_len += put_conv_d(ap, &content);
	else if (content.conv == E_XSMALL)
		printed_len += put_conv_x(ap, &content);


	*i += i_sdx;
	return printed_len;
}


int ft_printf(const char *format, ...)
{
	int printed_len = 0;
	char *fmt = (char *)format;
	int i = 0;
	va_list ap;

	va_start(ap, format);

	while (fmt[i])
	{
		if (fmt[i] == '%')
			printed_len += put_sdx(&ap, fmt+i, &i);
		else
			printed_len += write(1, &fmt[i++], 1);
	}

	va_end(ap);
	return printed_len;
}


#ifdef TEST

int main(){
	int x;
	int y;

	x = ft_printf("ft:[%x]\n", 42);
	y =    printf("og:[%x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%3x]\n", 42);
	y =    printf("og:[%3x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%8x]\n", 42);
	y =    printf("og:[%8x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%20x]\n", 42);
	y =    printf("og:[%20x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%.x]\n", 42);
	y =    printf("og:[%.x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%.3x]\n", 42);
	y =    printf("og:[%.3x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%.8x]\n", 42);
	y =    printf("og:[%.8x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%.20x]\n", 42);
	y =    printf("og:[%.20x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");


	x = ft_printf("ft:[%.x]\n", 42);
	y =    printf("og:[%.x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%3.x]\n", 42);
	y =    printf("og:[%3.x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%8.x]\n", 42);
	y =    printf("og:[%8.x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%20.x]\n", 42);
	y =    printf("og:[%20.x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%.2x]\n", 42);
	y =    printf("og:[%.2x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%3.2x]\n", 42);
	y =    printf("og:[%3.2x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%8.2x]\n", 42);
	y =    printf("og:[%8.2x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%20.2x]\n", 42);
	y =    printf("og:[%20.2x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%.5x]\n", 42);
	y =    printf("og:[%.5x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%3.5x]\n", 42);
	y =    printf("og:[%3.5x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%8.5x]\n", 42);
	y =    printf("og:[%8.5x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%20.5x]\n", 42);
	y =    printf("og:[%20.5x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%.10x]\n", 42);
	y =    printf("og:[%.10x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%3.10x]\n", 42);
	y =    printf("og:[%3.10x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%8.10x]\n", 42);
	y =    printf("og:[%8.10x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	x = ft_printf("ft:[%20.10x]\n", 42);
	y =    printf("og:[%20.10x]\n", 42);
	printf("ft_ret:%d\n", x-6);
	printf("og_ret:%d\n", y-6);
	printf("\n");

	return 0;
}

#endif

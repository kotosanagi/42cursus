/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:46:58 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/07 16:46:32 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	make_header(t_info *info, unsigned char *bmp_header)
{
	t_header	head;
	int			i;

	i = 0;
	head.file_size = info->r_width * info->r_height * 3 + 54;
	head.offset = 54;
	head.header_size = 40;
	head.planes = 1;
	head.bpp = 24;
	ft_memcpy(&bmp_header[i], "BM", 2);
	ft_memcpy(&bmp_header[i += 2], &head.file_size, 4);
	ft_memset(&bmp_header[i += 4], 0, 4);
	ft_memcpy(&bmp_header[i += 4], &head.offset, 4);
	ft_memcpy(&bmp_header[i += 4], &head.header_size, 4);
	ft_memcpy(&bmp_header[i += 4], &info->r_width, 4);
	ft_memcpy(&bmp_header[i += 4], &info->r_height, 4);
	ft_memcpy(&bmp_header[i += 4], &head.planes, 2);
	ft_memcpy(&bmp_header[i += 2], &head.bpp, 4);
	ft_memset(&bmp_header[i += 4], 0, 24);
}

static int	convert_color(int color, int rgb)
{
	if (rgb == RED)
		return ((color & (0xFF << 16)) >> 16);
	else if (rgb == GREEN)
		return ((color & (0xFF << 8)) >> 8);
	else if (rgb == BLUE)
		return (color & 0xFF);
	else
		return (0);
}

static void	store_bmp_image(t_info *info, unsigned char *img)
{
	int x;
	int y;

	y = 0;
	while (y < info->r_height - 1)
	{
		x = 0;
		while (x < info->r_width)
		{
			img[(y * info->r_width + x)
			* 3 + 2] = convert_color(info->buf[y][x], RED);
			img[(y * info->r_width + x)
			* 3 + 1] = convert_color(info->buf[y][x], GREEN);
			img[(y * info->r_width + x)
			* 3 + 0] = convert_color(info->buf[y][x], BLUE);
			x++;
		}
		y++;
	}
}

static void	draw_bmp(t_info *info, int fd, unsigned char *img)
{
	unsigned char	bmppad[3];
	int				pad_num;
	int				i;

	ft_bzero(bmppad, 3);
	pad_num = 4 - (info->r_width * 3) % 4;
	i = 0;
	while (i < info->r_height)
	{
		write(fd, img + (info->r_width * (info->r_height - i - 1) * 3),
		3 * info->r_width);
		if (pad_num != 4)
			write(fd, bmppad, pad_num);
		i++;
	}
}

void		create_bmp(t_info *info)
{
	unsigned char	bmp_header[54];
	int				fd;
	unsigned char	*img;

	calc_func(info);
	if (!(img = (unsigned char *)malloc(sizeof(unsigned char)
	* info->r_width * info->r_height * 3)))
		error_free_exit("can't allocate img\n", info);
	ft_bzero(img, 3 * info->r_width * info->r_height);
	make_header(info, bmp_header);
	store_bmp_image(info, img);
	fd = open("cub3d_image.bmp", O_CREAT | O_WRONLY);
	if (fd == -1)
		error_free_exit("can't open bmp file\n", info);
	write(fd, bmp_header, 54);
	draw_bmp(info, fd, img);
	close(fd);
	safe_free(img);
	exit_successful(info);
}

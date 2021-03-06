/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 07:11:14 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 20:15:11 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	load_image2(unsigned int *addr, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			addr[y * img->img_width + x] = \
				*(unsigned int *)(img->data + (y * img->img_width + x));
			x++;
		}
		y++;
	}
}

static void	load_image(t_info *info, char *path, int tex_num)
{
	t_img img;

	img.img = mlx_xpm_file_to_image(info->mlx, path, &img.img_width,
	&img.img_height);
	if (img.img == NULL)
		error_free_exit("can't load texture\n", info);
	if (img.img_width != TEX_WIDTH || img.img_height != TEX_HEIGHT)
		error_free_exit("textures are allowed 64 * 64 size\n", info);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp,
	&img.size_l, &img.endian);
	if (!(info->tex[tex_num].addr =
	(unsigned int *)malloc(sizeof(unsigned int)
	* img.img_width * img.img_height)))
		error_free_exit("can't allocate texture data\n", info);
	load_image2(info->tex[tex_num].addr, &img);
	info->tex[tex_num].h = img.img_height;
	info->tex[tex_num].w = img.img_width;
	mlx_destroy_image(info->mlx, img.img);
}

void		load_texture(t_info *info)
{
	load_image(info, info->south_path, SOUTH_TEXTURE);
	load_image(info, info->north_path, NORTH_TEXTURE);
	load_image(info, info->east_path, EAST_TEXTURE);
	load_image(info, info->west_path, WEST_TEXTURE);
	load_image(info, info->sprite_path, SPRITE_TEXTURE);
}

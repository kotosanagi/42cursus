/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 07:11:14 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 09:10:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	load_image2(unsigned int *addr, t_img *img)
{
	int	x;
	int	y;

	y = 0;
// printf("in load_image2\n");
// printf("img_width :%d\n", img->img_width);
// printf("img_height:%d\n", img->img_height);
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
	// printf("x:%d, y:%d\n",x, y);
// printf("img.img:%p\n",img->img);
// printf("img.data:%p\n",img->data);
// printf("img.size_l:%d\n",img->size_l);
// printf("img.bpp:%d\n",img->bpp);
// printf("img.endian:%d\n",img->endian);
// printf("img.img_width:%d\n",img->img_width);
// printf("img.img_height:%d\n",img->img_height);


// printf("-------\n");
// printf("y:%d, x:%d\n", y ,x);
			// addr[y * img->img_width + x] = 
				// *(unsigned int *)(img->data + (y * img->size_l + x * (img->bpp / 8)));//0305
			addr[y * img->img_width + x] = \
				*(unsigned int *)(img->data + (y * img->img_width + x));//0305
			x++;
		}
		
		y++;
	}

}

static void	load_image(t_info *info, char *path, int tex_num)
{
	t_img img;

	img.img = mlx_xpm_file_to_image(info->mlx, path, &img.img_width, &img.img_height);
	if (img.img == NULL)
		error_free_exit("can't load texture\n", info);
	if (img.img_width != TEX_WIDTH || img.img_height != TEX_HEIGHT)
		error_free_exit("textures are allowed 64 * 64 size\n", info);
// printf("success load %s\n", path);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size_l, &img.endian);
	// img.data = mlx_get_data_addr(img.img, &img.bpp, &img.size_l, &img.endian);////0305
// printf("img_width :%d\n", img.img_width);
// printf("img_height:%d\n", img.img_height);
	if (!(info->tex[tex_num].addr = (unsigned int *)malloc(sizeof(unsigned int) * img.img_width * img.img_height)))
		error_free_exit("can't allocate texture data\n", info);

	load_image2(info->tex[tex_num].addr, &img);
	info->tex[tex_num].h = img.img_height;
	info->tex[tex_num].w = img.img_width;

	mlx_destroy_image(info->mlx, img.img);




	// for (int y = 0; y < img.img_height; y++)
	// {
	// 	for (int x = 0; x < img.img_width; x++)
	// 		texture[img.img_width * y + x] = img.data[img.img_width * y + x];
	// }
	// mlx_destroy_image(info->mlx, img.img);
}

void		load_texture(t_info *info)
{

	load_image(info, info->south_path, NORTH_TEXTURE);
	load_image(info, info->north_path, SOUTH_TEXTURE);
	load_image(info, info->east_path, WEST_TEXTURE);
	load_image(info, info->west_path, EAST_TEXTURE);
	load_image(info, info->sprite_path , SPRITE_TEXTURE);

// 	t_img	img;
// //CAUSE OF DIRECTION CALC, NEED TO MODIFY WALL DEFINITION
// 	load_image(info, info->texture[NORTH_TEXTURE], info->south_path, &img);
// 	load_image(info, info->texture[SOUTH_TEXTURE], info->north_path, &img);
// 	load_image(info, info->texture[WEST_TEXTURE], info->east_path, &img);
// 	load_image(info, info->texture[EAST_TEXTURE], info->west_path, &img);
// 	load_image(info, info->texture[SPRITE_TEXTURE], info->sprite_path , &img);
	// load_image(info, info->texture[NORTH_TEXTURE], info->west_path, &img);
	// load_image(info, info->texture[SOUTH_TEXTURE], info->east_path, &img);
	// load_image(info, info->texture[WEST_TEXTURE], info->south_path, &img);
	// load_image(info, info->texture[EAST_TEXTURE], info->north_path, &img);
	// load_image(info, info->texture[NORTH_TEXTURE], "images/koto_west.xpm", &img);
	// load_image(info, info->texture[SOUTH_TEXTURE], "images/koto_east.xpm", &img);
	// load_image(info, info->texture[WEST_TEXTURE], "images/koto_south.xpm", &img);
	// load_image(info, info->texture[EAST_TEXTURE], "images/koto_north.xpm", &img);
	// load_image(info, info->texture[SPRITE_TEXTURE], "images/koto_sprite.xpm", &img);
	// load_image(info, info->texture[SPRITE_TEXTURE], "images/moco01.xpm", &img);
	// load_image(info, info->texture[0], "images/moco03.xpm", &img);
	// load_image(info, info->texture[1], "images/moco01.xpm", &img);
	// load_image(info, info->texture[2], "images/moco02.xpm", &img);
	// load_image(info, info->texture[3], "images/moco03.xpm", &img);
	// load_image(info, info->texture[4], "images/moco04.xpm", &img);
	// load_image(info, info->texture[5], "images/moco05.xpm", &img);
	// load_image(info, info->texture[6], "images/moco06.xpm", &img);
	// load_image(info, info->texture[7], "images/moco03.xpm", &img);
}

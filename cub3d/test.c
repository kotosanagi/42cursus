// gcc test.c -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz && ./a.out

#include "mlx_linux/mlx.h"
#include "key_linux.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// #define K_ESC 65307
#define WIDTH 640
#define HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define NS 1
#define EW 0
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define EAST_TEXTURE 0
#define WEST_TEXTURE 1
#define NORTH_TEXTURE 2
#define SOUTH_TEXTURE 3
#define SPRITE_TEXTURE 4


typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void *mlx;
	void *win;
	t_img img;
	int buf[HEIGHT][WIDTH];
	int **texture;
	double moveSpeed;
	double rotSpeed;
}				t_info;

int	key_hook(int keycode, t_info *info)
{
	printf("keycode : %d\n", keycode);
	return 0;
}

int mouse_hook(int mousecode, t_info *info)
{
	printf("mousecode : %d\n", mousecode);
	return 0;
}

int close_window(int keycode, t_info *info)
{
	if (keycode == K_ESC)
		mlx_destroy_window(info->mlx, info->win);
	return 0;
}

int print_hello(t_info *info)
{
	printf("Hello~~~~\n");
	return 0;
}

int print_bye(t_info *info)
{
	printf("bye!!!!!\n");
	return 0;
}

int	worldMap[MAP_WIDTH][MAP_HEIGHT] = {
	{1,1,1,4,4,1,1,1},
	{1,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,1},
	{1,0,0,0,2,0,0,2},
	{1,4,0,0,0,0,0,2},
	{1,0,0,0,0,0,2,2},
	{1,4,0,4,0,0,0,2},
	{1,1,1,1,1,3,3,3}
};
// int	worldMap[MAP_WIDTH][MAP_HEIGHT] = {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
// 	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
// 	{1,0,1,0,0,0,0,4,4,4,4,4,4,4,4,4,1,1,0,1,1,1,1,1},
// 	{1,0,4,0,0,0,0,4,0,4,0,4,0,4,0,4,1,0,0,0,1,1,1,1},
// 	{1,0,4,0,0,0,0,4,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,4},
// 	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
// 	{1,0,4,0,0,0,0,4,0,0,0,0,0,0,0,4,1,0,0,0,0,0,0,4},
// 	{1,0,0,0,0,0,0,4,0,0,0,0,0,0,0,4,1,0,0,0,1,1,1,1},
// 	{1,0,0,0,0,0,0,4,4,4,4,0,4,4,4,4,1,1,1,1,1,1,1,1},
// 	{4,4,4,4,4,4,4,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
// 	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{4,4,4,4,4,4,0,4,4,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4},
// 	{1,1,1,1,1,1,0,1,1,1,4,0,4,2,2,2,2,2,2,2,3,3,3,3},
// 	{1,0,0,0,0,0,0,0,0,1,4,0,4,2,0,0,0,0,0,2,0,0,0,2},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,4,2,0,0,4,0,0,2,0,0,0,2},
// 	{1,0,0,0,0,0,0,0,0,1,4,0,4,2,0,0,0,0,0,2,2,0,2,2},
// 	{1,0,4,0,4,0,0,0,0,1,4,0,0,0,0,0,4,0,0,0,0,0,0,2},
// 	{1,0,0,4,0,0,0,0,0,1,4,0,4,2,0,0,0,0,0,2,2,0,2,2},
// 	{1,0,4,0,4,0,0,0,0,1,4,0,4,2,0,0,4,0,0,2,0,0,0,2},
// 	{1,0,0,0,0,0,0,0,0,1,4,0,4,2,0,0,0,0,0,2,0,0,0,2},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
// };

////////////////////////////////////////////////////

void	draw(t_info *info)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			info->img.data[y * WIDTH + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void calc(t_info *info)
{
	int color;

	for (int y = 0; y < HEIGHT; y++) // in order to draw left to right, buf[y][x]
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (y < HEIGHT / 2)
				color = 0x9dcce0; // color of ceiling
			else
				color = 0xb26235; // color of floor
			info->buf[y][x] = color;
		}
	}


	int x = 0;

	while (x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;

		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = EW; // EW?
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = NS; // NS?
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == EW) // EW?
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd > HEIGHT)
			drawEnd = HEIGHT - 1;

		// int texNum = worldMap[mapX][mapY];

//////////////////////////////// choose texture
		int texNum;

		if (side == EW)
		{
			if (mapX > info->posX)
				texNum = WEST_TEXTURE;
			else
				texNum = EAST_TEXTURE;
		}
		else
		{
			if (mapY > info->posY)
				texNum = SOUTH_TEXTURE;
			else
				texNum = NORTH_TEXTURE;
		}


////////////////////////////////


		double wallX;
		if (side == EW)
			wallX = info->posY + perpWallDist * rayDirY;
		else
			wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)TEX_WIDTH);
		if (side == EW && rayDirX > 0)
			texX = TEX_WIDTH - texX - 1;
		if (side == NS && rayDirY < 0)
			texX = TEX_WIDTH - texX - 1;

		double step = 1.0 * TEX_HEIGHT / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			int texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			int color = info->texture[texNum][TEX_HEIGHT * texY + texX];
			info->buf[y][x] = color;
		}

// printf("posX:%2.2f, posY:%2.2f, dirX:%2.2f, dirY:%2.2f, planeX:%2.2f, planeY:%2.2f\n", info->posX, info->posY, info->dirX, info->dirY, info->planeX, info->planeY);

		x++;
	}
}

////////////////////////////////////////////////////



////////////////////////////
int main_loop(t_info *info)
{
	calc(info);
	draw(info);

	return (0);
}


int	key_press(int key, t_info *info)
{
	//move forwards if no wall in front of you
	if (key == K_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	////////////move right-step if no wall right of you
	if (key == K_D)
	{
		if (!worldMap[(int)(info->posX + info->planeX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->planeX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->planeY * info->moveSpeed)])
			info->posY += info->planeY * info->moveSpeed;
	}
	////////////move left-step if no wall left of you
	if (key == K_A)
	{
		if (!worldMap[(int)(info->posX - info->planeX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->planeX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->planeY * info->moveSpeed)])
			info->posY -= info->planeY * info->moveSpeed;
	}
	//rotate to the right
	if (key == K_AR_R)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (key == K_AR_L)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;


	load_image(info, info->texture[EAST_TEXTURE], "images/koto_east.xpm", &img);
	load_image(info, info->texture[WEST_TEXTURE], "images/koto_west.xpm", &img);
	load_image(info, info->texture[SOUTH_TEXTURE], "images/koto_south.xpm", &img);
	load_image(info, info->texture[NORTH_TEXTURE], "images/koto_north.xpm", &img);
	load_image(info, info->texture[SPRITE_TEXTURE], "images/moco01.xpm", &img);
	// load_image(info, info->texture[0], "images/moco03.xpm", &img);
	// load_image(info, info->texture[1], "images/moco01.xpm", &img);
	// load_image(info, info->texture[2], "images/moco02.xpm", &img);
	// load_image(info, info->texture[3], "images/moco03.xpm", &img);
	// load_image(info, info->texture[4], "images/moco04.xpm", &img);
	// load_image(info, info->texture[5], "images/moco05.xpm", &img);
	// load_image(info, info->texture[6], "images/moco06.xpm", &img);
	// load_image(info, info->texture[7], "images/moco03.xpm", &img);
	// load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	// load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	// load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	// load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	// load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	// load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	// load_image(info, info->texture[6], "textures/wood.xpm", &img);
	// load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}

int main(void)
{
	t_info	info;
	// t_data	img;

	info.mlx = mlx_init();
	info.posX = 1.5;
	info.posY = 1.5;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;

	int tex_num = 5;


	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			info.buf[i][j] = 0;
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * tex_num)))
		return (-1);
	for (int i = 0; i < tex_num; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH))))
			return (-1);
	}
	for (int i = 0; i < tex_num; i++)
	{
		for (int j = 0; j < TEX_HEIGHT * TEX_WIDTH; j++)
			info.texture[i][j] = 0;
	}

	load_texture(&info);

	info.win = mlx_new_window(info.mlx, WIDTH, HEIGHT, "mocomoco world!!!!");

	info.img.img = mlx_new_image(info.mlx, WIDTH, HEIGHT);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);


	mlx_key_hook(info.win, key_hook, &info);
	mlx_mouse_hook(info.win, mouse_hook, &info);
	mlx_hook(info.win, 2, 1L<<0, close_window, &info);	//close window when ESC pressed
	mlx_hook(info.win, 7, 1L<<4, print_hello, &info);	//enter window 
	mlx_hook(info.win, 8, 1L<<5, print_bye, &info);		//leave window


	mlx_loop_hook(info.mlx, &main_loop, &info);

	mlx_hook(info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &info);

	mlx_loop(info.mlx);
	return 0;
}
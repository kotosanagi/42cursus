// gcc main.c -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz && ./a.out

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

#define num_sprites 5

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;


//////////// for sprite ////////////
t_sprite	sprite[num_sprites] =
{
	{3.5, 1.5, SPRITE_TEXTURE},
	{3.5, 2.5, SPRITE_TEXTURE},
	{5.5, 4.5, SPRITE_TEXTURE},
	{2.5, 5.5, SPRITE_TEXTURE},
	{6.5, 6.5, SPRITE_TEXTURE},
};

int		sprite_order[num_sprites];
double	sprite_distance[num_sprites];

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

//////////// end for sprite ////////////

typedef struct	s_info
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	void *mlx;
	void *win;
	t_img img;
	int buf[HEIGHT][WIDTH];

	double	z_buffer[WIDTH];///////////for sprite?

	int **texture;
	double move_speed;
	double rot_speed;
}				t_info;


////////////// for sprite 2 ////////////

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

static int	compare(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
		return (1);
	else if (*(int *)first < *(int *)second)
		return (-1);
	else
		return (0);
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}



////////////// end for sprite 2 ////////////


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

int	world_map[MAP_WIDTH][MAP_HEIGHT] = {
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1},
	{1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1},
	{1,1,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};
// int	world_map[MAP_WIDTH][MAP_HEIGHT] = {
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

	////////////// draw ceiling and floor /////////////////
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

	////////////// end draw ceiling and floor /////////////////

	int x = 0;

	while (x < WIDTH)
	{
		double camera_x = 2 * x / (double)WIDTH - 1;
		double ray_dir_x = info->dir_x + info->plane_x * camera_x;
		double ray_dir_y = info->dir_y + info->plane_y * camera_x;

		int map_x = (int)info->pos_x;
		int map_y = (int)info->pos_y;

		double side_dist_x;
		double side_dist_y;

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;

		int step_x;
		int step_y;

		int hit = 0;
		int side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (info->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - info->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (info->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - info->pos_y) * delta_dist_y;
		}

		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = EW; // EW?
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = NS; // NS?
			}
			if (world_map[map_x][map_y] == 1)
				hit = 1;
		}
		if (side == EW) // EW?
			perp_wall_dist = (map_x - info->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - info->pos_y + (1 - step_y) / 2) / ray_dir_y;

		int line_height = (int)(HEIGHT / perp_wall_dist);

		int draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end > HEIGHT)
			draw_end = HEIGHT - 1;

		// int tex_num = world_map[map_x][map_y];

//////////////////////////////// choose texture
		int tex_num;

		if (side == EW)
		{
			if (map_x > info->pos_x)
				tex_num = WEST_TEXTURE;
			else
				tex_num = EAST_TEXTURE;
		}
		else
		{
			if (map_y > info->pos_y)
				tex_num = SOUTH_TEXTURE;
			else
				tex_num = NORTH_TEXTURE;
		}

////////////////////////////////


		double wall_x;
		if (side == EW)
			wall_x = info->pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = info->pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		// x coordinate on the texture
		int tex_x = (int)(wall_x * (double)TEX_WIDTH);
		if (side == EW && ray_dir_x > 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		if (side == NS && ray_dir_y < 0)
			tex_x = TEX_WIDTH - tex_x - 1;

		double step = 1.0 * TEX_HEIGHT / line_height;
		// Starting texture coordinate
		double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
			tex_pos += step;
			int color = info->texture[tex_num][TEX_HEIGHT * tex_y + tex_x];
			info->buf[y][x] = color;
		}

		/////////// for fprite //////////////////////////////////////
		//SET THE z_buffer FOR THE SPRITE CASTING
		info->z_buffer[x] = perp_wall_dist; //perpendicular distance is used
		/////////// end for fprite //////////////////////////////////////

// printf("pos_x:%2.2f, pos_y:%2.2f, dir_x:%2.2f, dir_y:%2.2f, plane_x:%2.2f, plane_y:%2.2f\n", info->pos_x, info->pos_y, info->dir_x, info->dir_y, info->plane_x, info->plane_y);

		x++;
	}

	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < num_sprites; i++)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((info->pos_x - sprite[i].x) * (info->pos_x - sprite[i].x) + (info->pos_y - sprite[i].y) * (info->pos_y - sprite[i].y)); //sqrt not taken, unneeded
	}
	sort_sprites(sprite_order, sprite_distance, num_sprites);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < num_sprites; i++)
	{
		//translate sprite position to relative to camera
		double sprite_x = sprite[sprite_order[i]].x - info->pos_x;
		double spriteY = sprite[sprite_order[i]].y - info->pos_y;

		//transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
		// [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [                 ]
		// [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

		double inv_det = 1.0 / (info->plane_x * info->dir_y - info->dir_x * info->plane_y); //required for correct matrix multiplication

		double transform_x = inv_det * (info->dir_y * sprite_x - info->dir_x * spriteY);
		double transform_y = inv_det * (-info->plane_y * sprite_x + info->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(sprite_distance[i])

		int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));

		//parameters for scaling and moving the sprites
		#define u_div 1
		#define v_div 1
		#define v_move 0.0
		int v_move_screen = (int)(v_move / transform_y);

		//calculate HEIGHT of the sprite on screen
		int sprite_height = (int)fabs((HEIGHT / transform_y) / v_div); //using "transform_y" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int draw_start_y = -sprite_height / 2 + HEIGHT / 2 + v_move_screen;
		if(draw_start_y < 0) draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + HEIGHT / 2 + v_move_screen;
		if(draw_end_y >= HEIGHT) draw_end_y = HEIGHT - 1;

		//calculate WIDTH of the sprite
		int sprite_width = (int)fabs((HEIGHT / transform_y) / u_div);
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if(draw_start_x < 0) draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if(draw_end_x >= WIDTH) draw_end_x = WIDTH - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * TEX_WIDTH / sprite_width) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) z_buffer, with perpendicular distance
			if(transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < info->z_buffer[stripe])
			for(int y = draw_start_y; y < draw_end_y; y++) //for every pixel of the current stripe
			{
				int d = (y-v_move_screen) * 256 - HEIGHT * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
				int tex_y = ((d * TEX_HEIGHT) / sprite_height) / 256;
				int color = info->texture[sprite[sprite_order[i]].texture][TEX_WIDTH * tex_y + tex_x]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
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
		if (!world_map[(int)(info->pos_x + info->dir_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x += info->dir_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y + info->dir_y * info->move_speed)])
			info->pos_y += info->dir_y * info->move_speed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!world_map[(int)(info->pos_x - info->dir_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x -= info->dir_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y - info->dir_y * info->move_speed)])
			info->pos_y -= info->dir_y * info->move_speed;
	}
	////////////move right-step if no wall right of you
	if (key == K_D)
	{
		if (!world_map[(int)(info->pos_x + info->plane_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x += info->plane_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y + info->plane_y * info->move_speed)])
			info->pos_y += info->plane_y * info->move_speed;
	}
	////////////move left-step if no wall left of you
	if (key == K_A)
	{
		if (!world_map[(int)(info->pos_x - info->plane_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x -= info->plane_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y - info->plane_y * info->move_speed)])
			info->pos_y -= info->plane_y * info->move_speed;
	}
	//rotate to the right
	if (key == K_AR_R)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = info->dir_x;
		info->dir_x = info->dir_x * cos(-info->rot_speed) - info->dir_y * sin(-info->rot_speed);
		info->dir_y = old_dir_x * sin(-info->rot_speed) + info->dir_y * cos(-info->rot_speed);
		double old_plane_x = info->plane_x;
		info->plane_x = info->plane_x * cos(-info->rot_speed) - info->plane_y * sin(-info->rot_speed);
		info->plane_y = old_plane_x * sin(-info->rot_speed) + info->plane_y * cos(-info->rot_speed);
	}
	//rotate to the left
	if (key == K_AR_L)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = info->dir_x;
		info->dir_x = info->dir_x * cos(info->rot_speed) - info->dir_y * sin(info->rot_speed);
		info->dir_y = old_dir_x * sin(info->rot_speed) + info->dir_y * cos(info->rot_speed);
		double old_plane_x = info->plane_x;
		info->plane_x = info->plane_x * cos(info->rot_speed) - info->plane_y * sin(info->rot_speed);
		info->plane_y = old_plane_x * sin(info->rot_speed) + info->plane_y * cos(info->rot_speed);
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
	load_image(info, info->texture[SPRITE_TEXTURE], "images/koto_sprite.xpm", &img);
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

int main(void)
{
	t_info	info;

	info.mlx = mlx_init();
	info.pos_x = 1.5;
	info.pos_y = 1.5;
	info.dir_x = -1.0;
	info.dir_y = 0.0;
	info.plane_x = 0.0;
	info.plane_y = 0.66;
	info.move_speed = 0.05;
	info.rot_speed = 0.05;

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
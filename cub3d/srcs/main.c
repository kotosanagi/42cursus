/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 04:57:59 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/01 07:03:56 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  COMPILATION //
//OLD// gcc main.c -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz && ./a.out
//OLD// gcc -Wall -Wextra -Werror main.c libft/*.o -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -I./includes -L./libraries -lXext -lX11 -lm -lz && ./a.out
//OLD// gcc -Wall -Wextra -Werror srcs/*.c libft/*.o -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -I./includes -L./libraries -lXext -lX11 -lm -lz && ./a.out
// gcc -Wall -Wextra -Werror srcs/*.c libft/*.o gnl/*.o -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -I./includes -L./libraries -lXext -lX11 -lm -lz && ./a.out koto.cub

// leak check
// gcc -Wall -Wextra -Werror -g -fsanitize=leak srcs/*.c libft/*.o gnl/*.o -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -I./includes -L./libraries -lXext -lX11 -lm -lz && ./a.out
// valgrind --leak-check=full --show-leak-kinds=all ./a.out koto.cub

// #include "../mlx_linux/mlx.h"
// #include "../includes/key_linux.h"
// #include "../includes/libft.h"
// #include <stdio.h>
// #include <math.h>
// #include <stdlib.h>

#include "../includes/cub3d.h"


// static int	compare(const void *first, const void *second)
// {
// 	if (*(int *)first > *(int *)second)
// 		return (1);
// 	else if (*(int *)first < *(int *)second)
// 		return (-1);
// 	else
// 		return (0);
// }

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
	int i;
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}



////////////// end for sprite 2 ////////////


// int	key_hook(int keycode, t_info *info)
// {
// 	printf("keycode : %d\n", keycode);
// 	return 0;
// }

// int mouse_hook(int mousecode, t_info *info)
// {
// 	printf("mousecode : %d\n", mousecode);
// 	return 0;
// }

int close_window(int keycode, t_info *info)
{
	if (keycode == K_ESC)
		mlx_destroy_window(info->mlx, info->win);
	return 0;
}

int close_window_redx(void)
{
	// exit_successful(info); // I want to exec this row...
	exit(EXIT_SUCCESS);
	return (0);
}

// int print_hello(t_info *info)
// {
// 	printf("Hello~~~~\n");
// 	return 0;
// }

// int print_bye(t_info *info)
// {
// 	printf("bye!!!!!\n");
// 	return 0;
// }

t_sprite	sprite[num_sprites] =
{
	{3.5, 1.5},//, SPRITE_TEXTURE},
	{3.5, 2.5},//, SPRITE_TEXTURE},
	{5.5, 4.5},//, SPRITE_TEXTURE},
	{2.5, 5.5},//, SPRITE_TEXTURE},
	{6.5, 6.5},//, SPRITE_TEXTURE},
};

int	world_map[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,0,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1},
	{1,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1},
	{1,1,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};


////////////////////////////////////////////////////

void	draw(t_info *info)
{
	for (int y = 0; y < R_HEIGHT; y++)
	{
		for (int x = 0; x < R_WIDTH; x++)
		{
			info->img.data[y * R_WIDTH + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void calc(t_info *info)
{

	////////////// draw ceiling and floor /////////////////
	int color;

	for (int y = 0; y < R_HEIGHT; y++) // in order to draw left to right, buf[y][x]
	{
		for (int x = 0; x < R_WIDTH; x++)
		{
			if (y < R_HEIGHT / 2)
				color = info->ceiling_color;//0x9dcce0; // color of ceiling
			else
				color = info->floor_color;//0xb26235; // color of floor
			info->buf[y][x] = color;
		}
	}

	////////////// end draw ceiling and floor /////////////////

	int x = 0;

	while (x < R_WIDTH)
	{
		double camera_x = 2 * x / (double)R_WIDTH - 1;
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
			if (world_map[map_x][map_y] == 1)///////////
				hit = 1;
		}
		if (side == EW) // EW?
			perp_wall_dist = (map_x - info->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - info->pos_y + (1 - step_y) / 2) / ray_dir_y;

		int line_height = (int)(R_HEIGHT / perp_wall_dist);

		int draw_start = -line_height / 2 + R_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + R_HEIGHT / 2;
		if (draw_end > R_HEIGHT)
			draw_end = R_HEIGHT - 1;

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
		double tex_pos = (draw_start - R_HEIGHT / 2 + line_height / 2) * step;
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
		double sprite_y = sprite[sprite_order[i]].y - info->pos_y;

		//transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
		// [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [                 ]
		// [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

		double inv_det = 1.0 / (info->plane_x * info->dir_y - info->dir_x * info->plane_y); //required for correct matrix multiplication

		double transform_x = inv_det * (info->dir_y * sprite_x - info->dir_x * sprite_y);
		double transform_y = inv_det * (-info->plane_y * sprite_x + info->plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(sprite_distance[i])

		int sprite_screen_x = (int)((R_WIDTH / 2) * (1 + transform_x / transform_y));

		//parameters for scaling and moving the sprites
		//#define u_div 1
		// #define v_div 1
		// #define v_move 0.0///////////
		//int v_move_screen = (int)(v_move / transform_y);

		//calculate R_HEIGHT of the sprite on screen
		int sprite_height = (int)fabs(R_HEIGHT / transform_y); //using "transform_y" instead of the real distance prevents fisheye
		// int sprite_height = (int)fabs((R_HEIGHT / transform_y) / v_div); //using "transform_y" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int draw_start_y = -sprite_height / 2 + R_HEIGHT / 2;// + v_move_screen;
		if(draw_start_y < 0) draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + R_HEIGHT / 2;// + v_move_screen;
		if(draw_end_y >= R_HEIGHT) draw_end_y = R_HEIGHT - 1;

		//calculate R_WIDTH of the sprite
		int sprite_width = (int)fabs(R_HEIGHT / transform_y);
		// int sprite_width = (int)fabs((R_HEIGHT / transform_y) / u_div);
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if(draw_start_x < 0) draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if(draw_end_x >= R_WIDTH) draw_end_x = R_WIDTH - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
		{
			int tex_x = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * TEX_WIDTH / sprite_width) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) z_buffer, with perpendicular distance
			if(transform_y > 0 && stripe > 0 && stripe < R_WIDTH && transform_y < info->z_buffer[stripe])
			for(int y = draw_start_y; y < draw_end_y; y++) //for every pixel of the current stripe
			{
				int d = y * 256 - R_HEIGHT * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
				int tex_y = ((d * TEX_HEIGHT) / sprite_height) / 256;
				int color = info->texture[SPRITE_TEXTURE][TEX_WIDTH * tex_y + tex_x]; //get current color from the texture
				if(color & 0x00FFFFFF) // color & 0x00FFFFFF == 0 is black  =>  black to invisible
					info->buf[y][stripe] = color;
			}
		}
	}
}

////////////////////////////////////////////////////


int	key_update(t_info *info)
{
	if (info->key_ar_u && info->key_ar_d)
		info->move_speed = 0.008;
	else if (info->key_ar_u && !(info->key_ar_d))
		info->move_speed = 0.023;
	else if (!(info->key_ar_u) && info->key_ar_d)
		info->move_speed = 0.002;
	else if (!(info->key_ar_u) && !(info->key_ar_d))
		info->move_speed = 0.008;
	// move forwards if no wall in front of you
	if (info->key_w)
	{
		if (!world_map[(int)(info->pos_x + info->dir_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x += info->dir_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y + info->dir_y * info->move_speed)])
			info->pos_y += info->dir_y * info->move_speed;
	}
	//move backwards if no wall behind you
	if (info->key_s)
	{
		if (!world_map[(int)(info->pos_x - info->dir_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x -= info->dir_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y - info->dir_y * info->move_speed)])
			info->pos_y -= info->dir_y * info->move_speed;
	}
	////////////move right-step if no wall right of you
	if (info->key_d)
	{
		if (!world_map[(int)(info->pos_x + info->plane_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x += info->plane_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y + info->plane_y * info->move_speed)])
			info->pos_y += info->plane_y * info->move_speed;
	}
	////////////move left-step if no wall left of you
	if (info->key_a)
	{
		if (!world_map[(int)(info->pos_x - info->plane_x * info->move_speed)][(int)(info->pos_y)])
			info->pos_x -= info->plane_x * info->move_speed;
		if (!world_map[(int)(info->pos_x)][(int)(info->pos_y - info->plane_y * info->move_speed)])
			info->pos_y -= info->plane_y * info->move_speed;
	}
	//rotate to the right
	if (info->key_ar_r)
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
	if (info->key_ar_l)
	{
		//both camera direction and camera plane must be rotated
		double old_dir_x = info->dir_x;
		info->dir_x = info->dir_x * cos(info->rot_speed) - info->dir_y * sin(info->rot_speed);
		info->dir_y = old_dir_x * sin(info->rot_speed) + info->dir_y * cos(info->rot_speed);
		double old_plane_x = info->plane_x;
		info->plane_x = info->plane_x * cos(info->rot_speed) - info->plane_y * sin(info->rot_speed);
		info->plane_y = old_plane_x * sin(info->rot_speed) + info->plane_y * cos(info->rot_speed);
	}
	if (info->key_esc)
		exit_successful(info);
	return (0);
}

int main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

void	exit_successful(t_info *info)
{
	int	i;

	i = 0;
	safe_free(info->east_path);
	safe_free(info->west_path);
	safe_free(info->south_path);
	safe_free(info->north_path);
	safe_free(info->sprite_path);
	while (info->map[i])
		safe_free(info->map[i++]);
	printf("thank you for playing!\n");
	exit(EXIT_SUCCESS);
}

int	key_press(int key, t_info *info)
{
	if (key == K_ESC)
		info->key_esc = 1;
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_AR_R)
		info->key_ar_r = 1;
	else if (key == K_AR_L)
		info->key_ar_l = 1;
	else if (key == K_AR_U)
		info->key_ar_u = 1;
	else if (key == K_AR_D)
		info->key_ar_d = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		info->key_esc = 1;
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_AR_R)
		info->key_ar_r = 0;
	else if (key == K_AR_L)
		info->key_ar_l = 0;
	else if (key == K_AR_U)
		info->key_ar_u = 0;
	else if (key == K_AR_D)
		info->key_ar_d = 0;
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
//CAUSE OF DIRECTION CALC, NEED TO MODIFY WALL DEFINITION
	load_image(info, info->texture[NORTH_TEXTURE], "images/koto_west.xpm", &img);
	load_image(info, info->texture[SOUTH_TEXTURE], "images/koto_east.xpm", &img);
	load_image(info, info->texture[WEST_TEXTURE], "images/koto_south.xpm", &img);
	load_image(info, info->texture[EAST_TEXTURE], "images/koto_north.xpm", &img);
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







// --------------------------- //
// --------------------------- //
// --------------------------- //
// --------------------------- //
// --------------------------- //
// --------------------------- //
// --------------------------- //
// --------------------------- //






// void init_info_temp(t_info *info)
// {
// 	info->mlx = mlx_init();

// 	info->pos_x = 1.5;
// 	info->pos_y = 1.5;

// // // NORTH
// // 	info->dir_x = -1.0;
// // 	info->dir_y = 0.0;
// // 	info->plane_x = 0.0;
// // 	info->plane_y = 0.66;
// // // WEST
// // 	info->dir_x = 0.0;
// // 	info->dir_y = -1.0;
// // 	info->plane_x = -0.66;
// // 	info->plane_y = 0.0;
// // // EAST
// // 	info->dir_x = 0.0;
// // 	info->dir_y = 1.0;
// // 	info->plane_x = 0.66;
// // 	info->plane_y = 0.0;
// // SOUTH
// 	info->dir_x = 1.0;
// 	info->dir_y = 0.0;
// 	info->plane_x = 0.0;
// 	info->plane_y = -0.66;



// 	info->move_speed = 0.008;
// 	info->rot_speed = 0.005;

// 	info->key_w = 0;
// 	info->key_s = 0;
// 	info->key_d = 0;
// 	info->key_a = 0;
// 	info->key_ar_r = 0;
// 	info->key_ar_l = 0;
// 	info->key_ar_u = 0;
// 	info->key_ar_d = 0;
// 	info->key_esc = 0;

// 	info->floor_red = 130;
// 	info->floor_green = 150;
// 	info->floor_blue = 100;
// 	info->ceiling_red = 60;
// 	info->ceiling_green = 190;
// 	info->ceiling_blue = 245;
// }

// int main(void)
// {
// 	t_info	info;

// 	init_info_temp(&info);
// 	get_floor_ceiling_color(&info);
// 	int tex_num = 5;

// 	for (int i = 0; i < R_HEIGHT; i++)
// 	{
// 		for (int j = 0; j < R_WIDTH; j++)
// 			info.buf[i][j] = 0;
// 	}

// 	if (!(info.texture = (int **)malloc(sizeof(int *) * tex_num)))
// 		return (-1);
// 	for (int i = 0; i < tex_num; i++)
// 	{
// 		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH))))
// 			return (-1);
// 	}
// 	for (int i = 0; i < tex_num; i++)
// 	{
// 		for (int j = 0; j < TEX_HEIGHT * TEX_WIDTH; j++)
// 			info.texture[i][j] = 0;
// 	}

// 	load_texture(&info);

// 	info.win = mlx_new_window(info.mlx, R_WIDTH, R_HEIGHT, "mocomoco world!!!!");

// 	info.img.img = mlx_new_image(info.mlx, R_WIDTH, R_HEIGHT);
// 	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);


// 	// mlx_key_hook(info.win, key_hook, &info);
// 	// mlx_mouse_hook(info.win, mouse_hook, &info);
// 	mlx_hook(info.win, 2, 1L<<0, close_window, &info);	//close window when ESC pressed
// 	mlx_hook(info.win, 33, 1L<<17, close_window_redx, &info);	//close window when red cross pushed // for 2nd arg, old ver is 17 , but latest ver is 33
// 	// mlx_hook(info.win, 7, 1L<<4, print_hello, &info);	//enter window 
// 	// mlx_hook(info.win, 8, 1L<<5, print_bye, &info);		//leave window


// 	mlx_loop_hook(info.mlx, &main_loop, &info);

// 	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &info);
// 	mlx_hook(info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &info);

// 	mlx_loop(info.mlx);// when check leak, comment out this row, and do fsanitize
// 	return 0;
// }



// // // --------------------------- //




// int	main(int argc, char *argv[])
// {
// 	t_info	info;

// 	init_info(&info);
// 	is_correct_arg(argc, argv, &info);
// 	get_mapfile_info(argv[1], &info);
// 	analyze_mapdata(&info);
// 	get_sprite_info(&info);
// 	get_window_size(&info);
// 	printf("STARTING GAME\n");


// DEBUG_print_info(&info);
// printf("here is end of main.c\n");
	
// 	return (0);
// }
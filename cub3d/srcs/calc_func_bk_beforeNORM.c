// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   calc_func.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/03/06 11:49:18 by skotoyor          #+#    #+#             */
// /*   Updated: 2021/03/06 11:49:33 by skotoyor         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/cub3d.h"

// void calc_func(t_info *info)
// {

// 	////////////// draw ceiling and floor /////////////////
// 	int color;

// 	for (int y = 0; y < info->r_height; y++) // in order to draw left to right, buf[y][x]
// 	{
// 		for (int x = 0; x < info->r_width; x++)
// 		{
// 			if (y < info->r_height / 2)
// 				color = info->ceiling_color;//0x9dcce0; // color of ceiling
// 			else
// 				color = info->floor_color;//0xb26235; // color of floor
// 			info->buf[y][x] = color;
// 		}
// 	}

// 	////////////// end draw ceiling and floor /////////////////

// 	int x = 0;

// 	while (x < info->r_width)
// 	{
// 		double camera_x = 2 * x / (double)info->r_width - 1;
// 		double ray_dir_x = info->dir_x + info->plane_x * camera_x;
// 		double ray_dir_y = info->dir_y + info->plane_y * camera_x;

// 		int map_x = (int)info->pos_x;
// 		int map_y = (int)info->pos_y;

// 		double side_dist_x;
// 		double side_dist_y;

// 		double delta_dist_x = fabs(1 / ray_dir_x);
// 		double delta_dist_y = fabs(1 / ray_dir_y);
// 		double perp_wall_dist;

// 		int step_x;
// 		int step_y;

// 		int hit = 0;
// 		int side;

// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (info->pos_x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - info->pos_x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (info->pos_y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - info->pos_y) * delta_dist_y;
// 		}

// 		while (!hit)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = EW; // EW?
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = NS; // NS?
// 			}
// 			if (info->world_map[map_x][map_y] == 1)///////////0303
// 				hit = 1;
// 		}
// 		if (side == EW) // EW?
// 			perp_wall_dist = (map_x - info->pos_x + (1 - step_x) / 2) / ray_dir_x;
// 		else
// 			perp_wall_dist = (map_y - info->pos_y + (1 - step_y) / 2) / ray_dir_y;

// 		int line_height = (int)(info->r_height / perp_wall_dist);

// 		int draw_start = -line_height / 2 + info->r_height / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + info->r_height / 2;
// 		if (draw_end > info->r_height)
// 			draw_end = info->r_height - 1;

// 		// int tex_num = info->world_map[map_x][map_y];

// //////////////////////////////// choose texture
// 		int tex_num;

// 		if (side == EW)
// 		{
// 			if (map_x > info->pos_x)
// 				tex_num = WEST_TEXTURE;
// 			else
// 				tex_num = EAST_TEXTURE;
// 		}
// 		else
// 		{
// 			if (map_y > info->pos_y)
// 				tex_num = SOUTH_TEXTURE;
// 			else
// 				tex_num = NORTH_TEXTURE;
// 		}

// ////////////////////////////////


// 		double wall_x;
// 		if (side == EW)
// 			wall_x = info->pos_y + perp_wall_dist * ray_dir_y;
// 		else
// 			wall_x = info->pos_x + perp_wall_dist * ray_dir_x;
// 		wall_x -= floor(wall_x);

// 		// x coordinate on the texture
// 		int tex_x = (int)(wall_x * (double)TEX_WIDTH);//0306tex
// 		if (side == EW && ray_dir_x > 0)
// 			tex_x = TEX_WIDTH - tex_x - 1;//0306tex
// 		if (side == NS && ray_dir_y < 0)
// 			tex_x = TEX_WIDTH - tex_x - 1;//0306tex

// 		double step = 1.0 * TEX_HEIGHT / line_height;//0306tex
// 		// Starting texture coordinate
// 		double tex_pos = (draw_start - info->r_height / 2 + line_height / 2) * step;
// 		for (int y = draw_start; y < draw_end; y++)
// 		{
// 			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
// 			int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);//0306tex
// 			tex_pos += step;


// 			// int color = info->texture[tex_num][TEX_HEIGHT * tex_y + tex_x];
// 			int color = info->tex[tex_num].addr[TEX_HEIGHT * tex_y + tex_x];//0306tex
// 			info->buf[y][x] = color;
// 		}

// 		/////////// for fprite //////////////////////////////////////
// 		//SET THE z_buffer FOR THE SPRITE CASTING
// 		info->z_buffer[x] = perp_wall_dist; //perpendicular distance is used
// 		/////////// end for fprite //////////////////////////////////////

// // printf("pos_x:%2.2f, pos_y:%2.2f, dir_x:%2.2f, dir_y:%2.2f, plane_x:%2.2f, plane_y:%2.2f\n", info->pos_x, info->pos_y, info->dir_x, info->dir_y, info->plane_x, info->plane_y);
// // printf("buf[0][0]:%x\n", info->buf[0][0]);
// 		x++;
// 	}

// 	//SPRITE CASTING
// 	//sort sprites from far to close
// 	for(int i = 0; i < info->num_sprite; i++)
// 	{
// 		info->sprite_order[i] = i;
// 		info->sprite_distance[i] = ((info->pos_x - info->sp[i].x) * (info->pos_x - info->sp[i].x) + (info->pos_y - info->sp[i].y) * (info->pos_y - info->sp[i].y)); //sqrt not taken, unneeded
// 	}
// 	sort_sprites(info->sprite_order, info->sprite_distance, info->num_sprite, info);
// 	//after sorting the sprites, do the projection and draw them
// 	for(int i = 0; i < info->num_sprite; i++)
// 	{
// 		//translate sprite position to relative to camera
// 		double sprite_x = info->sp[info->sprite_order[i]].x - info->pos_x;
// 		double sprite_y = info->sp[info->sprite_order[i]].y - info->pos_y;

// 		//transform sprite with the inverse camera matrix
// 		// [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
// 		// [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [                 ]
// 		// [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

// 		double inv_det = 1.0 / (info->plane_x * info->dir_y - info->dir_x * info->plane_y); //required for correct matrix multiplication

// 		double transform_x = inv_det * (info->dir_y * sprite_x - info->dir_x * sprite_y);
// 		double transform_y = inv_det * (-info->plane_y * sprite_x + info->plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(info->sprite_distance[i])

// 		int sprite_screen_x = (int)((info->r_width / 2) * (1 + transform_x / transform_y));

// 		//parameters for scaling and moving the sprites
// 		//#define u_div 1
// 		// #define v_div 1
// 		// #define v_move 0.0///////////
// 		//int v_move_screen = (int)(v_move / transform_y);

// 		//calculate info->r_height of the sprite on screen
// 		int sprite_height = (int)fabs(info->r_height / transform_y); //using "transform_y" instead of the real distance prevents fisheye
// 		// int sprite_height = (int)fabs((info->r_height / transform_y) / v_div); //using "transform_y" instead of the real distance prevents fisheye
// 		//calculate lowest and highest pixel to fill in current stripe
// 		int draw_start_y = -sprite_height / 2 + info->r_height / 2;// + v_move_screen;
// 		if(draw_start_y < 0) draw_start_y = 0;
// 		int draw_end_y = sprite_height / 2 + info->r_height / 2;// + v_move_screen;
// 		if(draw_end_y >= info->r_height) draw_end_y = info->r_height - 1;

// 		//calculate info->r_width of the sprite
// 		int sprite_width = (int)fabs(info->r_height / transform_y);
// 		// int sprite_width = (int)fabs((info->r_height / transform_y) / u_div);
// 		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
// 		if(draw_start_x < 0) draw_start_x = 0;
// 		int draw_end_x = sprite_width / 2 + sprite_screen_x;
// 		if(draw_end_x >= info->r_width) draw_end_x = info->r_width - 1;

// 		//loop through every vertical stripe of the sprite on screen
// 		for(int stripe = draw_start_x; stripe < draw_end_x; stripe++)
// 		{
// 			int tex_x = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * TEX_WIDTH / sprite_width) / 256);//0306tex
// 			//the conditions in the if are:
// 			//1) it's in front of camera plane so you don't see things behind you
// 			//2) it's on the screen (left)
// 			//3) it's on the screen (right)
// 			//4) z_buffer, with perpendicular distance
// 			if(transform_y > 0 && stripe > 0 && stripe < info->r_width && transform_y < info->z_buffer[stripe])
// 			for(int y = draw_start_y; y < draw_end_y; y++) //for every pixel of the current stripe
// 			{
// 				int d = y * 256 - info->r_height * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
// 				int tex_y = ((d * TEX_HEIGHT) / sprite_height) / 256;//0306tex
// 				// int color = info->texture[SPRITE_TEXTURE][TEX_WIDTH * tex_y + tex_x]; //get current color from the texture
// 				int color = info->tex[SPRITE_TEXTURE].addr[TEX_WIDTH * tex_y + tex_x]; //get current color from the texture//0306tex
// 				if(color & 0x00FFFFFF) // color & 0x00FFFFFF == 0 is black  =>  black to invisible
// 					info->buf[y][stripe] = color;
// 			}
// 		}
// 	}
// }

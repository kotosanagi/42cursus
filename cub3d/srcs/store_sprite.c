/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:26:56 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 16:54:19 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	store_sprite(t_raycasting *rc, t_info *info)
{
(void)rc;
	////////////  store_sprite() ///////////////
	//SPRITE CASTING
	//sort sprites from far to close
	int i = 0;
	// for(int i = 0; i < info->num_sprite; i++)
	while (i < info->num_sprite)
	{
		info->sprite_order[i] = i;
		info->sprite_distance[i] = ((info->pos_x - info->sp[i].x) * (info->pos_x - info->sp[i].x) + (info->pos_y - info->sp[i].y) * (info->pos_y - info->sp[i].y)); //sqrt not taken, unneeded
		i++;
	}
	sort_sprites(info->sprite_order, info->sprite_distance, info->num_sprite, info);
	//after sorting the sprites, do the projection and draw them
	i = 0;
	while (i < info->num_sprite)
	{
		//translate sprite position to relative to camera
		double sprite_x = info->sp[info->sprite_order[i]].x - info->pos_x;
		double sprite_y = info->sp[info->sprite_order[i]].y - info->pos_y;

		//transform sprite with the inverse camera matrix
		// [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
		// [               ]       =  1/(plane_x*dir_y-dir_x*plane_y) *   [                 ]
		// [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

		double inv_det = 1.0 / (info->plane_x * info->dir_y - info->dir_x * info->plane_y); //required for correct matrix multiplication

		double transform_x = inv_det * (info->dir_y * sprite_x - info->dir_x * sprite_y);
		double transform_y = inv_det * (-info->plane_y * sprite_x + info->plane_x * sprite_y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(info->sprite_distance[i])

		int sprite_screen_x = (int)((info->r_width / 2) * (1 + transform_x / transform_y));

		//parameters for scaling and moving the sprites
		//#define u_div 1
		// #define v_div 1
		// #define v_move 0.0///////////
		//int v_move_screen = (int)(v_move / transform_y);

		//calculate info->r_height of the sprite on screen
		int sprite_height = (int)fabs(info->r_height / transform_y); //using "transform_y" instead of the real distance prevents fisheye
		// int sprite_height = (int)fabs((info->r_height / transform_y) / v_div); //using "transform_y" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int draw_start_y = -sprite_height / 2 + info->r_height / 2;// + v_move_screen;
		if(draw_start_y < 0) draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + info->r_height / 2;// + v_move_screen;
		if(draw_end_y >= info->r_height) draw_end_y = info->r_height - 1;

		//calculate info->r_width of the sprite
		int sprite_width = (int)fabs(info->r_height / transform_y);
		// int sprite_width = (int)fabs((info->r_height / transform_y) / u_div);
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if(draw_start_x < 0) draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if(draw_end_x >= info->r_width) draw_end_x = info->r_width - 1;

		//loop through every vertical stripe of the sprite on screen
		int stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			int tex_x = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * TEX_WIDTH / sprite_width) / 256);//0306tex
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) z_buffer, with perpendicular distance
			if(transform_y > 0 && stripe > 0 && stripe < info->r_width && transform_y < info->z_buffer[stripe])
			{
				int y = draw_start_y;
				while (y < draw_end_y) //for every pixel of the current stripe
				{
					int d = y * 256 - info->r_height * 128 + sprite_height * 128; //256 and 128 factors to avoid floats
					int tex_y = ((d * TEX_HEIGHT) / sprite_height) / 256;//0306tex
					// int color = info->texture[SPRITE_TEXTURE][TEX_WIDTH * tex_y + tex_x]; //get current color from the texture
					int color = info->tex[SPRITE_TEXTURE].addr[TEX_WIDTH * tex_y + tex_x]; //get current color from the texture//0306tex
					if(color & 0x00FFFFFF) // color & 0x00FFFFFF == 0 is black  =>  black to invisible
						info->buf[y][stripe] = color;
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
	//////////// end store_sprite() ///////////////
}

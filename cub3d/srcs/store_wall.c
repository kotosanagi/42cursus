/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:54:37 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 13:00:35 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	store_wall(t_raycasting *rc, t_info *info)
{
(void)rc;

	int x = 0;
	while (x < info->r_width)
	{
		double camera_x = 2 * x / (double)info->r_width - 1;
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
			if (info->world_map[map_x][map_y] == 1)///////////0303
				hit = 1;
		}
		if (side == EW) // EW?
			perp_wall_dist = (map_x - info->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - info->pos_y + (1 - step_y) / 2) / ray_dir_y;

		int line_height = (int)(info->r_height / perp_wall_dist);

		int draw_start = -line_height / 2 + info->r_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + info->r_height / 2;
		if (draw_end > info->r_height)
			draw_end = info->r_height - 1;

		// int tex_num = info->world_map[map_x][map_y];

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
		int tex_x = (int)(wall_x * (double)TEX_WIDTH);//0306tex
		if (side == EW && ray_dir_x > 0)
			tex_x = TEX_WIDTH - tex_x - 1;//0306tex
		if (side == NS && ray_dir_y < 0)
			tex_x = TEX_WIDTH - tex_x - 1;//0306tex

		double step = 1.0 * TEX_HEIGHT / line_height;//0306tex
		// Starting texture coordinate
		double tex_pos = (draw_start - info->r_height / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);//0306tex
			tex_pos += step;


			// int color = info->texture[tex_num][TEX_HEIGHT * tex_y + tex_x];
			int color = info->tex[tex_num].addr[TEX_HEIGHT * tex_y + tex_x];//0306tex
			info->buf[y][x] = color;
		}

		/////////// for fprite //////////////////////////////////////
		//SET THE z_buffer FOR THE SPRITE CASTING
		info->z_buffer[x] = perp_wall_dist; //perpendicular distance is used
		/////////// end for fprite //////////////////////////////////////

// printf("pos_x:%2.2f, pos_y:%2.2f, dir_x:%2.2f, dir_y:%2.2f, plane_x:%2.2f, plane_y:%2.2f\n", info->pos_x, info->pos_y, info->dir_x, info->dir_y, info->plane_x, info->plane_y);
// printf("buf[0][0]:%x\n", info->buf[0][0]);
		x++;
	}

}

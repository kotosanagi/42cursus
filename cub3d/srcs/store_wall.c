/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:54:37 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/06 14:23:01 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	store_wall(t_raycasting *rc, t_info *info)
{
	rc->x = 0;
	while (rc->x < info->r_width)
	{
		rc->camera_x = 2 * rc->x / (double)info->r_width - 1;
		rc->ray_dir_x = info->dir_x + info->plane_x * rc->camera_x;
		rc->ray_dir_y = info->dir_y + info->plane_y * rc->camera_x;

		rc->map_x = (int)info->pos_x;
		rc->map_y = (int)info->pos_y;

		// double side_dist_x;
		// double side_dist_y;

		rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
		rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
		// double perp_wall_dist;

		// int step_x;
		// int step_y;



		if (rc->ray_dir_x < 0)
		{
			rc->step_x = -1;
			rc->side_dist_x = (info->pos_x - rc->map_x) * rc->delta_dist_x;
		}
		else
		{
			rc->step_x = 1;
			rc->side_dist_x = (rc->map_x + 1.0 - info->pos_x) * rc->delta_dist_x;
		}
		if (rc->ray_dir_y < 0)
		{
			rc->step_y = -1;
			rc->side_dist_y = (info->pos_y - rc->map_y) * rc->delta_dist_y;
		}
		else
		{
			rc->step_y = 1;
			rc->side_dist_y = (rc->map_y + 1.0 - info->pos_y) * rc->delta_dist_y;
		}

		rc->hit = 0;
		// int side;
		while (!rc->hit)
		{
			if (rc->side_dist_x < rc->side_dist_y)
			{
				rc->side_dist_x += rc->delta_dist_x;
				rc->map_x += rc->step_x;
				rc->side = EW; // EW?
			}
			else
			{
				rc->side_dist_y += rc->delta_dist_y;
				rc->map_y += rc->step_y;
				rc->side = NS; // NS?
			}
			if (info->world_map[rc->map_x][rc->map_y] == 1)///////////0303
				rc->hit = 1;
		}
		if (rc->side == EW)// EW?
			rc->perp_wall_dist = (rc->map_x - info->pos_x + (1 - rc->step_x) / 2) / rc->ray_dir_x;
		else
			rc->perp_wall_dist = (rc->map_y - info->pos_y + (1 - rc->step_y) / 2) / rc->ray_dir_y;

		rc->line_height = (int)(info->r_height / rc->perp_wall_dist);

		rc->draw_start = -rc->line_height / 2 + info->r_height / 2;
		if (rc->draw_start < 0)
			rc->draw_start = 0;
		rc->draw_end = rc->line_height / 2 + info->r_height / 2;
		if (rc->draw_end > info->r_height)
			rc->draw_end = info->r_height - 1;

		// int tex_num = info->world_map[rc->map_x][rc->map_y];

//////////////////////////////// choose texture
		// int tex_num;

		if (rc->side == EW)
		{
			// if (rc->map_x > info->pos_x)
			if (rc->map_x < info->pos_x)
				rc->tex_num = WEST_TEXTURE;
			else
				rc->tex_num = EAST_TEXTURE;
		}
		else
		{
			// if (rc->map_y > info->pos_y)
			if (rc->map_y < info->pos_y)
				rc->tex_num = SOUTH_TEXTURE;
			else
				rc->tex_num = NORTH_TEXTURE;
		}

////////////////////////////////


		// double wall_x;
		if (rc->side == EW)
			rc->wall_x = info->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
		else
			rc->wall_x = info->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
		rc->wall_x -= floor(rc->wall_x);

		// x coordinate on the texture
		rc->tex_x = (int)(rc->wall_x * (double)TEX_WIDTH);//0306tex
		if (rc->side == EW && rc->ray_dir_x > 0)
			rc->tex_x = TEX_WIDTH - rc->tex_x - 1;//0306tex
		if (rc->side == NS && rc->ray_dir_y < 0)
			rc->tex_x = TEX_WIDTH - rc->tex_x - 1;//0306tex

		rc->step = 1.0 * TEX_HEIGHT / rc->line_height;//0306tex
		// Starting texture coordinate
		rc->tex_pos = (rc->draw_start - info->r_height / 2 + rc->line_height / 2) * rc->step;
		rc->y = rc->draw_start;
		// for (int y = rc->draw_start; y < rc->draw_end; y++)
		while (rc->y < rc->draw_end)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			rc->tex_y = (int)rc->tex_pos & (TEX_HEIGHT - 1);//0306tex
			rc->tex_pos += rc->step;
			// int color = info->texture[rc->tex_num][TEX_HEIGHT * rc->tex_y + rc->tex_x];
			rc->color = info->tex[rc->tex_num].addr[TEX_HEIGHT * rc->tex_y + rc->tex_x];//0306tex
			info->buf[rc->y][rc->x] = rc->color;
			rc->y += 1;
		}

		/////////// for fprite //////////////////////////////////////
		//SET THE z_buffer FOR THE SPRITE CASTING
		info->z_buffer[rc->x] = rc->perp_wall_dist; //perpendicular distance is used
		/////////// end for fprite //////////////////////////////////////

// printf("pos_x:%2.2f, pos_y:%2.2f, dir_x:%2.2f, dir_y:%2.2f, plane_x:%2.2f, plane_y:%2.2f\n", info->pos_x, info->pos_y, info->dir_x, info->dir_y, info->plane_x, info->plane_y);
// printf("buf[0][0]:%x\n", info->buf[0][0]);
		rc->x += 1;
	}
}

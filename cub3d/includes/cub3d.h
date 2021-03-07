/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:14:55 by skotoyor          #+#    #+#             */
/*   Updated: 2021/03/07 14:54:33 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

/*
** Keyboard LETTERS
*/

# define K_A 97
# define K_B 98
# define K_C 99
# define K_D 100
# define K_E 101
# define K_F 102
# define K_G 103
# define K_H 104
# define K_I 105
# define K_J 106
# define K_K 107
# define K_L 108
# define K_M 109
# define K_N 110
# define K_O 111
# define K_P 112
# define K_Q 113
# define K_R 114
# define K_S 115
# define K_T 116
# define K_U 117
# define K_V 118
# define K_W 119
# define K_X 120
# define K_Y 121
# define K_Z 122

/*
** Keyboard ARROWS
*/

# define K_AR_L 65361
# define K_AR_R 65363
# define K_AR_U 65362
# define K_AR_D 65364

/*
** Keyboard NUMPAD
*/

# define K_NP_DIV 65455
# define K_NP_MUL 65450
# define K_NP_MIN 65453
# define K_NP_PLU 65451
# define K_NP_1 65436
# define K_NP_2 65433
# define K_NP_3 65435
# define K_NP_4 65430
# define K_NP_5 65437
# define K_NP_6 65432
# define K_NP_7 65429
# define K_NP_8 65431
# define K_NP_9 65434

/*
** Keyboard MISC
*/

# define K_SP 21
# define K_ESC 65307
# define K_TAB 65289

/*
** Mouse
*/

# define M_CLK_L 1
# define M_CLK_M 2
# define M_CLK_R 3
# define M_SCR_U 4
# define M_SCR_D 5

/*
** for cub3d
*/

# define R_WIDTH 512
# define R_HEIGHT 384
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAP_WIDTH 80
# define MAP_HEIGHT 80
# define NS 1
# define EW 0
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define NORTH_TEXTURE 0
# define SOUTH_TEXTURE 1
# define WEST_TEXTURE 2
# define EAST_TEXTURE 3
# define SPRITE_TEXTURE 4
# define RED 0
# define GREEN 1
# define BLUE 2

typedef struct	s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_img
{
	void	*img;
	// char		*data;////0304
	int		*data;////before 0304
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct		s_tex
{
	unsigned int	*addr;
	int				w;
	int				h;
}					t_tex;


typedef struct	s_info
{
	int			r_width;
	int			r_height;
	char		*east_path;
	char		*west_path;
	char		*south_path;
	char		*north_path;
	char		*sprite_path;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			floor_red;
	int			floor_green;
	int			floor_blue;
	int			ceiling_red;
	int			ceiling_green;
	int			ceiling_blue;
	int			floor_color;
	int			ceiling_color;
	int			num_sprite;
	char		*map[MAP_HEIGHT];//////////need to modify of MAP_WIDTH and MAP_HEIGHT in main.c
	int			world_map[MAP_HEIGHT][MAP_WIDTH];
	int			save_flg;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_a;
	int			key_ar_r;
	int			key_ar_l;
	int			key_ar_u;
	int			key_ar_d;
	int			key_esc;
	double		move_speed;
	double		rot_speed;
	int			map_h;
	void		*mlx;
	void		*win;
	t_sprite	*sp;
	double		*z_buffer;
	t_img		img;
	int			**buf;
	int			buf_malloc_flg;
	t_tex		tex[5];
	int			*sprite_order;//[num_sprites];
	double		*sprite_distance;//[num_sprites];
}				t_info;

typedef struct		s_pair
{
	double			first;
	int				second;
}					t_pair;

typedef struct		s_raycasting
{
	int		color;
	int		y;
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		i;
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		d;
}					t_raycasting;

typedef struct		s_mapdata
{
	int	ret;
	int	start;
	int	end;
	int	i;
}					t_mapdata;

typedef struct		s_header
{
	unsigned int	file_size;
	unsigned int	offset;
	unsigned int	header_size;
	unsigned int	planes;
	unsigned int	bpp;
}					t_header;

void	safe_free(void *p);
void	error_exit(char *message);
void	error_free_exit(char *msg, t_info *info);
void	free_elem(char **elem);
void	error_free_elem_exit(char *msg, t_info *info, char **elem);
void	is_correct_arg(int argc, char *argv[], t_info *info);
void	init_info(t_info *info);
void	get_mapfile_info(char *path, t_info *info);
void	get_mappart_data(int fd, char **line, t_info *info);
void	error_free_line(char *msg, t_info *info, char *str, int fd);
void	error_fd_close(char *msg, t_info *info, int fd);
int		is_enough_8elements(t_info *info);
int		cnt_elem(char **elem);
int		is_num(char *str);
int		is_correct_rgb(t_info *info, char **elem, char **rgb);
int		cnt_str_c(char *str, char c);
void	get_floor_ceiling_color(t_info *info);// exec after get file info (end of read_file func)
void	analyze_mapdata(t_info *info);
void	is_closed_map(t_info *info);
void	get_sprite_info(t_info *info);
void	get_window_size(t_info *info);
void	load_texture(t_info *info);
void	key_update(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
void	sort_sprites(int *order, double *dist, int amount, t_info *info);
void	set_buf(t_info *info);
int		close_window(int keycode, t_info *info);
int		close_window_redx(void);
void	exit_successful(t_info *info);//
void	draw_func(t_info *info);
void	calc_func(t_info *info);
void	store_wall(t_raycasting *rc, t_info *info);
void	choose_texture(t_raycasting *rc, t_info *info);
void	get_wall_tex_x(t_raycasting *rc, t_info *info);
void	store_wall_tex(t_raycasting *rc, t_info *info);
void	store_sprite(t_raycasting *rc, t_info *info);
void	create_bmp(t_info *info);

//should be deleted//
void DEBUG_print_info(t_info *info);///
void	DEBUG_print_MAPPPPPP(t_info *info);///
void	DEBUG_print_tmpmap(char tmp_map[MAP_HEIGHT][MAP_WIDTH], t_info *info);////

#endif

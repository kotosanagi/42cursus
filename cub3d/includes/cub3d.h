/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:14:55 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/27 19:50:13 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// #include "key_linux.h"
# include "../mlx_linux/mlx.h"
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





///////////////////////////





# define R_WIDTH 640
# define R_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAP_WIDTH 8		// replace more large number
# define MAP_HEIGHT 8	// replace more large number

# define NS 1
# define EW 0
# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define EAST_TEXTURE 0
# define WEST_TEXTURE 1
# define NORTH_TEXTURE 2
# define SOUTH_TEXTURE 3
# define SPRITE_TEXTURE 4
# define num_sprites 5

typedef struct	s_sprite
{
	double		x;
	double		y;
	// int			texture;
}				t_sprite;

//////////// for sprite ////////////
// t_sprite	sprite[num_sprites] =
// {
// 	{3.5, 1.5},//, SPRITE_TEXTURE},
// 	{3.5, 2.5},//, SPRITE_TEXTURE},
// 	{5.5, 4.5},//, SPRITE_TEXTURE},
// 	{2.5, 5.5},//, SPRITE_TEXTURE},
// 	{6.5, 6.5},//, SPRITE_TEXTURE},
// };

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
// (start) need to get info from mapfile //
	int		r_width;
	int		r_height;
	char	*east_path;
	char	*west_path;
	char	*south_path;
	char	*north_path;
	char	*sprite_path;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	int		floor_red;
	int		floor_green;
	int		floor_blue;
	int		ceiling_red;
	int		ceiling_green;
	int		ceiling_blue;

	int		floor_color;
	int		ceiling_color;
	int		num_sprite;

	char	*map[MAP_HEIGHT];//////////need to modify of MAP_WIDTH and MAP_HEIGHT in main.c
// (end) need to get info from mapfile //

// (start) NOT need to get info from mapfile //
	int save_flg;
	int	key_w;
	int	key_s;
	int	key_d;
	int	key_a;
	int	key_ar_r;
	int	key_ar_l;
	int key_ar_u;
	int key_ar_d;
	int	key_esc;
	double	move_speed;
	double	rot_speed;
	int	map_h;

	void *mlx;
	void *win;

// (end) NOT need to get info from mapfile //

// think later //
	t_img img;
	int buf[R_HEIGHT][R_WIDTH];

	double	z_buffer[R_WIDTH];

	int **texture;

}				t_info;


////////////// for sprite 2 ////////////

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;










//////////////////////////////

























// error_func.c//
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

// get_mapfile_info.c
void	get_floor_ceiling_color(t_info *info);// exec after get file info (end of read_file func)

// analyze_mapdata.c
void	analyze_mapdata(t_info *info);

//--------------




#endif

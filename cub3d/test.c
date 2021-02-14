// gcc test.c -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz


#include "mlx_linux/mlx.h"
#include <stdio.h>

#define K_ESC 65307

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars
{
	void *mlx;
	void *mlx_window;
}				t_vars;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("keycode : %d\n", keycode);
	return 0;
}

int mouse_hook(int mousecode, t_vars *vars)
{
	printf("mousecode : %d\n", mousecode);
	return 0;
}

int close_window(int keycode, t_vars *vars)
{
	if (keycode == K_ESC)
		mlx_destroy_window(vars->mlx, vars->mlx_window);
	return 0;
}

int print_hello(t_vars *vars)
{
	printf("Hello~~~~\n");
	return 0;
}

int print_bye(t_vars *vars)
{
	printf("bye!!!!!\n");
	return 0;
}

int main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.mlx_window = mlx_new_window(vars.mlx, 400, 600, "Hello window!!!!");

	img.img = mlx_new_image(vars.mlx, 400, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int color;

	color = 0x00ff0000;

	for (int i = 30; i < 100; i++){
		for (int j = 20; j < 300; j++){
			my_mlx_pixel_put(&img, i, j, color);
			color += 1;
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.mlx_window, img.img, 0, 0);
	mlx_key_hook(vars.mlx_window, key_hook, &vars);
	mlx_mouse_hook(vars.mlx_window, mouse_hook, &vars);
	mlx_hook(vars.mlx_window, 2, 1L<<0, close_window, &vars);	//close window when ESC pressed
	mlx_hook(vars.mlx_window, 7, 1L<<4, print_hello, &vars);	//enter window 
	mlx_hook(vars.mlx_window, 8, 1L<<5, print_bye, &vars);		//leave window
//	mlx_loop_hook(vars.mlx, render_next_frame, &vars);

	mlx_loop(vars.mlx);
	return 0;
}
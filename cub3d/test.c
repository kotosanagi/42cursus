// gcc test.c -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz


#include "mlx_linux/mlx.h"

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

	for (int i = 30; i < 40; i++){
		for (int j = 20; j < 70; j++){
			my_mlx_pixel_put(&img, i, j, color);
			color += 100;
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.mlx_window, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return 0;
}
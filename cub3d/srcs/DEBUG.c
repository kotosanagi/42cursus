#include "../includes/cub3d.h"

void	DEBUG_print_MAPPPPPP(t_info *info)
{
	int i = 0;

	while (info->map[i])
		printf("%s\n", info->map[i++]);
}

void DEBUG_print_info(t_info *info)/////////////////////////
{
printf("-------\n");
printf("r_width :%d\n", info->r_width);
printf("r_height:%d\n", info->r_height);

printf("east  :%s\n", info->east_path);
printf("west  :%s\n", info->west_path);
printf("south :%s\n", info->south_path);
printf("north :%s\n", info->north_path);
printf("sprite:%s\n", info->sprite_path);

printf("pos_x  :%f\n", info->pos_x);
printf("pos_y  :%f\n", info->pos_y);
printf("dir_x  :%f\n", info->dir_x);
printf("dir_y  :%f\n", info->dir_y);
printf("plane_x:%f\n", info->plane_x);
printf("plane_y:%f\n", info->plane_y);

printf("floor_red  :%d\n", info->floor_red);
printf("floor_green:%d\n", info->floor_green);
printf("floor_blue :%d\n", info->floor_blue);
printf("ceiling_red  :%d\n", info->ceiling_red);
printf("ceiling_green:%d\n", info->ceiling_green);
printf("ceiling_blue :%d\n", info->ceiling_blue);

printf("floor_color  :%x\n", info->floor_color);
printf("ceiling_color:%x\n", info->ceiling_color);
printf("num_sprite:%d\n", info->num_sprite);



printf("------\n");
printf("map\n");
for (int y = 0; info->map[y] != NULL;)
	printf("%s\n", info->map[y++]);

printf("------\n");
printf("world_map\n");
for (int y = 0; y < MAP_HEIGHT; y++)
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		printf("%d",info->world_map[y][x]);
	}
	printf("\n");
}

printf("-------\n");
}
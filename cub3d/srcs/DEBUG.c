#include "../includes/cub3d.h"

void	DEBUG_print_MAPPPPPP(t_info *info)
{
	int i = 0;

	while (info->map[i])
		printf("%s\n", info->map[i++]);
}

void DEBUG_print_info(t_info *info)/////////////////////////
{

printf("\n");
printf("******************\n");
printf("******************\n");
printf("*** DEBUG ZONE ***\n");
printf("******************\n");
printf("******************\n");
printf("\n");


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

printf("save_flg:%d\n",info->save_flg);
printf("key_w:%d\n", info->key_w);
printf("key_s:%d\n", info->key_s);
printf("key_d:%d\n", info->key_d);
printf("key_a:%d\n", info->key_a);
printf("key_ar_r:%d\n", info->key_ar_r);
printf("key_ar_l:%d\n", info->key_ar_l);
printf("key_ar_u:%d\n", info->key_ar_u);
printf("key_ar_d:%d\n", info->key_ar_d);
printf("key_esc:%d\n", info->key_esc);
printf("move_speed:%f\n", info->move_speed);
printf("rot_speed :%f\n", info->rot_speed);
printf("map_h:%d\n", info->map_h);

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
printf("-----\n");
printf("sp:%p\n", info->sp);
if (info->num_sprite > 0)
{
	for (int i = 0; i < info->num_sprite; i++)
	{
		printf("sprite[%d]:x:%f\n", i, info->sp[i].x);
		printf("sprite[%d]:y:%f\n", i, info->sp[i].y);
	}
}
printf("-------\n");
}


void	DEBUG_print_tmpmap(char tmp_map[MAP_HEIGHT][MAP_WIDTH], t_info *info)
{
	int y = 0;
	
	printf("---tmp_map---\n");
	while (y < info->map_h)
		printf("%s\n", tmp_map[y++]);
}